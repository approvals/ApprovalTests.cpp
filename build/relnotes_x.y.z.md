See the [v.x.y.z milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/8?closed=1) for the full list of changes.

* **Breaking changes**
    * None
* **New features**
    * Our Conan.io package now supports our Boost.Test integration (#121)
* **Bug fixes**
    * None
* **Other changes**
    * Consistent macro names
        * All our Macros now start with `APPROVAL_TESTS_`.
        * We have kept the old macros, redirecting to the new ones, for backwards compatibility.


| Old                                        | New                                       |
| ------------------------------------------ | ----------------------------------------- |
| `APPROVALTESTS_VERSION`                    | `APPROVAL_TESTS_VERSION`                  |
| `APPROVALTESTS_VERSION_MAJOR`              | `APPROVAL_TESTS_VERSION_MAJOR`            |
| `APPROVALTESTS_VERSION_MINOR`              | `APPROVAL_TESTS_VERSION_MINOR`            |
| `APPROVALTESTS_VERSION_PATCH`              | `APPROVAL_TESTS_VERSION_PATCH`            |
| `APPROVALTESTS_VERSION_STR`                | `APPROVAL_TESTS_VERSION_STR`              |
| `APPROVALS_CATCH_DISABLE_FILE_MACRO_CHECK` | `APPROVAL_TESTS_DISABLE_FILE_MACRO_CHECK` |
