#! /usr/bin/env python3

# Constants

import Version
from deploy_release import DeployRelease


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


def build(update_version):
    version = Version.load_version()
    new_version = update_version(version)
    release_details = ReleaseDetails(version, new_version, False)
    deploy_release = DeployRelease(release_details)
    deploy_release.prepare_everything()
    if not deploy_release.details.push_to_production:
        print("Everything worked - didn't commit or push")
    else:
        deploy_release.push_everything_live()
