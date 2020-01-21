#! /usr/bin/env python3

# Constants
import os
import shutil

from Utilities import run, write_file, read_file, pushdir, popdir, replace_text_in_file
import Version


def check_step(step):
    print("\nCHECK: ", step)
    response = input("  Press Y OR y to continue; Anything else to Quit: ")
    if response not in ['Y', 'y']:
        exit(0)


class Release:

    def __init__(self, old_version, new_version, publish_release):
        self.LAST_VERSION = Version.get_version(old_version)
        self.VERSION = Version.get_version(new_version)
        self.PUSH_TO_PRODUCTION = publish_release


        self.OLD_SINGLE_HEADER = F"ApprovalTests.{self.LAST_VERSION}.hpp"
        self.NEW_SINGLE_HEADER = F"ApprovalTests.{self.VERSION}.hpp"

        self.RELEASE_DIR = F"../build/releases"
        self.RELEASE_NEW_SINGLE_HEADER = F"{self.RELEASE_DIR}/{self.NEW_SINGLE_HEADER}"

        self.MAIN_PROJECT_DIR = F"../../ApprovalTests.Cpp"
        self.STARTER_PROJECT_DIR = F"../../ApprovalTests.Cpp.StarterProject"


    # TODO copy in checks from https://github.com/pages-themes/minimal/blob/master/script/release


    def update_features_page(self):
        features_file = '../doc/mdsource/Features.source.md'
        content = read_file(features_file)
        missing_features = F"""
## v.x.y.z

## {self.LAST_VERSION}
"""
        if missing_features in content:
            check_step("the Features page is empty: are you sure you want this?")
        else:
            update_version = F"""
## v.x.y.z

## {self.VERSION}
"""

            replace_text_in_file(features_file, '\n## v.x.y.z\n', update_version)

    def check_pre_conditions_for_publish(self):
        if not self.PUSH_TO_PRODUCTION:
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
        run(["java", "-jar", "../build/SingleHpp.v.0.0.2.jar", self.RELEASE_NEW_SINGLE_HEADER])
        text = read_file(self.RELEASE_NEW_SINGLE_HEADER)
        text = F"""
    // Approval Tests version {self.VERSION}
    // More information at: https://github.com/approvals/ApprovalTests.cpp
    
    {text}
    """
        write_file(self.RELEASE_NEW_SINGLE_HEADER, text)


    # https://stackoverflow.com/a/10528259/104370
    # initialise a directory stack


    def update_starter_project(self):
        STARTER_PATH_OLD_SINGLE_HEADER = F"{self.STARTER_PROJECT_DIR}/lib/{self.OLD_SINGLE_HEADER}"
        STARTER_PATH_NEW_SINGLE_HEADER = F"{self.STARTER_PROJECT_DIR}/lib/{self.NEW_SINGLE_HEADER}"

        # Make sure starter project folder is clean
        pushdir(self.STARTER_PROJECT_DIR)
        run(["git", "clean", "-fx"])
        run(["git", "reset", "--hard"])
        popdir()

        shutil.copyfile(self.RELEASE_NEW_SINGLE_HEADER, STARTER_PATH_NEW_SINGLE_HEADER)

        # Delete the last release:
        if os.path.exists(STARTER_PATH_OLD_SINGLE_HEADER):
            os.remove(STARTER_PATH_OLD_SINGLE_HEADER)

        # Update the version in the "redirect" header:
        replace_text_in_file(F"{self.STARTER_PROJECT_DIR}/lib/ApprovalTests.hpp", self.LAST_VERSION, self.VERSION)

        # Update the version number in the Visual Studio project:
        replace_text_in_file(F"{self.STARTER_PROJECT_DIR}/visual-studio-2017/StarterProject.vcxproj", self.OLD_SINGLE_HEADER,
                             self.NEW_SINGLE_HEADER)


    def check_starter_project_builds(self):
        pushdir(F"{self.STARTER_PROJECT_DIR}/cmake-build-debug")
        run(["cmake", "--build", "."])
        popdir()

    def commit_starter_project(self):
        pushdir(self.STARTER_PROJECT_DIR)
        run(["git", "add", "."])
        run(["git", "commit", "-m", F"Update to Approvals {self.VERSION}"])
        popdir()

    def push_starter_project(self):
        pushdir(self.STARTER_PROJECT_DIR)
        run(["git", "push", "origin", "master"])
        popdir()

    def commit_main_project(self):
        pushdir(self.MAIN_PROJECT_DIR)
        run(["git", "add", "."])
        run(["git", "commit", "-m", F"{self.VERSION} release"])
        popdir()

    def push_main_project(self):
        pushdir(self.MAIN_PROJECT_DIR)
        run(["git", "push", "origin", "master"])
        popdir()

    def update_readme_and_docs(self):
        pushdir("..")
        replace_text_in_file("mdsource/README.source.md", self.LAST_VERSION, self.VERSION)
        run(["./run_markdown_templates.sh"], shell=True)
        popdir()


    def publish_main_project(self):
        self.commit_main_project()
        self.push_main_project()

        # Draft the tweet
        tweet_text = F"https://twitter.com/intent/tweet?text=%23ApprovalTests.cpp+{self.VERSION}+released%2C+now+with+___%21%0D%0Ahttps%3A%2F%2Fgithub.com%2Fapprovals%2FApprovalTests.cpp%2Freleases%2Ftag%2F{self.VERSION}+%0D%0Aor+try+the+starter+project%3A+https%3A%2F%2Fgithub.com%2Fapprovals%2FApprovalTests.cpp.StarterProject%0D%0AThanks+%40LlewellynFalco+%40ClareMacraeUK+%21"
        run(["open", tweet_text])

        # Draft the upload to github - do this last, so this tab appears on top
        github_url = F"https://github.com/approvals/ApprovalTests.cpp/releases/new?tag={self.VERSION}&title=Single%20Hpp%20File%20-%20{self.VERSION}"
        run(["open", github_url])

        run(["open", self.RELEASE_DIR])


    def build_hpp(self):
        self.check_pre_conditions_for_publish()
        self.create_single_header_file()
        self.update_starter_project()
        self.check_starter_project_builds()
        if not self.PUSH_TO_PRODUCTION:
            print("Everything worked - didn't commit or push")
        else:
            self.push_everything_live()

    def push_everything_live(self):
        self.commit_starter_project()
        self.push_starter_project()
        self.update_readme_and_docs()
        self.publish_main_project()
        Version.write_version(self.VERSION)


def build(update_version):
    version = Version.load_version()
    new_version = update_version(version)
    Release(version, new_version, False).build_hpp()