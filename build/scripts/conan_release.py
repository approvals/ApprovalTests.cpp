import os

from git import Repo

from scripts import version
from scripts.utilities import check_step, read_file, write_file, calculate_sha256, assert_step, run, use_directory


class ConanReleaseDetails:
    def __init__(self):
        self.conan_repo_dir = '../../../conan/conan-center-index-claremacrae'
        self.conan_approvaltests_dir = os.path.join(self.conan_repo_dir, 'recipes', 'approvaltests.cpp')


class PrepareConanRelease:
    @staticmethod
    def prepare_release(details):
        response = input("  Conan: Has the previous pull request been accepted? [Y/y] ")
        if response not in ['Y', 'y']:
            PrepareConanRelease.sync_conan_repo(details.new_version)
        else:
            # Do nothing - we are adding to our previous Pull Request
            # This does assume the same user is doing the previous and current release.
            print('Staying on current branch in conan repo')
        PrepareConanRelease.update_conan_recipe(details)

    @staticmethod
    def sync_conan_repo(new_version):
        print('Updating conan repo and creating branch')
        with use_directory(ConanReleaseDetails().conan_repo_dir):
            print(os.getcwd())
            repo = Repo('.')
            repo.git.checkout('master')

            repo.remote('upstream').pull('master')
            repo.remote('origin').push('master')

            new_branch = f'approvaltests.cpp.{version.get_version_without_v(new_version)}'
            current = repo.create_head(new_branch)
            current.checkout()

    @staticmethod
    def update_conan_recipe(details):
        PrepareConanRelease.check_conan_repo(details)

        new_version_with_v = details.new_version
        new_version_without_v = version.get_version_without_v(details.new_version)

        conan_approvaltests_dir = ConanReleaseDetails().conan_approvaltests_dir

        PrepareConanRelease.update_conandata_yml(details, ConanReleaseDetails().conan_approvaltests_dir, new_version_with_v,
                                                 new_version_without_v)
        PrepareConanRelease.update_conan_config_yml(conan_approvaltests_dir, new_version_without_v)

    @staticmethod
    def update_conan_config_yml(conan_approvaltests_dir, new_version_without_v):
        conan_data_file = os.path.join(conan_approvaltests_dir, 'config.yml')
        conandata_yml_text = read_file(conan_data_file)

        conan_data = \
            F'''  {new_version_without_v}:
    folder: all
    '''
        conandata_yml_text += conan_data

        write_file(conan_data_file, conandata_yml_text)

    @staticmethod
    def update_conandata_yml(details, conan_approvaltests_dir, new_version_with_v, new_version_without_v):
        conan_data_file = os.path.join(conan_approvaltests_dir, 'all', 'conandata.yml')
        conandata_yml_text = read_file(conan_data_file)

        new_single_header = details.release_new_single_header
        licence_file = '../LICENSE'

        conan_data = \
            F'''  {new_version_without_v}:
    - url: https://github.com/approvals/ApprovalTests.cpp/releases/download/{new_version_with_v}/ApprovalTests.{new_version_with_v}.hpp
      sha256: {calculate_sha256(new_single_header)}
    - url: "https://raw.githubusercontent.com/approvals/ApprovalTests.cpp/{new_version_with_v}/LICENSE"
      sha256: {calculate_sha256(licence_file)}
    '''
        conandata_yml_text += conan_data

        write_file(conan_data_file, conandata_yml_text)

    @staticmethod
    def check_conan_repo(details):
        repo = Repo(ConanReleaseDetails().conan_repo_dir)
        assert_step(not repo.bare)

        # TODO Add descriptions in case of failure
        assert_step((repo.active_branch.name == 'master'))

        assert_step((len(repo.index.diff(None)) == 0))  # Modified
        assert_step((len(repo.index.diff("HEAD")) == 0))  # Staged

        run(["open", "https://github.com/conan-io/conan/releases"])
        run(["conan", "--version"])
        # TODO pip3 install --upgrade conan
        check_step("you are running the latest Conan release")


class DeployConanRelease:
    @staticmethod
    def test_conan_and_create_pr(details):
        with use_directory(os.path.join(ConanReleaseDetails().conan_approvaltests_dir, 'all')):
            # We cannot test the new Conan recipe until the new release has been
            # published on github
            new_version_without_v = version.get_version_without_v(details.new_version)
            run(['conan', 'create', '.', F'{new_version_without_v}@'])

            check_step(F"Commit the changes - with message 'Add approvaltests.cpp {new_version_without_v}'")
            check_step('Push the changes - NB on the feature branch for the release')

        print(
            F"Create a pull request, including this in the description: **approvaltests.cpp/{new_version_without_v}**")
        check_step("that you have created a Pull Request for conan-center-index?")
