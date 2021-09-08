import os
from typing import List

import pyperclip
from git import Repo
from git.exc import GitCommandError

from scripts.multiline_string_utilities import remove_indentation_from
from scripts.vcpkg_release_details import VcpkgReleaseDetails
from scripts.git_utilities import GitUtilities
from scripts.project_details import ProjectDetails
from scripts.release_details import ReleaseDetails
from scripts.utilities import check_step, write_file, calculate_sha512, run, use_directory, optional_action
from scripts.version import Version


class PrepareVcpkgRelease:
    @staticmethod
    def check_preconditions(details: ReleaseDetails) -> None:
        if not details.project_details.update_vcpkg:
            return

        pass

    @staticmethod
    def prepare_release(details: ReleaseDetails) -> None:
        if not details.project_details.update_vcpkg:
            return

        GitUtilities.reset_and_clean_working_directory(details.vcpkg_details.vcpkg_repo_dir)

        accepted = details.old_version.get_version_text_without_v() in PrepareVcpkgRelease.get_accepted_approval_releases(
            details.project_details)
        if accepted:
            PrepareVcpkgRelease.sync_vcpkg_repo(details.vcpkg_details, details.project_details, details.new_version)
        else:
            # Do nothing - we are adding to our previous Pull Request
            # This does assume the same user is doing the previous and current release.
            print('Staying on current branch in vcpkg repo')
        PrepareVcpkgRelease.update_vcpkg_recipe(details)

    @staticmethod
    def sync_vcpkg_repo(vcpkg_details: VcpkgReleaseDetails, project_details: ProjectDetails, new_version: Version) -> None:
        print('Updating vcpkg repo and creating branch')
        with use_directory(vcpkg_details.vcpkg_repo_dir):
            print(os.getcwd())
            repo = Repo('.')
            repo.git.checkout('master')

            repo.remote('upstream').pull('master')
            try:
                repo.remote('origin').push('master')
            except GitCommandError:
                # If we are only preparing a release, not deploying, a failure
                # to push here (e.g. if being from GitHub Actions, to test release
                # preparation) is harmless, so just continue.
                print(f"INFO: No permission to push to remote repo in {vcpkg_details.vcpkg_repo_dir}")

            new_branch = PrepareVcpkgRelease.get_new_branch_name(project_details, new_version)
            print(repo.heads)
            if new_branch in repo.heads:
                def delete_branch() -> None:
                    print(f"Deleting previously-created branch {new_branch}")
                    repo.delete_head(new_branch)  # only works if not checked out
                optional_action(f'Branch {new_branch} already exists in vcpkg repo: Do you want to delete it?', delete_branch)
            current = repo.create_head(new_branch)
            current.checkout()

    @staticmethod
    def get_new_branch_name(project_details: ProjectDetails, new_version: Version) -> str:
        return f'{project_details.vcpkg_directory_name}.{new_version.get_version_text_without_v()}'

    @staticmethod
    def update_vcpkg_recipe(details: ReleaseDetails) -> None:
        vcpkg_approvaltests_dir = details.vcpkg_details.vcpkg_approvaltests_dir

        PrepareVcpkgRelease.update_portfile_cmake(details, vcpkg_approvaltests_dir)
        PrepareVcpkgRelease.update_vcpkg_vcpkg_json(vcpkg_approvaltests_dir, details.new_version)

    @staticmethod
    def update_vcpkg_vcpkg_json(vcpkg_approvaltests_dir: str, new_version: Version) -> None:
        vcpkg_data_file = os.path.join(vcpkg_approvaltests_dir, 'vcpkg.json')
        portfile_cmake_text = PrepareVcpkgRelease.create_vcpkg_vcpkg_json_text(new_version)

        write_file(vcpkg_data_file, portfile_cmake_text)

    @staticmethod
    def create_vcpkg_vcpkg_json_text(new_version: Version) -> str:
        vcpkg_data = \
            remove_indentation_from(F'''
                            {{
                              "name": "approval-tests-cpp",
                              "version": "{new_version.get_version_text_without_v()}",
                              "description": "Approval Tests allow you to verify a chunk of output (such as a file) in one operation as opposed to writing test assertions for each element.",
                              "homepage": "https://github.com/approvals/ApprovalTests.cpp"
                            }}
                        ''')
        return vcpkg_data

    @staticmethod
    def update_portfile_cmake(details: ReleaseDetails, vcpkg_approvaltests_dir: str) -> None:
        version = details.new_version
        vcpkg_data_file = os.path.join(vcpkg_approvaltests_dir, 'portfile.cmake')

        new_single_header = details.release_new_single_header
        licence_file = '../LICENSE'

        single_header_sha = calculate_sha512(new_single_header)
        licence_file_sha = calculate_sha512(licence_file)
        portfile_cmake_text = PrepareVcpkgRelease.create_portfile_cmake_text(version, single_header_sha,
                                                                             licence_file_sha)

        write_file(vcpkg_data_file, portfile_cmake_text)

    @staticmethod
    def create_portfile_cmake_text(new_version: Version, single_header_sha: str,
                                   licence_file_sha: str) -> str:
        new_version_with_v = new_version.get_version_text()
        vcpkg_data =   remove_indentation_from(F'''
                        vcpkg_download_distfile(single_header
                            URLS https://github.com/approvals/ApprovalTests.cpp/releases/download/{new_version_with_v}/ApprovalTests.{new_version_with_v}.hpp
                            FILENAME ApprovalTests.{new_version_with_v}.hpp
                            SHA512 {single_header_sha}
                        )
                        
                        vcpkg_download_distfile(license_file
                            URLS https://raw.githubusercontent.com/approvals/ApprovalTests.cpp/{new_version_with_v}/LICENSE
                            FILENAME ApprovalTestsLicense.{new_version_with_v}
                            SHA512 {licence_file_sha}
                        )
                        
                        file(INSTALL "${{single_header}}" DESTINATION "${{CURRENT_PACKAGES_DIR}}/include" RENAME ApprovalTests.hpp)
                        file(INSTALL "${{license_file}}" DESTINATION "${{CURRENT_PACKAGES_DIR}}/share/${{PORT}}" RENAME copyright)
                        ''')
        return vcpkg_data

    @staticmethod
    def get_accepted_approval_releases(project_details: ProjectDetails) -> List[str]:
        vcpkg_url = f'https://raw.githubusercontent.com/microsoft/vcpkg/master/versions/a-/{project_details.vcpkg_directory_name}.json'
        import urllib.request, json
        with urllib.request.urlopen(vcpkg_url) as url:
            data = json.loads(url.read().decode())
            return list(map(lambda v: v["version"], data['versions']))


class DeployVcpkgRelease:
    @staticmethod
    def test_vcpkg_and_create_pr(details: ReleaseDetails) -> None:
        if not details.project_details.update_vcpkg:
            return

        new_version_without_v = details.new_version.get_version_text_without_v()
        commit_message = F'[{details.project_details.vcpkg_directory_name}] Update to {new_version_without_v}'
        GitUtilities.add_and_commit_everything(details.vcpkg_details.vcpkg_repo_dir,
                                               commit_message)
        DeployVcpkgRelease.update_vcpkg_version_files(details, commit_message)
        GitUtilities.push_active_branch_origin(details.vcpkg_details.vcpkg_repo_dir)
        DeployVcpkgRelease.create_pull_request(details)

    @staticmethod
    def update_vcpkg_version_files(details: ReleaseDetails, commit_message: str) -> None:
        run(["brew", "install", "vcpkg"])
        run(["vcpkg", "x-add-version", f"--vcpkg-root={details.vcpkg_details.vcpkg_repo_dir}",
             details.project_details.vcpkg_directory_name])
        GitUtilities.add_and_commit_everything(details.vcpkg_details.vcpkg_repo_dir, commit_message)

    @staticmethod
    def create_pull_request(details: ReleaseDetails) -> None:
        accepted = details.old_version.get_version_text_without_v() in PrepareVcpkgRelease.get_accepted_approval_releases(
            details.project_details)
        if not accepted:
            print(
                F'Previous version number {details.old_version.get_version_text_without_v()} not found in list of '
                F'accepted releases. Not prompting to create a Pull Request.')
            return

        new_version_without_v = details.new_version.get_version_text_without_v()
        new_branch = PrepareVcpkgRelease.get_new_branch_name(details.project_details, details.new_version)
        run(["open",
             F'https://github.com/microsoft/vcpkg/compare/master...isidore:{new_branch}?expand=1'])
        description = F'[{details.project_details.vcpkg_directory_name}] Update to {new_version_without_v}'
        pyperclip.copy(description)
        print(
            F"Create a pull request, including this at the start of the description (which is on your clipboard): {description}")
        check_step("that you have created a Pull Request for vcpkg?")
