import unittest

from git import Repo

from scripts.conan_release import ConanReleaseDetails
from scripts.git_utilities import GitUtilities
from scripts.release_details import ReleaseDetails
from scripts.utilities import run
from scripts.version import create_version
from tests.test_conan_release import set_home_directory


class TestGitUtilities(unittest.TestCase):
    def disabled_test_entry_point_for_uncommitted_changes(self):
        set_home_directory()
        repo = Repo(ConanReleaseDetails().conan_repo_dir)
        GitUtilities.check_no_uncommitted_changes(repo)



 def disabled_test_entry_point_generating_single_hpp(self):
        set_home_directory()
        details = ReleaseDetails(create_version(1,1,1),create_version(1,1,2), False);
        for a in range(1,1000):
            run(["java", "-jar", "../build/SingleHpp.v.0.0.2.jar", details.release_new_single_header])

