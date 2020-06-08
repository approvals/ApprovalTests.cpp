import pyperclip

from scripts.conan_release import DeployConanRelease
from scripts.git_utilities import GitUtilities
from scripts.release_constants import release_constants
from scripts.release_details import ReleaseDetails
from scripts.utilities import read_file, check_step, run, use_directory, check_url_exists, assert_step


class DeployRelease:
    def __init__(self, details: ReleaseDetails):
        self.details = details

    # Starter Project
    def commit_starter_project(self) -> None:
        message = F"Update to Approvals {self.details.new_version_as_text()}"
        GitUtilities.commit_everything(self.details.locations.starter_project_dir, message)

    def push_starter_project(self) -> None:
        with use_directory(self.details.locations.starter_project_dir):
            run(["git", "push", "origin", "master"])

    def publish_starter_project(self) -> None:
        self.commit_starter_project()
        self.push_starter_project()
        assert_step(self.check_starter_project_published(), "the starter project is published")

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
        github_url = F"'https://github.com/approvals/ApprovalTests.cpp/releases/new?tag={self.details.new_version_as_text()}&title=Single%20Hpp%20File%20-%20{self.details.new_version_as_text()}'"
        run(["open", github_url])
        run(["open", release_constants.release_dir])
        check_step("that the release is published")

    def publish_tweet(self) -> None:
        # Draft the tweet
        check_step("that you have created a screenshot of the release notes, for the Tweet")
        tweet_text = F"'https://twitter.com/intent/tweet?text=%23ApprovalTests.cpp+{self.details.new_version_as_text()}+released%2C+now+with+___%21%0D%0Ahttps%3A%2F%2Fgithub.com%2Fapprovals%2FApprovalTests.cpp%2Freleases%2Ftag%2F{self.details.new_version_as_text()}+%0D%0Aor+try+the+starter+project%3A+https%3A%2F%2Fgithub.com%2Fapprovals%2FApprovalTests.cpp.StarterProject%0D%0AThanks+%40LlewellynFalco+%40ClareMacraeUK+%21'"
        run(["open", tweet_text])
        check_step("that the tweet is published")

    def publish_on_reddit_optionally(self) -> None:
        # Announce on Reddit - maybe?
        run(["open", "https://www.reddit.com/r/cpp/"])
        check_step("if you want to announce this on Reddit r/cpp")

    def push_everything_live(self, start_at_conan: bool = False) -> None:
        if not start_at_conan:
            self.publish_main_project()
            self.upload_release_to_github()
            self.publish_starter_project()
        DeployConanRelease.test_conan_and_create_pr(self.details)
        self.publish_tweet()
        self.publish_on_reddit_optionally()

    def check_starter_project_published(self) -> bool:
        version = self.details.new_version.get_version_text_without_v()
        url = DeployRelease.get_url_for_starter_project_single_header_for_version(version)
        published = check_url_exists(url)
        return published

    @staticmethod
    def get_url_for_starter_project_single_header_for_version(version_without_v: str) -> str:
        return F'https://raw.githubusercontent.com/approvals/ApprovalTests.cpp.StarterProject/master/lib/ApprovalTests.v.{version_without_v}.hpp'
