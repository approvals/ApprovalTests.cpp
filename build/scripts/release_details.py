import os

from scripts import version
from scripts.prepare_release import PrepareRelease
from scripts.deploy_release import DeployRelease

# TODO list
# Add CI step to check this prepare process works on every push
# Rewrite the SingleHpp Java program in Python
# Automate the check_steps
# Improve the chdir to start at the top-level directory - and check that we are the top-level
# Review folder structure for Python scripts
# Add a reminder to close any release milestone
from scripts.release_constants import release_constants


class ReleaseDetails:
    def __init__(self, old_version, new_version, publish_release):
        self.old_version = version.get_version_text(old_version)
        self.new_version = version.get_version_text(new_version)
        self.new_version_object = new_version
        self.push_to_production = publish_release

        self.old_single_header = F"ApprovalTests.{self.old_version}.hpp"
        self.new_single_header = F"ApprovalTests.{self.new_version}.hpp"

        self.release_new_single_header = F"{release_constants.release_dir}/{self.new_single_header}"

        self.new_release_notes_path = os.path.join(release_constants.release_notes_dir,
                                                   F'relnotes_{version.get_version_without_v(self.new_version)}.md')


def build(update_version, deploy):
    old_version = version.load_version('.')
    new_version = update_version(old_version)
    os.chdir("../ApprovalTests")

    release_details = ReleaseDetails(old_version, new_version, deploy)
    prepare_release = PrepareRelease(release_details)
    prepare_release.prepare_everything()
    if not release_details.push_to_production:
        print("Everything worked - didn't commit or push")
    else:
        deploy_release = DeployRelease(release_details)
        deploy_release.push_everything_live()
