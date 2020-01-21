import os
import shutil

import pyperclip

import Version
from Utilities import read_file, check_step, run, pushdir, popdir
from prepare_release import PrepareRelease


class DeployRelease(PrepareRelease):

    # TODO copy in checks from https://github.com/pages-themes/minimal/blob/master/script/release

    # https://stackoverflow.com/a/10528259/104370
    # initialise a directory stack

    def commit_starter_project(self):
        pushdir(self.details.starter_project_dir)
        run(["git", "add", "."])
        run(["git", "commit", "-m", F"Update to Approvals {self.details.new_version}"])
        popdir()

    def push_starter_project(self):
        pushdir(self.details.starter_project_dir)
        run(["git", "push", "origin", "master"])
        popdir()

    def commit_main_project(self):
        pushdir(self.details.main_project_dir)
        run(["git", "add", "."])
        run(["git", "commit", "-m", F"{self.details.new_version} release"])
        popdir()

    def push_main_project(self):
        pushdir(self.details.main_project_dir)
        run(["git", "push", "origin", "master"])
        popdir()

    def publish_main_project(self):
        new_release_notes_path = os.path.join(self.details.build_dir, F'relnotes_{Version.get_version_without_v(self.details.new_version)}.md')
        xxx_release_notes_path = os.path.join(self.details.build_dir, F'relnotes_X.X.X.md')
        template_release_notes_path = os.path.join(self.details.build_dir, F'relnotes_template.md')

        shutil.move(xxx_release_notes_path, new_release_notes_path)
        shutil.copyfile(template_release_notes_path, xxx_release_notes_path)

        self.commit_main_project()
        self.push_main_project()

        # Draft the upload to github
        release_notes = read_file(new_release_notes_path)
        pyperclip.copy(release_notes)
        print('The release notes are on the clipboard')
        github_url = F"https://github.com/approvals/ApprovalTests.cpp/releases/new?tag={self.details.new_version}&title=Single%20Hpp%20File%20-%20{self.details.new_version}"
        run(["open", github_url])
        run(["open", self.details.release_dir])
        check_step("that the release is published")

        # Draft the tweet
        tweet_text = F"https://twitter.com/intent/tweet?text=%23ApprovalTests.cpp+{self.details.new_version}+released%2C+now+with+___%21%0D%0Ahttps%3A%2F%2Fgithub.com%2Fapprovals%2FApprovalTests.cpp%2Freleases%2Ftag%2F{self.details.new_version}+%0D%0Aor+try+the+starter+project%3A+https%3A%2F%2Fgithub.com%2Fapprovals%2FApprovalTests.cpp.StarterProject%0D%0AThanks+%40LlewellynFalco+%40ClareMacraeUK+%21"
        run(["open", tweet_text])

    def build_hpp(self):
        self.prepare_everything()
        if not self.details.push_to_production:
            print("Everything worked - didn't commit or push")
        else:
            self.push_everything_live()

    def push_everything_live(self):
        self.commit_starter_project()
        self.push_starter_project()
        self.update_readme_and_docs()
        self.publish_main_project()
        Version.write_version(self.details.new_version)