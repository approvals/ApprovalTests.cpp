#! /usr/bin/env python3

# Constants
import os
import shutil

from Utilities import run, write_file, read_file, pushdir, popdir, replace_text_in_file
from Version import Version

class Release:

    def __init__(self, old_version, new_version, publish_release):
        self.LAST_VERSION = Version.get_version(old_version)
        self.VERSION = Version.get_version(new_version)
        self.PUSH_TO_PRODUCTION = publish_release


        self.OLD_SINGLE_HEADER = F"ApprovalTests.{self.LAST_VERSION}.hpp"
        self.NEW_SINGLE_HEADER = F"ApprovalTests.{self.VERSION}.hpp"

        self.RELEASE_DIR = F"../build/releases"
        self.RELEASE_NEW_SINGLE_HEADER = F"{self.RELEASE_DIR}/{self.NEW_SINGLE_HEADER}"

        self.STARTER_PROJECT_DIR = F"../../ApprovalTests.Cpp.StarterProject"


    # TODO copy in checks from https://github.com/pages-themes/minimal/blob/master/script/release


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

        if not self.PUSH_TO_PRODUCTION:
            # Don't push to production if we haven't set the version number
            print("Everything worked - didn't commit or push")
            exit(0)


    def commit_and_push_starter_project(self):
        pushdir(self.STARTER_PROJECT_DIR)
        run(["git", "add", "."])
        run(["git", "commit", "-m", F"Update to Approvals {self.VERSION}"])
        run(["git", "push", "origin", "master"])
        popdir()


    def update_readme_and_docs(self):
        pushdir("..")
        replace_text_in_file("mdsource/README.source.md", self.LAST_VERSION, self.VERSION)
        run(["./run_markdown_templates.sh"], shell=True)
        popdir()


    def publish(self):
        # Draft the tweet
        tweet_text = F"https://twitter.com/intent/tweet?text=%23ApprovalTests.cpp+{self.VERSION}+released%2C+now+with+___%21%0D%0Ahttps%3A%2F%2Fgithub.com%2Fapprovals%2FApprovalTests.cpp%2Freleases%2Ftag%2F{self.VERSION}+%0D%0Aor+try+the+starter+project%3A+https%3A%2F%2Fgithub.com%2Fapprovals%2FApprovalTests.cpp.StarterProject%0D%0AThanks+%40LlewellynFalco+%40ClareMacraeUK+%21"
        run(["open", tweet_text])

        # Draft the upload to github - do this last, so this tab appears on top
        github_url = F"https://github.com/approvals/ApprovalTests.cpp/releases/new?tag={self.VERSION}&title=Single%20Hpp%20File%20-%20{self.VERSION}"
        run(["open", github_url])

        run(["open", self.RELEASE_DIR])


    def build_hpp(self):
        self.create_single_header_file()
        self.update_starter_project()
        self.check_starter_project_builds()
        self.commit_and_push_starter_project()
        self.update_readme_and_docs()
        self.publish()
        Version.write_version(self.VERSION)

