import unittest

from approvaltests.approvals import verify

from scripts.conan_release import PrepareConanRelease, ConanReleaseDetails
from scripts.version import Version
from tests.helpers import set_home_directory


class TestConanRelease(unittest.TestCase):
    def disable_test_entry_point_for_sync_conan(self) -> None:
        set_home_directory()
        # PrepareConanRelease.reset_and_clean_conan_repo()

    def test_config_yml(self) -> None:
        text = ''
        for i in range(3):
            text += PrepareConanRelease.create_conan_config_yml_text(Version(1, 1, i))
        verify(text)

    def test_conandata_yml(self) -> None:
        text = ''
        for i in range(3):
            text += PrepareConanRelease.create_conandata_yml_text(Version(1, 1, i), "single_header_sha",
                                                                  "licence_sha")
        verify(text)

    def test_can_find_conan_repo(self) -> None:
        set_home_directory()
        # Validate that function does not throw exception.
        # Will fail if person running test has not cloned conan-center-index
        directory = ConanReleaseDetails.get_conan_repo_directory()
        print(directory)
