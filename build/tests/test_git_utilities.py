import unittest

from git import Repo

from scripts.conan_release_details import ConanReleaseDetails
from scripts.git_utilities import GitUtilities
from scripts.project_details import ProjectDetails
from tests.helpers import set_home_directory


class TestGitUtilities(unittest.TestCase):
    def disabled_test_entry_point_for_uncommitted_changes(self) -> None:
        set_home_directory()
        repo = Repo(ConanReleaseDetails(ProjectDetails()).conan_repo_dir)
        GitUtilities.check_no_uncommitted_changes(repo)
