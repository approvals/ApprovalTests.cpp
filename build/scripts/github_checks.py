import json
import re
from typing import Dict, List, Tuple

from scripts.utilities import assert_step, run_and_capture

# Commits pushed by a workflow never trigger CI, so they have no runs to check.
FORMATTING_BOT_AUTHOR = "Clang GitHub Action"


class GitHubChecks:
    @staticmethod
    def get_commit_to_check(commits: List[Tuple[str, str]]) -> Tuple[str, List[str]]:
        """
        :param commits: (sha, author name) pairs, newest first
        :return: the newest commit not by the formatting bot, and the bot commits skipped to reach it
        """
        skipped: List[str] = []
        for sha, author in commits:
            if author != FORMATTING_BOT_AUTHOR:
                return sha, skipped
            skipped.append(sha)
        return "", skipped

    @staticmethod
    def get_ci_problems(runs: List[Dict[str, str]]) -> str:
        if len(runs) == 0:
            return "no CI runs found for this commit"
        problems = []
        for ci_run in runs:
            if ci_run['status'] != 'completed':
                problems.append(f"{ci_run['name']} is {ci_run['status']}")
            elif ci_run['conclusion'] not in ['success', 'skipped']:
                problems.append(f"{ci_run['name']} finished with {ci_run['conclusion']}")
        return "\n".join(problems)

    @staticmethod
    def check_ci_passing(github_repo: str, commits: List[Tuple[str, str]]) -> None:
        commit_sha, skipped = GitHubChecks.get_commit_to_check(commits)
        assert_step(commit_sha != "", "no commit found that was not made by the formatting bot")
        for sha in skipped:
            print(f"Skipping CI check of formatting-bot commit {sha}")
        print(f"Checking CI for {commit_sha}")
        output = run_and_capture(
            ["gh", "run", "list", "--repo", github_repo, "--commit", commit_sha, "--json", "name,status,conclusion"])
        problems = GitHubChecks.get_ci_problems(json.loads(output))
        assert_step(problems == "", f"CI is not passing for {commit_sha}:\n{problems}")

    @staticmethod
    def find_issue_numbers(release_notes: str) -> List[int]:
        return sorted(set(int(number) for number in re.findall(r"#(\d+)", release_notes)))

    @staticmethod
    def get_open_issue_problems(issues: List[Dict[str, str]]) -> str:
        problems = []
        for issue in issues:
            if issue['state'] != 'closed':
                problems.append(f"#{issue['number']} is {issue['state']}: {issue['title']}")
        return "\n".join(problems)

    @staticmethod
    def check_issues_closed(github_repo: str, release_notes: str) -> None:
        issues = []
        for number in GitHubChecks.find_issue_numbers(release_notes):
            # The issues API also covers pull requests, which release notes sometimes mention
            output = run_and_capture(["gh", "api", f"repos/{github_repo}/issues/{number}"])
            issues.append(json.loads(output))
        problems = GitHubChecks.get_open_issue_problems(issues)
        assert_step(problems == "", f"issues mentioned in the release notes are not closed:\n{problems}")
