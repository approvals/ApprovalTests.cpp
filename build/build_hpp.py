#! /usr/bin/env python3

# Constants
import os
import shutil
import pyperclip

from Utilities import run, write_file, read_file, pushdir, popdir, replace_text_in_file, check_step
import Version


class ReleaseDetails:
    def __init__(self, old_version, new_version, publish_release):
        self.old_version = Version.get_version(old_version)
        self.new_version = Version.get_version(new_version)
        self.push_to_production = publish_release

        self.old_single_header = F"ApprovalTests.{self.old_version}.hpp"
        self.new_single_header = F"ApprovalTests.{self.new_version}.hpp"

        self.build_dir = F"../build"
        self.release_dir = F"../build/releases"
        self.release_new_single_header = F"{self.release_dir}/{self.new_single_header}"

        self.main_project_dir = F"../../ApprovalTests.Cpp"
        self.starter_project_dir = F"../../ApprovalTests.Cpp.StarterProject"

class Release:
    def __init__(self, details):
        self.details = details


    # TODO copy in checks from https://github.com/pages-themes/minimal/blob/master/script/release


    def update_features_page(self):
        features_file = '../doc/mdsource/Features.source.md'
        content = read_file(features_file)
        missing_features = F"""
## v.x.y.z

## {self.details.old_version}
"""
        if missing_features in content:
            check_step("the Features page is empty: are you sure you want this?")
        else:
            update_version = F"""
## v.x.y.z

## {self.details.new_version}
"""

            replace_text_in_file(features_file, '\n## v.x.y.z\n', update_version)

    def check_pre_conditions_for_publish(self):
        if not self.details.push_to_production:
            return
        run(["git", "branch"])
        check_step("we are on the master branch")

        run(["git", "status"])
        check_step("everything is committed")
        check_step("everything is pushed")

        run(["open", "https://github.com/approvals/ApprovalTests.cpp/commits/master"])
        check_step("the builds are passing")

        run(["open", "https://github.com/approvals/ApprovalTests.cpp/blob/master/build/relnotes_X.X.X.md"])
        run(["open", "https://github.com/approvals/ApprovalTests.cpp/releases"])
        check_step("the release notes are ready")

        run(["open", "https://github.com/approvals/ApprovalTests.cpp/milestones"])
        check_step("the milestone (if any) is up to date, including actual version number of release")

        self.update_features_page()

    def create_single_header_file(self):
        os.chdir("../ApprovalTests")
        print(os.getcwd())
        run(["java", "-version"])
        run(["java", "-jar", "../build/SingleHpp.v.0.0.2.jar", self.details.release_new_single_header])
        text = read_file(self.details.release_new_single_header)
        text = F"""
    // Approval Tests version {self.details.new_version}
    // More information at: https://github.com/approvals/ApprovalTests.cpp
    
    {text}
    """
        write_file(self.details.release_new_single_header, text)


    # https://stackoverflow.com/a/10528259/104370
    # initialise a directory stack


    def update_starter_project(self):
        STARTER_PATH_OLD_SINGLE_HEADER = F"{self.details.starter_project_dir}/lib/{self.details.old_single_header}"
        STARTER_PATH_NEW_SINGLE_HEADER = F"{self.details.starter_project_dir}/lib/{self.details.new_single_header}"

        # Make sure starter project folder is clean
        pushdir(self.details.starter_project_dir)
        run(["git", "clean", "-fx"])
        run(["git", "reset", "--hard"])
        popdir()

        shutil.copyfile(self.details.release_new_single_header, STARTER_PATH_NEW_SINGLE_HEADER)

        # Delete the last release:
        if os.path.exists(STARTER_PATH_OLD_SINGLE_HEADER):
            os.remove(STARTER_PATH_OLD_SINGLE_HEADER)

        # Update the version in the "redirect" header:
        replace_text_in_file(F"{self.details.starter_project_dir}/lib/ApprovalTests.hpp", self.details.old_version, self.details.new_version)

        # Update the version number in the Visual Studio project:
        replace_text_in_file(F"{self.details.starter_project_dir}/visual-studio-2017/StarterProject.vcxproj", self.details.old_single_header,
                             self.details.new_single_header)


    def check_starter_project_builds(self):
        pushdir(F"{self.details.starter_project_dir}/cmake-build-debug")
        run(["cmake", "--build", "."])
        popdir()

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

    def update_readme_and_docs(self):
        pushdir("..")
        replace_text_in_file("mdsource/README.source.md", self.details.old_version, self.details.new_version)
        run(["./run_markdown_templates.sh"], shell=True)
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

    def prepare_everything(self):
        self.check_pre_conditions_for_publish()
        self.create_single_header_file()
        self.update_starter_project()
        self.check_starter_project_builds()

    def push_everything_live(self):
        self.commit_starter_project()
        self.push_starter_project()
        self.update_readme_and_docs()
        self.publish_main_project()
        Version.write_version(self.details.new_version)


def build(update_version):
    version = Version.load_version()
    new_version = update_version(version)
    release_details = ReleaseDetails(version, new_version, False)
    Release(release_details).build_hpp()