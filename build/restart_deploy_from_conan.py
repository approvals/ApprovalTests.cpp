#! /usr/bin/env python3

from scripts.deploy_release import DeployRelease
from scripts.prepare_release import set_working_directory_and_load_current_version
from scripts.project_details import ProjectDetails
from scripts.release_details import ReleaseDetails

if __name__ == '__main__':
    project_details = ProjectDetails()
    old_version = set_working_directory_and_load_current_version(project_details.library_folder_name)
    new_version = old_version.clone()
    details = ReleaseDetails(old_version, new_version, True, project_details)
    deploy_release = DeployRelease(details)
    deploy_release.push_everything_live(start_at_conan=True)
