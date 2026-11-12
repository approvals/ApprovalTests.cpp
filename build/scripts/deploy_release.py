from typing import List

from git import Repo

from scripts.conan_release import DeployConanRelease
from scripts.git_utilities import GitUtilities
from scripts.github_checks import GitHubChecks
from scripts.release_details import ReleaseDetails
from scripts.starter_project_release import DeployStarterProjectRelease
from scripts.utilities import check_step, run, run_and_capture, use_directory
from scripts.vcpkg_release import DeployVcpkgRelease


class DeployRelease:
    def __init__(self, details: ReleaseDetails):
        self.details = details

    # Main Project
    def commit_main_project(self) -> None:
        message = F"{self.details.new_version_as_text()} release"
        GitUtilities.commit_everything(self.details.locations.main_project_dir, message)

    def push_main_project(self) -> None:
        with use_directory(self.details.locations.main_project_dir):
            run(["git", "push", "origin", "master"])

    def publish_main_project(self) -> None:
        self.commit_main_project()
        self.push_main_project()

    def upload_release_to_github(self) -> None:
        # Tag the exact release commit: the formatting bot may push to master straight after it
        commit_sha = Repo(self.details.locations.main_project_dir).head.commit.hexsha
        run_and_capture(self.get_github_release_command(commit_sha))
        GitHubChecks.check_release_published(self.details.project_details.github_repo,
                                             self.details.new_version_as_text(),
                                             self.details.new_single_header)

    def get_github_release_command(self, commit_sha: str) -> List[str]:
        return ["gh", "release", "create", self.details.new_version_as_text(),
                "--repo", self.details.project_details.github_repo,
                "--target", commit_sha,
                "--title", F"Single Hpp File - {self.details.new_version_as_text()}",
                "--notes-file", self.details.new_release_notes_path,
                self.details.release_new_single_header]

    def publish_on_reddit_optionally(self) -> None:
        # Announce on Reddit - maybe?
        run(["open", "https://www.reddit.com/r/cpp/"])
        check_step("if you want to announce this on Reddit r/cpp")

    def push_everything_live(self, start_at_conan: bool = False) -> None:
        if not start_at_conan:
            self.publish_main_project()
            self.upload_release_to_github()
            DeployStarterProjectRelease.publish_starter_project(self.details)
        # DeployConanRelease.test_conan_and_create_pr(self.details)
        # DeployVcpkgRelease.test_vcpkg_and_create_pr(self.details)
        self.publish_on_reddit_optionally()


