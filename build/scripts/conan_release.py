import os

from git import Repo

from scripts import version
from scripts.utilities import check_step, read_file, write_file, calculate_sha256, assert_step, run


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