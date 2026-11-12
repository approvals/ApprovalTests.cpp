<!-- See the [v.10.14.0 milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/__MILESTONE_NUMBER__?closed=1) for the full list of changes. -->

* **Breaking changes**
    * None
* **New features**
    * Doctest approvals now work across multiple dynamically loaded libraries: added `APPROVALS_DOCTEST_EXTERNAL_MAIN`, `APPROVALS_DOCTEST_EXTERNAL_MAIN_IMPLEMENTATION` and `APPROVALS_DOCTEST_LISTENER_NAME`. See [Using Approval Tests With doctest](/doc/UsingDoctest.md#multiple-dynamically-loaded-libraries)
    * The [Catch2 v3 integration](/doc/UsingCatch2v3.md) now works with Catch2 amalgamated releases - `catch_amalgamated.hpp` and `catch_amalgamated.cpp` - by defining `APPROVALS_CATCH2_V3_AMALGAMATED`. (#231)
* **Bug fixes**
    * The {fmt} integration now includes `<fmt/format.h>` itself, so it no longer fails to compile when that header was not already included. (#213)
    * Fixed undefined behaviour in the Catch2 integration, reported by sanitizers, when a section ended with no sections recorded.
    * Fixed the [Boost.UT integration](/doc/UsingUT.md) hiding the default reporter's output.
* **Other changes**
    * Approval Tests now records every approved file it checks in `.approval_tests_temp/.approved_files.log`, relative to the working directory. You may want to add `.approval_tests_temp/` to your `.gitignore`.
