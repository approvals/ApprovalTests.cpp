import os
import shutil

from git import Repo

from scripts import version
from scripts.conan_release import PrepareConanRelease
from scripts.documentation_release import PrepareDocumentationRelease
from scripts.embed import create_single_header_file
from scripts.git_utilities import GitUtilities
from scripts.release_constants import release_constants
from scripts.single_header_file import SingleHeaderFile
from scripts.utilities import read_file, check_step, replace_text_in_file, run, write_file, use_directory, \
    check_step_with_revert, assert_step


class PrepareRelease:
    def __init__(self, details):
        self.details = details

    def check_pre_conditions_for_publish(self):
        if self.details.push_to_production:
            repo = Repo(release_constants.main_project_dir)
            assert_step(not repo.bare)

            assert_step((repo.active_branch.name == 'master'))

            GitUtilities.check_no_uncommitted_changes(repo)

            # From https://stackoverflow.com/questions/15849640/how-to-get-count-of-unpublished-commit-with-gitpython
            assert_step(len(
                list(repo.iter_commits('master@{u}..master'))) == 0, "there are un-pushed changes in ApprovalTests.cpp")

            run(["open", "https://github.com/approvals/ApprovalTests.cpp/commits/master"])
            check_step("the builds are passing")

            run(["open", "https://github.com/approvals/ApprovalTests.cpp/blob/master/build/relnotes_x.y.z.md"])
            run(["open", F"https://github.com/approvals/ApprovalTests.cpp/compare/{self.details.old_version}...master"])
            check_step("the release notes are ready")

            run(["open", "https://github.com/approvals/ApprovalTests.cpp/issues"])
            check_step("any issues resolved in this release are closed")

            run(["open", "https://github.com/approvals/ApprovalTests.cpp/milestones"])
            check_step("the milestone (if any) is up to date, including actual version number of release")

    def update_version_number_header(self):
        with use_directory(release_constants.approval_tests_dir):
            version_header = os.path.join("ApprovalTestsVersion.h")

            text = ('#ifndef APPROVALTESTS_CPP_APPROVALTESTSVERSION_H\n'
                    '#define APPROVALTESTS_CPP_APPROVALTESTSVERSION_H\n'
                    '\n'
                    f'#define APPROVALTESTS_VERSION_MAJOR {self.details.new_version_object["major"]}\n'
                    f'#define APPROVALTESTS_VERSION_MINOR {self.details.new_version_object["minor"]}\n'
                    f'#define APPROVALTESTS_VERSION_PATCH {self.details.new_version_object["patch"]}\n'
                    f'#define APPROVALTESTS_VERSION_STR "{version.get_version_without_v(self.details.new_version)}"\n'
                    '\n'
                    '#define APPROVALTESTS_VERSION                                                  \\n'
                    '    (APPROVALTESTS_VERSION_MAJOR * 10000 + APPROVALTESTS_VERSION_MINOR * 100 + \\n'
                    '     APPROVALTESTS_VERSION_PATCH)\n'
                    '\n'
                    '#endif //APPROVALTESTS_CPP_APPROVALTESTSVERSION_H\n'
                    )
            write_file(version_header, text)

    def create_simulated_single_header_file(self):
        return SingleHeaderFile.create('.')

    def create_single_header_file(self):
        self.create_simulated_single_header_file()

        simulated_single_header = os.path.abspath(release_constants.simulated_single_header_file_path)
        with use_directory("../build"):
            print(os.getcwd())
            self.run_for_approval_tests(simulated_single_header, self.details.release_new_single_header)
            text = read_file(self.details.release_new_single_header)
            text = (
                f'// Approval Tests version {self.details.new_version}\n'
                '// More information at: https://github.com/approvals/ApprovalTests.cpp\n'
                '\n'
                f'{text}'
            )
            write_file(self.details.release_new_single_header, text)
            return os.path.abspath(self.details.release_new_single_header)

    def run_for_approval_tests(self, initial_file, output_file):
        include_search_path1 = ".."
        include_search_path2 = "../ApprovalTests/"
        create_single_header_file(initial_file, output_file, include_search_path1, include_search_path2)

    def update_starter_project(self):
        STARTER_PATH_OLD_SINGLE_HEADER = F"{release_constants.starter_project_dir}/lib/{self.details.old_single_header}"
        STARTER_PATH_NEW_SINGLE_HEADER = F"{release_constants.starter_project_dir}/lib/{self.details.new_single_header}"

        # Make sure starter project folder is clean
        project_dir = release_constants.starter_project_dir
        GitUtilities.reset_and_clean_working_directory(project_dir)

        shutil.copyfile(self.details.release_new_single_header, STARTER_PATH_NEW_SINGLE_HEADER)

        # Delete the last release:
        if os.path.exists(STARTER_PATH_OLD_SINGLE_HEADER):
            os.remove(STARTER_PATH_OLD_SINGLE_HEADER)

        # Update the version in the "redirect" header:
        replace_text_in_file(F"{release_constants.starter_project_dir}/lib/ApprovalTests.hpp", self.details.old_version, self.details.new_version)

        # Update the version number in the Visual Studio project:
        replace_text_in_file(F"{release_constants.starter_project_dir}/visual-studio-2017/StarterProject.vcxproj", self.details.old_single_header,
                             self.details.new_single_header)

    def check_starter_project_builds(self):
        with use_directory(F"{release_constants.starter_project_dir}/cmake-build-debug"):
            run(["cmake", "--build", "."])

    def add_to_git(self):
        def add():
            run(["git", "add", "."])

        self.do_things_in_starter_project_and_main(add)

    def do_things_in_starter_project_and_main(self, function):
        with use_directory(release_constants.starter_project_dir):
            function()
        with use_directory(release_constants.main_project_dir):
            function()

    def check_changes(self):
        def revert():
            run(["git", "clean", "-fx"])
            run(["git", "reset", "--hard"])

        def revert_all():
            self.do_things_in_starter_project_and_main(revert)

        def do_nothing():
            pass

        check_step_with_revert("you are happy with the changes?", do_nothing)


    def prepare_everything(self):
        self.check_pre_conditions_for_publish()
        PrepareConanRelease.check_preconditions(self.details)

        self.update_version_number_header()

        self.create_single_header_file()

        self.update_starter_project()
        self.check_starter_project_builds()

        PrepareConanRelease.prepare_release(self.details)

        PrepareDocumentationRelease.prepare_documentation(self.details)

        version.write_version(self.details.new_version_object, release_constants.build_dir)
        self.add_to_git()

        self.check_changes()
