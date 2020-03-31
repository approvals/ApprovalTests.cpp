import os
import unittest

from scripts.conan_release import PrepareConanRelease


def set_home_directory():
    print(os.getcwd())
    os.chdir("../../ApprovalTests")
    print(os.getcwd())


class TestConanRelease(unittest.TestCase):
    def disable_test_entry_point_for_sync_conan(self):
        set_home_directory()
        PrepareConanRelease.check_conan_repo()
