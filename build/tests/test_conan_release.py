import os
import unittest

from scripts.conan_release import PrepareConanRelease


def set_home_directory():
    print(os.getcwd())
    os.chdir("../../ApprovalTests")
    print(os.getcwd())


class TestConanRelease(unittest.TestCase):
    def disabled_test_demo(self):
        set_home_directory()
        PrepareConanRelease.sync_conan_repo('v.8.4.1')
