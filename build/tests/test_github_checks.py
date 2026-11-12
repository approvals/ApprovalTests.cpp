import unittest
from typing import Dict, List, Tuple

from approvaltests.approvals import verify

from scripts.github_checks import GitHubChecks


def ci_run(name: str, status: str, conclusion: str) -> Dict[str, str]:
    return {"name": name, "status": status, "conclusion": conclusion}


class TestGitHubChecks(unittest.TestCase):
    def test_get_ci_problems(self) -> None:
        scenarios: Dict[str, List[Dict[str, str]]] = {
            "all passing": [ci_run("build", "completed", "success"), ci_run("mingw", "completed", "success")],
            "skipped counts as passing": [ci_run("build", "completed", "success"), ci_run("docs", "completed", "skipped")],
            "no runs": [],
            "still running": [ci_run("build", "in_progress", ""), ci_run("cygwin", "queued", "")],
            "failed": [ci_run("python-tests", "completed", "failure"), ci_run("mingw", "completed", "cancelled")],
        }
        text = ""
        for name, runs in scenarios.items():
            text += f"{name}:\n{GitHubChecks.get_ci_problems(runs)}\n\n"
        verify(text)

    def test_get_commit_to_check(self) -> None:
        bot = "Clang GitHub Action"
        scenarios: Dict[str, List[Tuple[str, str]]] = {
            "newest is by a person": [("aaa", "Llewellyn Falco"), ("bbb", bot)],
            "skips bot commits": [("aaa", bot), ("bbb", bot), ("ccc", "Llewellyn Falco")],
            "only bot commits": [("aaa", bot)],
            "no commits": [],
        }
        text = ""
        for name, commits in scenarios.items():
            sha, skipped = GitHubChecks.get_commit_to_check(commits)
            text += f"{name}:\ncheck '{sha}', skipped {skipped}\n\n"
        verify(text)


if __name__ == '__main__':
    unittest.main()
