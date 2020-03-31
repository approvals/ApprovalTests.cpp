import os
import shutil
import time
from scripts import version
from git import Repo

from scripts.utilities import read_file, check_step, replace_text_in_file, run, write_file, use_directory, \
    check_step_with_revert, calculate_sha256, assert_step


class PrepareRelease:
    def __init__(self, details):
        self.details = details

    def update_features_page(self):
        features_file = '../doc/mdsource/Features.source.md'
        content = read_file(features_file)
        update_file = PrepareRelease.prepare_update_features_page(self.details.old_version, self.details.new_version, content)
        update_file(features_file)

    @staticmethod
    def prepare_update_features_page(old_version, new_version, content):
        missing_features = F"""
## v.x.y.z

## {old_version}
"""
        if missing_features in content:
            def check(features_file, action = check_step):
                return action("the Features page is empty: are you sure you want this?")
            return check
        else:
            update_version = F"""
## v.x.y.z

## {new_version}
"""

            def replace(features_file, replace_text_in_file_action = replace_text_in_file):
                return replace_text_in_file_action(features_file, '\n## v.x.y.z\n', update_version)
            return replace

    def check_pre_conditions_for_publish(self):
        if self.details.push_to_production:
            repo = Repo(self.details.main_project_dir)
            assert_step(not repo.bare)

            assert_step((repo.active_branch.name == 'master'))

            # From https://stackoverflow.com/questions/31959425/how-to-get-staged-files-using-gitpython
            assert_step(len(repo.index.diff(None)) == 0, "there are un-committed changes to ApprovalTests.cpp")  # Modified
            assert_step(len(repo.index.diff("HEAD")) == 0, "there are un-committed changes to ApprovalTests.cpp")  # Staged

            # From https://stackoverflow.com/questions/15849640/how-to-get-count-of-unpublished-commit-with-gitpython
            assert_step(len(
                list(repo.iter_commits('master@{u}..master'))) == 0, "there are un-pushed changes in ApprovalTests.cpp")

            run(["open", "https://github.com/approvals/ApprovalTests.cpp/commits/master"])
            check_step("the builds are passing")

            run(["open", "https://github.com/approvals/ApprovalTests.cpp/blob/master/build/relnotes_x.y.z.md"])
            run(["open", F"https://github.com/approvals/ApprovalTests.cpp/compare/{self.details.old_version}...master"])
            check_step("the release notes are ready")

        run(["open", "https://github.com/approvals/ApprovalTests.cpp/issues"])
        check_step("any issues resolved in this release are closed")

        run(["open", "https://github.com/approvals/ApprovalTests.cpp/milestones"])
        check_step("the milestone (if any) is up to date, including actual version number of release")

    def update_version_number_header(self):
        with use_directory(self.details.approval_tests_dir):
            version_header = os.path.join("ApprovalTestsVersion.h")

            text = \
                F"""#ifndef APPROVALTESTS_CPP_APPROVALTESTSVERSION_H
#define APPROVALTESTS_CPP_APPROVALTESTSVERSION_H

#define APPROVALTESTS_VERSION_MAJOR {self.details.new_version_object['major']}
#define APPROVALTESTS_VERSION_MINOR {self.details.new_version_object['minor']}
#define APPROVALTESTS_VERSION_PATCH {self.details.new_version_object['patch']}
#define APPROVALTESTS_VERSION_STR "{version.get_version_without_v(self.details.new_version)}"

#define APPROVALTESTS_VERSION                                                  \\
    (APPROVALTESTS_VERSION_MAJOR * 10000 + APPROVALTESTS_VERSION_MINOR * 100 + \\
     APPROVALTESTS_VERSION_PATCH)

#endif //APPROVALTESTS_CPP_APPROVALTESTSVERSION_H
"""
            write_file(version_header, text)

    def create_single_header_file(self):
        os.chdir("../ApprovalTests")
        print(os.getcwd())
        run(["java", "-version"])
        run(["java", "-jar", "../build/SingleHpp.v.0.0.2.jar", self.details.release_new_single_header])
        text = read_file(self.details.release_new_single_header)
        text = \
F"""// Approval Tests version {self.details.new_version}
// More information at: https://github.com/approvals/ApprovalTests.cpp

{text}"""
        write_file(self.details.release_new_single_header, text)

    def update_starter_project(self):
        STARTER_PATH_OLD_SINGLE_HEADER = F"{self.details.starter_project_dir}/lib/{self.details.old_single_header}"
        STARTER_PATH_NEW_SINGLE_HEADER = F"{self.details.starter_project_dir}/lib/{self.details.new_single_header}"

        # Make sure starter project folder is clean
        with use_directory(self.details.starter_project_dir):
            # Delete untracked files:
            # - does not delete ignored files
            # - does not delete untracked files in new, untracked directories
            run(["git", "clean", "-f"])

            run(["git", "reset", "--hard"])

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
        with use_directory(F"{self.details.starter_project_dir}/cmake-build-debug"):
            run(["cmake", "--build", "."])

    def update_readme_and_docs(self):
        with use_directory(".."):
            replace_text_in_file("mdsource/README.source.md", self.details.old_version, self.details.new_version)

    def regenerate_markdown(self):
        with use_directory(".."):
            run(["./run_markdown_templates.sh"])

    def prepare_release_notes(self):
        replace_text_in_file(self.details.xxx_release_notes_path, 'v.x.y.z', self.details.new_version)
        shutil.move(self.details.xxx_release_notes_path, self.details.new_release_notes_path)

        # Make sure the above move has finished, before we create the new xxx file:
        time.sleep(1)

        shutil.copyfile(self.details.template_release_notes_path, self.details.xxx_release_notes_path)

    def add_to_git(self):
        def add():
            run(["git", "add", "."])

        self.do_things_in_starter_project_and_main(add)

    def do_things_in_starter_project_and_main(self, function):
        with use_directory(self.details.starter_project_dir):
            function()
        with use_directory(self.details.main_project_dir):
            function()

    def check_changes(self):
        def revert():
            run(["git", "clean", "-fx"])
            run(["git", "reset", "--hard"])

        def revert_all():
            self.do_things_in_starter_project_and_main(revert)

        def do_nothing():
            pass

        check_step_with_revert("you are happy with the changes?", do_nothing)


    def prepare_everything(self):
        self.check_pre_conditions_for_publish()
        self.update_version_number_header()
        self.create_single_header_file()
        self.update_starter_project()
        self.check_starter_project_builds()
        self.update_features_page()
        self.update_readme_and_docs()
        self.prepare_release_notes()
        update_conan_recipe(self.details)
        self.regenerate_markdown()
        version.write_version(self.details.new_version_object)
        self.add_to_git()

        self.check_changes()


def update_conan_recipe(details):
    check_conan_repo(details)

    new_version_with_v = details.new_version
    new_version_without_v = version.get_version_without_v(details.new_version)

    # TODO Execute or show these commands...
    # cd conan-center-index-claremacrae
    # git pull upstream master
    # git push
    # git checkout -b approvaltests.cpp.8.4.0

    check_step("Check out Conan master")
    check_step("Pull all changes in from upstream master")
    check_step(F"Create branch 'approvaltests.cpp.{new_version_without_v}', if it does not already exist")
    check_step(F"Check out branch 'approvaltests.cpp.{new_version_without_v}'")

    conan_approvaltests_dir = details.conan_approvaltests_dir

    update_conandata_yml(details, conan_approvaltests_dir, new_version_with_v, new_version_without_v)
    update_conan_config_yml(conan_approvaltests_dir, new_version_without_v)


def update_conan_config_yml(conan_approvaltests_dir, new_version_without_v):
    conan_data_file = os.path.join(conan_approvaltests_dir, 'config.yml')
    conandata_yml_text = read_file(conan_data_file)

    conan_data = \
F'''  {new_version_without_v}:
folder: all
'''
    conandata_yml_text += conan_data

    write_file(conan_data_file, conandata_yml_text)


def update_conandata_yml(details, conan_approvaltests_dir, new_version_with_v, new_version_without_v):
    conan_data_file = os.path.join(conan_approvaltests_dir, 'all', 'conandata.yml')
    conandata_yml_text = read_file(conan_data_file)

    new_single_header = details.release_new_single_header
    licence_file = '../LICENSE'

    conan_data = \
F'''  {new_version_without_v}:
- url: https://github.com/approvals/ApprovalTests.cpp/releases/download/{new_version_with_v}/ApprovalTests.{new_version_with_v}.hpp
  sha256: {calculate_sha256(new_single_header)}
- url: "https://raw.githubusercontent.com/approvals/ApprovalTests.cpp/{new_version_with_v}/LICENSE"
  sha256: {calculate_sha256(licence_file)}
'''
    conandata_yml_text += conan_data

    write_file(conan_data_file, conandata_yml_text)


def check_conan_repo(details):
    repo = Repo(details.conan_repo_dir)
    assert_step(not repo.bare)

    # TODO Add descriptions in case of failure
    assert_step((repo.active_branch.name == 'master'))

    assert_step((len(repo.index.diff(None)) == 0))  # Modified
    assert_step((len(repo.index.diff("HEAD")) == 0))  # Staged

    run(["open", "https://github.com/conan-io/conan/releases"])
    run(["conan", "--version"])
    # TODO pip3 install --upgrade conan
    check_step("you are running the latest Conan release")
