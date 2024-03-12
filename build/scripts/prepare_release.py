import os
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
from scripts.starter_project_release import PrepareStarterProjectRelease
from scripts.utilities import check_step, run, use_directory, \
    check_step_with_revert, assert_step
from scripts.vcpkg_release import PrepareVcpkgRelease
from scripts.version import Version


class PrepareRelease:
    def __init__(self, details: ReleaseDetails) -> None:
        self.details = details

    def check_pre_conditions_for_publish(self) -> None:
        if self.details.push_to_production:
            self.check_pre_conditions_for_main_repo()
            PrepareStarterProjectRelease.check_pre_conditions_for_starter_project_repo(self.details)

            open_url_command = "open"
            if os.name != "Darwin":
                open_url_command = "xdg-open"

            run([open_url_command, F"{self.details.project_details.github_project_url}/commits/master"])
            check_step("the builds are passing")

            run([open_url_command, F"{self.details.project_details.github_project_url}/blob/master/build/relnotes_x.y.z.md"])
            run([open_url_command,
                 F"{self.details.project_details.github_project_url}/compare/{self.details.old_version.get_version_text()}...master"])
            check_step("the release notes are ready")

            run([open_url_command, F"{self.details.project_details.github_project_url}/issues"])
            check_step("any issues resolved in this release are closed")

    def check_pre_conditions_for_main_repo(self) -> None:
        repo = Repo(self.details.locations.main_project_dir)
        assert_step(not repo.bare)
        GitUtilities.check_branch_name(repo, 'master')
        GitUtilities.check_no_uncommitted_changes(repo)

        # From https://stackoverflow.com/questions/15849640/how-to-get-count-of-unpublished-commit-with-gitpython
        assert_step(len(
            list(repo.iter_commits('master@{u}..master'))) == 0,
                    f"there are un-pushed changes in {self.details.project_details.github_project_name}")

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
        # PrepareConanRelease.check_preconditions(self.details)
        # PrepareVcpkgRelease.check_preconditions(self.details)
        self.check_pre_conditions_for_publish()

        CppGeneration.prepare_release(self.details)

        PrepareStarterProjectRelease.update_starter_project(self.details)
        PrepareStarterProjectRelease.check_starter_project_builds(self.details)

        # PrepareConanRelease.prepare_release(self.details)
        # PrepareVcpkgRelease.prepare_release(self.details)

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
