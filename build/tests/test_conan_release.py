import unittest

# from scripts.conan_release import PrepareConanRelease
from tests.helpers import set_home_directory


class TestConanRelease(unittest.TestCase):
    def disable_test_entry_point_for_sync_conan(self):
        set_home_directory()
        # PrepareConanRelease.reset_and_clean_conan_repo()
