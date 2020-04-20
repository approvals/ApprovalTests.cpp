import os

# TODO list
# Add CI step to check this prepare process works on every push
# Automate the check_steps
# Improve the chdir to start at the top-level directory - and check that we are the top-level
# Review folder structure for Python scripts
# Add a reminder to close any release milestone
from scripts.release_constants import release_constants
from scripts.version import Version


class ReleaseDetails:
    def __init__(self, old_version: Version, new_version: Version, publish_release: bool) -> None:
        self.old_version = old_version
        self.new_version = new_version
        self.push_to_production = publish_release

        self.old_single_header = F"ApprovalTests.{old_version.get_version_text()}.hpp"
        self.new_single_header = F"ApprovalTests.{new_version.get_version_text()}.hpp"

        self.release_new_single_header = F"{release_constants.release_dir}/{self.new_single_header}"

        self.new_release_notes_path = os.path.join(release_constants.release_notes_dir,
                                                   F'relnotes_{new_version.get_version_text_without_v()}.md')

    def old_version_as_text(self) -> str:
        return self.old_version.get_version_text()

    def new_version_as_text(self) -> str:
        return self.new_version.get_version_text()
