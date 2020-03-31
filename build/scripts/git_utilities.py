import os

from scripts.utilities import assert_step

class GitUtilities:
    @staticmethod
    def check_no_uncommitted_changes(repo):
        # From https://stackoverflow.com/questions/31959425/how-to-get-staged-files-using-gitpython
        repo_location = repo.working_dir
        repo_name = os.path.basename(repo_location)
        assert_step(len(repo.index.diff(None)) == 0, f"there are un-committed changes to {repo_name}")  # Modified
        assert_step(len(repo.index.diff("HEAD")) == 0, f"there are staged changes to {repo_name}")  # Staged
