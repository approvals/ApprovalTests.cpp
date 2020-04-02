import os
import unittest

from scripts.conan_release import PrepareConanRelease
from scripts.utilities import get_file_name


def set_home_directory():
    current_dir = os.getcwd().replace('\\', '/')
    if current_dir.endswith('ApprovalTests.cpp/ApprovalTests'):
        return
    source_dir = os.path.split(__file__)[0]
    library_dir = os.path.join(source_dir, "../../ApprovalTests")
    os.chdir(library_dir)


class TestConanRelease(unittest.TestCase):
    def disable_test_entry_point_for_sync_conan(self):
        set_home_directory()
        # PrepareConanRelease.reset_and_clean_conan_repo()
