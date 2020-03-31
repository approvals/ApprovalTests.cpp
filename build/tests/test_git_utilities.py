import os
import unittest

from git import Repo

from scripts.conan_release import ConanReleaseDetails
from scripts.git_utilities import GitUtilities
from tests.test_conan_release import set_home_directory


class TestGitUtilities(unittest.TestCase):
    def disabled_test_entry_point_for_uncommitted_changes(self):
        set_home_directory()
        repo = Repo(ConanReleaseDetails().conan_repo_dir)
        GitUtilities.check_no_uncommitted_changes(repo)
