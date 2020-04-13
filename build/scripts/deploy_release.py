import pyperclip

from scripts.conan_release import DeployConanRelease
from scripts.release_constants import release_constants
from scripts.utilities import read_file, check_step, run, use_directory


class DeployRelease:
    def __init__(self, details):
        self.details = details

    # TODO copy in checks from https://github.com/pages-themes/minimal/blob/master/script/release
    # TODO try out https://pypi.org/project/GitPython/

    # Starter Project
    def commit_starter_project(self):
        with use_directory(release_constants.starter_project_dir):
            run(["git", "commit", "-m", F"'Update to Approvals {self.details.new_version}'"])

    def push_starter_project(self):
        with use_directory(release_constants.starter_project_dir):
            run(["git", "push", "origin", "master"])

    def publish_starter_project(self):
        self.commit_starter_project()
        self.push_starter_project()
        run(["open", "https://github.com/approvals/ApprovalTests.cpp.StarterProject/commits/master"])
        check_step("that the starter project is published")

    # Main Project
    def commit_main_project(self):
        with use_directory(release_constants.main_project_dir):
            run(["git", "commit", "-m", F"'{self.details.new_version} release'"])

    def push_main_project(self):
        with use_directory(release_constants.main_project_dir):
            run(["git", "push", "origin", "master"])

    def publish_main_project(self):
        self.commit_main_project()
        self.push_main_project()

    def upload_release_to_github(self):
        # Draft the upload to github
        release_notes = read_file(self.details.new_release_notes_path)
        pyperclip.copy(release_notes)
        print('The release notes are on the clipboard')
        github_url = F"'https://github.com/approvals/ApprovalTests.cpp/releases/new?tag={self.details.new_version}&title=Single%20Hpp%20File%20-%20{self.details.new_version}'"
        run(["open", github_url])
        run(["open", release_constants.release_dir])
        check_step("that the release is published")

    def publish_tweet(self):
        # Draft the tweet
        check_step("that you have created a screenshot of the release notes, for the Tweet")
        tweet_text = F"'https://twitter.com/intent/tweet?text=%23ApprovalTests.cpp+{self.details.new_version}+released%2C+now+with+___%21%0D%0Ahttps%3A%2F%2Fgithub.com%2Fapprovals%2FApprovalTests.cpp%2Freleases%2Ftag%2F{self.details.new_version}+%0D%0Aor+try+the+starter+project%3A+https%3A%2F%2Fgithub.com%2Fapprovals%2FApprovalTests.cpp.StarterProject%0D%0AThanks+%40LlewellynFalco+%40ClareMacraeUK+%21'"
        run(["open", tweet_text])
        check_step("that the tweet is published")

    def publish_on_reddit_optionally(self):
        # Announce on Reddit - maybe?
        run(["open", "https://www.reddit.com/r/cpp/"])
        check_step("if you want to announce this on Reddit r/cpp")

    def push_everything_live(self, start_at_conan = False):
        if not start_at_conan:
            self.publish_main_project()
            self.upload_release_to_github()
            self.publish_starter_project()
        DeployConanRelease.test_conan_and_create_pr(self.details)
        self.publish_tweet()
        self.publish_on_reddit_optionally()
