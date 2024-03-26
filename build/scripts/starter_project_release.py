import os
import shutil

from git import Repo

from scripts.git_utilities import GitUtilities
from scripts.project_details import ProjectDetails
from scripts.release_details import ReleaseDetails
from scripts.utilities import assert_step, replace_text_in_file, use_directory, run, check_url_exists, \
    ensure_directory_exists


class PrepareStarterProjectRelease:
    @staticmethod
    def check_pre_conditions_for_starter_project_repo(details: ReleaseDetails) -> None:
        repo = Repo(details.locations.starter_project_dir)
        assert_step(not repo.bare)
        GitUtilities.check_branch_name(repo, 'master')

    @staticmethod
    def update_starter_project(details: ReleaseDetails) -> None:
        STARTER_PATH_OLD_SINGLE_HEADER = F"{details.locations.starter_project_dir}/lib/{details.old_single_header}"
        STARTER_PATH_NEW_SINGLE_HEADER = F"{details.locations.starter_project_dir}/lib/{details.new_single_header}"

        # Make sure starter project folder is clean
        project_dir = details.locations.starter_project_dir
        GitUtilities.reset_and_clean_working_directory(project_dir)

        shutil.copyfile(details.release_new_single_header, STARTER_PATH_NEW_SINGLE_HEADER)

        # Delete the last release:
        if os.path.exists(STARTER_PATH_OLD_SINGLE_HEADER):
            os.remove(STARTER_PATH_OLD_SINGLE_HEADER)
        else:
            raise RuntimeError(F"""
    ----------------------------------------------------------------
    ERROR: Old header file does not exist:
    {STARTER_PATH_OLD_SINGLE_HEADER}
    Starting state of Starter Project does not match '{details.old_version.get_version_text()}'
    Check whether:
    1. There were uncommitted changes to version.ini in main project,
       from a previous release preparation step.
    2. The Starter Project repo needs pulling.
    3. This is a CI build of a release tag - in which case the
       updated Starter Project has not yet been pushed, and this 
       failure can be ignored.
    ----------------------------------------------------------------
    
    """)

        # Update the version in the "redirect" header:
        replace_text_in_file(
            F"{details.locations.starter_project_dir}/lib/{details.project_details.simulated_single_header_file}",
            details.old_version.get_version_text(),
            details.new_version.get_version_text())


    @staticmethod
    def check_starter_project_builds(details: ReleaseDetails) -> None:
        build_dir = F"{details.locations.starter_project_dir}/cmake-build-validate-release"
        ensure_directory_exists(build_dir)
        with use_directory(build_dir):
            run(["cmake", ".."])
            run(["cmake", "--build", "."])


class DeployStarterProjectRelease:
    @staticmethod
    def get_url_for_starter_project_single_header_for_version(project_details: ProjectDetails,
                                                              version_without_v: str) -> str:
        return F'https://raw.githubusercontent.com/approvals/' \
               F'{project_details.github_project_name}.StarterProject/master/lib/' \
               F'{project_details.library_folder_name}.v.{version_without_v}.hpp'

    @staticmethod
    def commit_starter_project(details: ReleaseDetails) -> None:
        message = F"Update to {details.project_details.github_project_name} {details.new_version_as_text()}"
        GitUtilities.commit_everything(details.locations.starter_project_dir, message)

    @staticmethod
    def push_starter_project(details: ReleaseDetails) -> None:
        with use_directory(details.locations.starter_project_dir):
            run(["git", "push", "origin", "master"])

    @staticmethod
    def publish_starter_project(details: ReleaseDetails) -> None:
        DeployStarterProjectRelease.commit_starter_project(details)
        DeployStarterProjectRelease.push_starter_project(details)
        assert_step(DeployStarterProjectRelease.check_starter_project_published(details),
                    "the starter project is published")

    @staticmethod
    def check_starter_project_published(details: ReleaseDetails) -> bool:
        version = details.new_version.get_version_text_without_v()
        url = DeployStarterProjectRelease.get_url_for_starter_project_single_header_for_version(
            details.project_details, version)
        published = check_url_exists(url)
        return published
