import unittest

from approvaltests import verify

from scripts.conan_release import PrepareConanRelease
from scripts.version import create_version
from tests.helpers import set_home_directory


class TestConanRelease(unittest.TestCase):
    def disable_test_entry_point_for_sync_conan(self):
        set_home_directory()
        # PrepareConanRelease.reset_and_clean_conan_repo()

    def test_config_yml(self):
        text = ''
        for i in range(3):
            text += PrepareConanRelease.create_conan_config_yml_text(F"1.1.{i}")
        verify(text)

    def test_conandata_yml(self):
        text = ''
        for i in range(3):
            text += PrepareConanRelease.create_conandata_yml_text(create_version(1, 1, i), "single_header_sha",
                                                                  "licence_sha")
        verify(text)
