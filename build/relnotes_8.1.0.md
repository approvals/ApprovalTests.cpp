See the [v.8.1.0 milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/5?closed=1) for the full list of changes.

* **Breaking changes**
    * None
* **New features**
    * Added ability to detect ApprovalTests.cpp version in code: see [Version detection](/doc/Features.md#version-detection) (#40)
* **Bug fixes**
    * Relaxed the static_assert check on `__FILE__` to stop it wrongly triggering in Cygwin builds that don't define `_WIN32` (#92)
    * Fixed inability to use project as sub-module on Windows due to long filenames - by shortening the names of some files and folders in the tests. (#38)
* **Other changes**
    * Include `__FILE__` value in static_assert message, to aid diagnosis
    * Implement check for broken links in documentation (#26)
    * Fixed some broken links in documentation (#26)
