#! /usr/bin/env python3

from scripts import version
from scripts.conan_release import DeployConanRelease
from scripts.deploy_release import DeployRelease
from scripts.prepare_release import load_current_version
from scripts.release_details import ReleaseDetails

if __name__ == '__main__':
    old_version = load_current_version()
    new_version = old_version.clone()
    details = ReleaseDetails(old_version, new_version, True)
    deploy_release = DeployRelease(details)
    deploy_release.push_everything_live(start_at_conan=True)
