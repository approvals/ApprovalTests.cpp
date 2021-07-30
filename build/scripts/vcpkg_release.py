import os
from typing import List

import pyperclip
import yaml
from git import Repo
from git.exc import GitCommandError

from scripts.vcpkg_release_details import VcpkgReleaseDetails
from scripts.git_utilities import GitUtilities
from scripts.project_details import ProjectDetails
from scripts.release_details import ReleaseDetails
from scripts.utilities import check_step, read_file, write_file, calculate_sha256, run, use_directory, read_url, \
    optional_action
from scripts.version import Version


# TODO Check vcpkg installed
# TODO Check vcpkg uptodate
# TODO Check vcpkg-hooks installed: https://github.com/vcpkg-io/hooks.git
# TODO Check vcpkg-hooks uptodate

class PrepareVcpkgRelease:
    @staticmethod
    def check_preconditions(details: ReleaseDetails) -> None:
        PrepareVcpkgRelease.update_vcpkg_to_latest()
        PrepareVcpkgRelease.confirm_previous_release_still_works(details)

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

        PrepareVcpkgRelease.update_vcpkgdata_yml(details, vcpkg_approvaltests_dir)
        PrepareVcpkgRelease.update_vcpkg_vcpkg_json(vcpkg_approvaltests_dir, details.new_version)

    @staticmethod
    def update_vcpkg_vcpkg_json(vcpkg_approvaltests_dir: str, new_version: Version) -> None:
        vcpkg_data_file = os.path.join(vcpkg_approvaltests_dir, 'config.yml')
        vcpkgdata_yml_text = read_file(vcpkg_data_file)

        vcpkgdata_yml_text += PrepareVcpkgRelease.create_vcpkg_vcpkg_json_text(new_version)

        write_file(vcpkg_data_file, vcpkgdata_yml_text)

    @staticmethod
    def create_vcpkg_vcpkg_json_text(new_version: Version) -> str:
        vcpkg_data = \
            F'''  {new_version.get_version_text_without_v()}:
    folder: all
'''
        return vcpkg_data

    @staticmethod
    def update_vcpkgdata_yml(details: ReleaseDetails, vcpkg_approvaltests_dir: str) -> None:
        version = details.new_version
        vcpkg_data_file = os.path.join(vcpkg_approvaltests_dir, 'all', 'vcpkgdata.yml')
        vcpkgdata_yml_text = read_file(vcpkg_data_file)

        new_single_header = details.release_new_single_header
        licence_file = '../LICENSE'

        single_header_sha = calculate_sha256(new_single_header)
        licence_file_sha = calculate_sha256(licence_file)
        vcpkg_data = PrepareVcpkgRelease.create_vcpkgdata_yml_text(details.project_details, version, single_header_sha,
                                                                   licence_file_sha)
        vcpkgdata_yml_text += vcpkg_data

        write_file(vcpkg_data_file, vcpkgdata_yml_text)

    @staticmethod
    def create_vcpkgdata_yml_text(project_details: ProjectDetails, new_version: Version, single_header_sha: str,
                                  licence_file_sha: str) -> str:
        new_version_with_v = new_version.get_version_text()
        vcpkg_data = \
            F'''  {new_version.get_version_text_without_v()}:
    - url: {project_details.github_project_url}/releases/download/{new_version_with_v}/{project_details.library_folder_name}.{new_version_with_v}.hpp
      sha256: {single_header_sha}
    - url: "https://raw.githubusercontent.com/approvals/{project_details.github_project_name}/{new_version_with_v}/LICENSE"
      sha256: {licence_file_sha}
'''
        return vcpkg_data

    @staticmethod
    def update_vcpkg_to_latest() -> None:
        run(["pip3", "install", "--upgrade", "vcpkg"])

    @staticmethod
    def confirm_previous_release_still_works(details: ReleaseDetails) -> None:
        last_approved = max(PrepareVcpkgRelease.get_accepted_approval_releases(details.project_details), key=lambda x: Version.from_string_without_v(x))

        DeployVcpkgRelease.test_vcpkg_build_passes(details.vcpkg_details, last_approved)

    @staticmethod
    def get_accepted_approval_releases(project_details: ProjectDetails) -> List[str]:
        vcpkg_url = f'https://raw.githubusercontent.com/vcpkg-io/vcpkg-center-index/master/recipes/{project_details.vcpkg_directory_name}/config.yml'
        text = read_url(vcpkg_url)
        return yaml.safe_load(text)['versions'].keys()


class DeployVcpkgRelease:
    @staticmethod
    def test_vcpkg_and_create_pr(details: ReleaseDetails) -> None:
        if not details.project_details.update_vcpkg:
            return

        new_version_without_v = details.new_version.get_version_text_without_v()
        # See test_vcpkg_release.py's disabled_test_all_vcpkg_versions_build() if you want to test
        # that vcpkg builds against all supported library versions.
        DeployVcpkgRelease.test_vcpkg_build_passes(details.vcpkg_details, new_version_without_v)

        GitUtilities.add_and_commit_everything(details.vcpkg_details.vcpkg_repo_dir,
                                               F'Add {details.project_details.vcpkg_directory_name} {new_version_without_v}')
        GitUtilities.push_active_branch_origin(details.vcpkg_details.vcpkg_repo_dir)

        DeployVcpkgRelease.create_pull_request(details)

    @staticmethod
    def test_vcpkg_build_passes(vcpkg_details: VcpkgReleaseDetails, version_without_v: str) -> None:
        vcpkg_directory = os.path.join(vcpkg_details.vcpkg_approvaltests_dir, 'all')
        with use_directory(vcpkg_directory):
            run(['vcpkg', 'create', '--build=missing', '.', F'{version_without_v}@'])

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
             F'https://github.com/vcpkg-io/vcpkg-center-index/compare/master...claremacrae:{new_branch}?expand=1'])
        description = F'**{details.project_details.vcpkg_directory_name}/{new_version_without_v}**'
        pyperclip.copy(description)
        print(
            F"Create a pull request, including this at the start of the description (which is on your clipboard): {description}")
        check_step("that you have created a Pull Request for vcpkg-center-index?")
