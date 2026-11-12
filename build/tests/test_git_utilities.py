import os
import tempfile
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

    def test_commit_everything_keeps_message_exactly(self) -> None:
        message = "Update to ApprovalTests.cpp v.1.2.3 - it's \"quoted\""
        with tempfile.TemporaryDirectory() as directory:
            repo = Repo.init(directory)
            repo.config_writer().set_value("user", "name", "Test").release()
            repo.config_writer().set_value("user", "email", "test@example.com").release()
            with open(os.path.join(directory, "file.txt"), "w") as f:
                f.write("text")
            GitUtilities.add_and_commit_everything(directory, message)
            self.assertEqual(message, str(repo.head.commit.message).strip())
