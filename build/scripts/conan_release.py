import os

import pyperclip
from git import Repo

from scripts.git_utilities import GitUtilities
from scripts.release_details import ReleaseDetails
from scripts.utilities import check_step, read_file, write_file, calculate_sha256, run, use_directory
from scripts.version import Version


class ConanReleaseDetails:
    def __init__(self) -> None:
        self.conan_repo_dir = ConanReleaseDetails.get_conan_repo_directory()
        self.conan_approvaltests_dir = os.path.join(self.conan_repo_dir, 'recipes', 'approvaltests.cpp')

    @staticmethod
    def get_conan_repo_directory() -> str:
        possibles = [
            '../../conan-center-index-claremacrae',  # llewellyn
            '../../../conan/conan-center-index-claremacrae'  # clare
        ]
        for dir in possibles:
            if os.path.isdir(dir):
                return dir
        raise RuntimeError("Could not find fork of conan-center-index")


class PrepareConanRelease:
    @staticmethod
    def check_preconditions(details: ReleaseDetails) -> None:
        PrepareConanRelease.update_conan_to_latest()

    @staticmethod
    def prepare_release(details: ReleaseDetails) -> None:
        GitUtilities.reset_and_clean_working_directory(ConanReleaseDetails().conan_repo_dir)

        response = input("  Conan: Has the previous pull request been accepted? [Y/y] ")
        if response in ['Y', 'y']:
            PrepareConanRelease.sync_conan_repo(details.new_version)
        else:
            # Do nothing - we are adding to our previous Pull Request
            # This does assume the same user is doing the previous and current release.
            print('Staying on current branch in conan repo')
        PrepareConanRelease.update_conan_recipe(details)

    @staticmethod
    def sync_conan_repo(new_version: Version) -> None:
        print('Updating conan repo and creating branch')
        with use_directory(ConanReleaseDetails().conan_repo_dir):
            print(os.getcwd())
            repo = Repo('.')
            repo.git.checkout('master')

            repo.remote('upstream').pull('master')
            repo.remote('origin').push('master')

            new_branch = PrepareConanRelease.get_new_branch_name(new_version)
            current = repo.create_head(new_branch)
            current.checkout()

    @staticmethod
    def get_new_branch_name(new_version: Version) -> str:
        new_branch = f'approvaltests.cpp.{new_version.get_version_text_without_v()}'
        return new_branch

    @staticmethod
    def update_conan_recipe(details: ReleaseDetails) -> None:
        conan_approvaltests_dir = ConanReleaseDetails().conan_approvaltests_dir

        PrepareConanRelease.update_conandata_yml(details, ConanReleaseDetails().conan_approvaltests_dir)
        PrepareConanRelease.update_conan_config_yml(conan_approvaltests_dir, details.new_version)

    @staticmethod
    def update_conan_config_yml(conan_approvaltests_dir: str, new_version: Version) -> None:
        conan_data_file = os.path.join(conan_approvaltests_dir, 'config.yml')
        conandata_yml_text = read_file(conan_data_file)

        conandata_yml_text += PrepareConanRelease.create_conan_config_yml_text(new_version)

        write_file(conan_data_file, conandata_yml_text)

    @staticmethod
    def create_conan_config_yml_text(new_version: Version) -> str:
        conan_data = \
            F'''  {new_version.get_version_text_without_v()}:
    folder: all
'''
        return conan_data

    @staticmethod
    def update_conandata_yml(details: ReleaseDetails, conan_approvaltests_dir: str) -> None:
        version = details.new_version
        conan_data_file = os.path.join(conan_approvaltests_dir, 'all', 'conandata.yml')
        conandata_yml_text = read_file(conan_data_file)

        new_single_header = details.release_new_single_header
        licence_file = '../LICENSE'

        single_header_sha = calculate_sha256(new_single_header)
        licence_file_sha = calculate_sha256(licence_file)
        conan_data = PrepareConanRelease.create_conandata_yml_text(version,
                                                                   single_header_sha, licence_file_sha)
        conandata_yml_text += conan_data

        write_file(conan_data_file, conandata_yml_text)

    @staticmethod
    def create_conandata_yml_text(new_version: Version, single_header_sha: str, licence_file_sha: str) -> str:
        new_version_with_v = new_version.get_version_text()
        conan_data = \
            F'''  {new_version.get_version_text_without_v()}:
    - url: https://github.com/approvals/ApprovalTests.cpp/releases/download/{new_version_with_v}/ApprovalTests.{new_version_with_v}.hpp
      sha256: {single_header_sha}
    - url: "https://raw.githubusercontent.com/approvals/ApprovalTests.cpp/{new_version_with_v}/LICENSE"
      sha256: {licence_file_sha}
'''
        return conan_data

    @staticmethod
    def update_conan_to_latest() -> None:
        run(["pip3", "install", "--upgrade", "conan"])


class DeployConanRelease:
    @staticmethod
    def test_conan_and_create_pr(details: ReleaseDetails) -> None:
        with use_directory(os.path.join(ConanReleaseDetails().conan_approvaltests_dir, 'all')):
            # We cannot test the new Conan recipe until the new release has been
            # published on github
            new_version_without_v = details.new_version.get_version_text_without_v()
            run(['conan', 'create', '.', F'{new_version_without_v}@'])

            check_step(F"Commit the changes - with message 'Add approvaltests.cpp {new_version_without_v}'")
            check_step('Push the changes - NB on the feature branch for the release')

        new_branch = PrepareConanRelease.get_new_branch_name(details.new_version)
        run(["open", F'https://github.com/conan-io/conan-center-index/compare/master...claremacrae:{new_branch}?expand=1'])
        description = F'** approvaltests.cpp / {new_version_without_v} **'
        pyperclip.copy(description)
        print(
            F"Create a pull request, including this at the start of the description (which is on your clipboard): {description}")
        check_step("that you have created a Pull Request for conan-center-index?")
