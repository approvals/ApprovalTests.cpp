import os

from scripts.conan_release_details import ConanReleaseDetails
from scripts.project_details import ProjectDetails
from scripts.release_constants import release_constants
from scripts.release_locations import ReleaseLocations
from scripts.utilities import ensure_directory_exists
from scripts.vcpkg_release_details import VcpkgReleaseDetails
from scripts.version import Version


class ReleaseDetails:
    def __init__(self, old_version: Version, new_version: Version, publish_release: bool,
                 project_details: ProjectDetails) -> None:
        self.project_details = project_details
        self.locations = ReleaseLocations(project_details)
        # self.conan_details = ConanReleaseDetails(project_details)
        # self.vcpkg_details = VcpkgReleaseDetails(project_details)

        self.old_version = old_version
        self.new_version = new_version
        self.push_to_production = publish_release

        self.old_single_header = F"{project_details.library_folder_name}.{old_version.get_version_text()}.hpp"
        self.new_single_header = F"{project_details.library_folder_name}.{new_version.get_version_text()}.hpp"

        ensure_directory_exists(release_constants.release_dir)
        self.release_new_single_header = F"{release_constants.release_dir}/{self.new_single_header}"

        self.new_release_notes_path = os.path.join(release_constants.release_notes_dir,
                                                   F'relnotes_{new_version.get_version_text_without_v()}.md')

    def old_version_as_text(self) -> str:
        return self.old_version.get_version_text()

    def new_version_as_text(self) -> str:
        return self.new_version.get_version_text()
