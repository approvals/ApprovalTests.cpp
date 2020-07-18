import os
import shutil

from git import Repo

from scripts.git_utilities import GitUtilities
from scripts.release_details import ReleaseDetails
from scripts.utilities import assert_step, replace_text_in_file, use_directory, run


class PrepareStarterProjectRelease:
    pass


def check_pre_conditions_for_starter_project_repo(details: ReleaseDetails) -> None:
    repo = Repo(details.locations.starter_project_dir)
    assert_step(not repo.bare)
    GitUtilities.check_branch_name(repo, 'master')


def update_starter_project(details: ReleaseDetails) -> None:
    STARTER_PATH_OLD_SINGLE_HEADER = F"{details.locations.starter_project_dir}/lib/{details.old_single_header}"
    STARTER_PATH_NEW_SINGLE_HEADER = F"{details.locations.starter_project_dir}/lib/{details.new_single_header}"

    # Make sure starter project folder is clean
    project_dir = details.locations.starter_project_dir
    GitUtilities.reset_and_clean_working_directory(project_dir)

    shutil.copyfile(details.release_new_single_header, STARTER_PATH_NEW_SINGLE_HEADER)

    # Delete the last release:
    if os.path.exists(STARTER_PATH_OLD_SINGLE_HEADER):
        os.remove(STARTER_PATH_OLD_SINGLE_HEADER)
    else:
        raise RuntimeError(F"""
----------------------------------------------------------------
ERROR: Old header file does not exist:
{STARTER_PATH_OLD_SINGLE_HEADER}
Starting state of Starter Project does not match '{details.old_version.get_version_text()}'
Check whether:
1. There were uncommitted changes to version.ini in main project,
from a previous release preparation step.
2. The Starter Project repo needs pulling.
----------------------------------------------------------------

""")

    # Update the version in the "redirect" header:
    replace_text_in_file(
        F"{details.locations.starter_project_dir}/lib/{details.project_details.simulated_single_header_file}",
        details.old_version.get_version_text(),
        details.new_version.get_version_text())

    # Update the version number in the Visual Studio project:
    visual_studio_2017_sln = F"{details.locations.starter_project_dir}/visual-studio-2017/StarterProject.vcxproj"
    if os.path.isfile(visual_studio_2017_sln):
        replace_text_in_file(visual_studio_2017_sln,
                             details.old_single_header,
                             details.new_single_header)
    else:
        print(f"Info: No Visual Studio solution file: {visual_studio_2017_sln}")


def check_starter_project_builds(details: ReleaseDetails) -> None:
    with use_directory(F"{details.locations.starter_project_dir}/cmake-build-debug"):
        run(["cmake", "--build", "."])