import pyperclip

from scripts.conan_release import DeployConanRelease
from scripts.git_utilities import GitUtilities
from scripts.release_constants import release_constants
from scripts.release_details import ReleaseDetails
from scripts.starter_project_release import DeployStarterProjectRelease
from scripts.utilities import read_file, check_step, run, use_directory
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
        # Draft the upload to github
        release_notes = read_file(self.details.new_release_notes_path)
        pyperclip.copy(release_notes)
        print('The release notes are on the clipboard')
        github_url = self.get_github_release_url()
        run(["open", github_url])
        run(["open", release_constants.release_dir])
        check_step("that the release is published")

    def get_github_release_url(self) -> str:
        return F"'{self.details.project_details.github_project_url}/releases/new?" \
               F"tag={self.details.new_version_as_text()}&" \
               F"title=Single%20Hpp%20File%20-%20{self.details.new_version_as_text()}'"

    def publish_tweet(self) -> None:
        # Draft the tweet
        check_step("that you have created a screenshot of the release notes, for the Tweet")
        tweet_text = self.get_tweet_text()
        run(["open", tweet_text])
        check_step("that the tweet is published")

    def get_tweet_text(self) -> str:
        project = self.details.project_details.github_project_name
        return F"'https://twitter.com/intent/tweet?text=%23{project}+" \
               F"{self.details.new_version_as_text()}" \
               F"+released%2C+now+with+___%21%0D%0Ahttps%3A%2F%2Fgithub.com%2F" \
               F"approvals%2F{project}%2Freleases%2Ftag%2F" \
               F"{self.details.new_version_as_text()}+%0D%0Aor+try+the+starter+project%3A+https%3A%2F%2Fgithub.com" \
               F"%2Fapprovals%2F{project}.StarterProject%0D%0AThanks+%40LlewellynFalco+%40ClareMacraeUK+%21'"

    def publish_on_reddit_optionally(self) -> None:
        # Announce on Reddit - maybe?
        run(["open", "https://www.reddit.com/r/cpp/"])
        check_step("if you want to announce this on Reddit r/cpp")

    def push_everything_live(self, start_at_conan: bool = False) -> None:
        if not start_at_conan:
            self.publish_main_project()
            self.upload_release_to_github()
            DeployStarterProjectRelease.publish_starter_project(self.details)
        DeployConanRelease.test_conan_and_create_pr(self.details)
        DeployVcpkgRelease.test_vcpkg_and_create_pr(self.details)
        self.publish_tweet()
        self.publish_on_reddit_optionally()


