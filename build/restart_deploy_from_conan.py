#! /usr/bin/env python3

import version
from deploy_release import DeployRelease
from prepare_release import PrepareRelease
from release_details import ReleaseDetails

if __name__ == '__main__':
    old_version = version.load_version()
    new_version = version.no_version_change(old_version)
    details = ReleaseDetails(old_version, new_version, True)
    deploy_release = DeployRelease(details)
    deploy_release.test_conan_and_create_pr()
    deploy_release.publish_tweet()
    deploy_release.publish_on_reddit_optionally()
