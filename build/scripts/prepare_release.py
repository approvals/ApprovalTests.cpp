import os
import shutil
from typing import Callable

from git import Repo

from scripts.code_generation import CppGeneration
from scripts.conan_release import PrepareConanRelease
from scripts.deploy_release import DeployRelease
from scripts.documentation_release import PrepareDocumentationRelease
from scripts.git_utilities import GitUtilities
from scripts.project_details import ProjectDetails
from scripts.release_constants import release_constants
from scripts.release_details import ReleaseDetails
from scripts.utilities import check_step, replace_text_in_file, run, use_directory, \
    check_step_with_revert, assert_step
from scripts.version import Version


class PrepareRelease:
    def __init__(self, details: ReleaseDetails) -> None:
        self.details = details

    def check_pre_conditions_for_publish(self) -> None:
        if self.details.push_to_production:
            self.check_pre_conditions_for_main_repo()

            run(["open", F"{self.details.project_details.github_project_url}/commits/master"])
            check_step("the builds are passing")

            run(["open", F"{self.details.project_details.github_project_url}/blob/master/build/relnotes_x.y.z.md"])
            run(["open",
                 F"{self.details.project_details.github_project_url}/compare/{self.details.old_version.get_version_text()}...master"])
            check_step("the release notes are ready")

            run(["open", F"{self.details.project_details.github_project_url}/issues"])
            check_step("any issues resolved in this release are closed")

            run(["open", F"{self.details.project_details.github_project_url}/milestones"])
            check_step("the milestone (if any) is up to date, including actual version number of release")

    def check_pre_conditions_for_main_repo(self) -> None:
        repo = Repo(self.details.locations.main_project_dir)
        assert_step(not repo.bare)
        GitUtilities.check_branch_name(repo, 'master')
        GitUtilities.check_no_uncommitted_changes(repo)

        # From https://stackoverflow.com/questions/15849640/how-to-get-count-of-unpublished-commit-with-gitpython
        assert_step(len(
            list(repo.iter_commits('master@{u}..master'))) == 0,
                    f"there are un-pushed changes in {self.details.project_details.github_project_name}")

    def update_starter_project(self) -> None:
        STARTER_PATH_OLD_SINGLE_HEADER = F"{self.details.locations.starter_project_dir}/lib/{self.details.old_single_header}"
        STARTER_PATH_NEW_SINGLE_HEADER = F"{self.details.locations.starter_project_dir}/lib/{self.details.new_single_header}"

        # Make sure starter project folder is clean
        project_dir = self.details.locations.starter_project_dir
        GitUtilities.reset_and_clean_working_directory(project_dir)

        shutil.copyfile(self.details.release_new_single_header, STARTER_PATH_NEW_SINGLE_HEADER)

        # Delete the last release:
        if os.path.exists(STARTER_PATH_OLD_SINGLE_HEADER):
            os.remove(STARTER_PATH_OLD_SINGLE_HEADER)
        else:
            raise RuntimeError(F"""
----------------------------------------------------------------
ERROR: Old header file does not exist:
{STARTER_PATH_OLD_SINGLE_HEADER}
Starting state of Starter Project does not match '{self.details.old_version.get_version_text()}'
Check whether:
1. There were uncommitted changes to version.ini in main project,
   from a previous release preparation step.
2. The Starter Project repo needs pulling.
----------------------------------------------------------------

""")

        # Update the version in the "redirect" header:
        replace_text_in_file(
            F"{self.details.locations.starter_project_dir}/lib/{self.details.project_details.simulated_single_header_file}",
            self.details.old_version.get_version_text(),
            self.details.new_version.get_version_text())

        # Update the version number in the Visual Studio project:
        visual_studio_2017_sln = F"{self.details.locations.starter_project_dir}/visual-studio-2017/StarterProject.vcxproj"
        if os.path.isfile(visual_studio_2017_sln):
            replace_text_in_file(visual_studio_2017_sln,
                                 self.details.old_single_header,
                                 self.details.new_single_header)
        else:
            print(f"Info: No Visual Studio solution file: {visual_studio_2017_sln}")

    def check_starter_project_builds(self) -> None:
        with use_directory(F"{self.details.locations.starter_project_dir}/cmake-build-debug"):
            run(["cmake", "--build", "."])

    def add_to_git(self) -> None:
        def add() -> None:
            run(["git", "add", "."])

        self.do_things_in_starter_project_and_main(add)

    def do_things_in_starter_project_and_main(self, function: Callable) -> None:
        with use_directory(self.details.locations.starter_project_dir):
            function()
        with use_directory(self.details.locations.main_project_dir):
            function()

    def check_changes(self) -> None:
        def revert() -> None:
            run(["git", "clean", "-fx"])
            run(["git", "reset", "--hard"])

        def revert_all() -> None:
            self.do_things_in_starter_project_and_main(revert)

        def do_nothing() -> None:
            pass

        check_step_with_revert("you are happy with the changes?", do_nothing)

    def prepare_everything(self) -> None:
        self.check_pre_conditions_for_publish()
        PrepareConanRelease.check_preconditions(self.details)

        CppGeneration.prepare_release(self.details)

        self.update_starter_project()
        self.check_starter_project_builds()

        PrepareConanRelease.prepare_release(self.details)

        PrepareDocumentationRelease.prepare_documentation(self.details)

        self.details.new_version.write(release_constants.build_dir)
        self.add_to_git()

        self.check_changes()


def build(update_version: Callable[[Version], Version], deploy: bool,
          project_details: ProjectDetails) -> None:
    old_version = set_working_directory_and_load_current_version(project_details.library_folder_name)
    new_version = update_version(old_version)

    release_details = ReleaseDetails(old_version, new_version, deploy, project_details)
    prepare_release = PrepareRelease(release_details)
    prepare_release.prepare_everything()
    if not release_details.push_to_production:
        print("Everything worked - didn't commit or push")
    else:
        deploy_release = DeployRelease(release_details)
        deploy_release.push_everything_live()


def set_working_directory_and_load_current_version(library_folder_name: str) -> Version:
    """
    :param library_folder_name: the sub-folder where headers are, e.g. "ApprovalTests"
    """
    os.chdir(os.path.join("..", library_folder_name))
    return Version.read(release_constants.build_dir)
