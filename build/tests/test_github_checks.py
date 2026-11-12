import unittest
from typing import Any, Dict, List, Tuple

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

    def test_find_issue_numbers(self) -> None:
        release_notes = (
            "* **Bug fixes**\n"
            "    * Fixed the {fmt} integration (#213)\n"
            "    * Catch2 amalgamated support ([#231](https://github.com/approvals/ApprovalTests.cpp/issues/231))\n"
            "    * Same issue mentioned again (#213)\n"
        )
        verify(str(GitHubChecks.find_issue_numbers(release_notes)))

    def test_get_open_issue_problems(self) -> None:
        issues = [
            {"number": "213", "state": "open", "title": "Bug with {fmt} integration"},
            {"number": "231", "state": "closed", "title": "Catch2 v3 integration does not work with amalgamated"},
        ]
        verify(f"one open:\n{GitHubChecks.get_open_issue_problems(issues)}\n\n"
               f"all closed:\n{GitHubChecks.get_open_issue_problems(issues[1:])}\n")

    def test_get_release_problems(self) -> None:
        def release(is_draft: bool, assets: List[str]) -> Dict[str, Any]:
            return {"tagName": "v.10.14.0", "isDraft": is_draft, "assets": [{"name": name} for name in assets]}

        expected = "ApprovalTests.v.10.14.0.hpp"
        scenarios = {
            "published with header": release(False, [expected]),
            "draft": release(True, [expected]),
            "missing header": release(False, []),
        }
        text = ""
        for name, scenario in scenarios.items():
            text += f"{name}:\n{GitHubChecks.get_release_problems(scenario, expected)}\n\n"
        verify(text)


if __name__ == '__main__':
    unittest.main()
