# Process for Fixing Bugs

STARTER_CHARACTER = 🐞

When fixing a bug reported in an issue, follow these steps:

**Ask for the bug number.**

## 1. Understand the Bug
- Thoroughly read the issue description and any related comments to understand the problem, expected behavior, and actual behavior.
- Read the issue via the GitHub CLI:
  ```sh
  gh issue view <number> --json body
  ```

## 2. Write a Failing Test
- Create a new test case or modify an existing one in the relevant test suite.
- The test should specifically target the scenario described in the bug report and fail with the current codebase, clearly demonstrating the bug (e.g., throwing the specific exception, producing incorrect output).
- Run the tests to verify the bug is present.

## 3. Implement the Fix
- Modify the necessary source code file(s) to correct the bug.
- Focus on addressing the root cause identified by the failing test.

## 4. Verify the Fix
- Run the tests.
- Confirm that the previously failing test now passes.
- Ensure **all** other tests continue to pass, verifying no regressions were introduced.

## 5. Refactor and Commit the Changes
- Clean up and refactor code if needed.
- Commit your changes with a clear message referencing the bug number.

* Remove unneeded comments, improve variable names and run tests to confirm refactorings.
* Use the Arlo Commit Notation (`<Risk Symbol> B <Title>`). Typically, the risk symbol will be `-` (Tested) if you wrote a unit test.
* Reference the fixed issue number in the commit message body (e.g., `Fixes #<issue_number>`).
