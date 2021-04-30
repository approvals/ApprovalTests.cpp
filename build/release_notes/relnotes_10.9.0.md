<!-- See the [v.10.9.0 milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/__MILESTONE_NUMBER__?closed=1) for the full list of changes. -->

* **Breaking changes**
    * None
* **New features**
    * Custom template namer: see [TemplatedCustomNamer](/doc/Namers.md#templatedcustomnamer). (#149)
      * This gives great flexibility 
      * It also introduces the ability to run Approval Tests on machines that do not have the source code, such as when doing cross-compilation.
    * `Options.withNamer()`: [Options](/doc/Options.md#top) now has the ability to specify a custom namer.
    * New `Path` utility class: see [Path.h](/ApprovalTests/utilities/Path.h) and [Path.cpp](/ApprovalTests/utilities/Path.cpp)
* **Bug fixes**
    * Calls to `Approvals::verify()` and related methods no longer spuriously pass if the received and approved
      filenames are identical (#178)
    * `TextDiffReporter` no longer throws when reporting that files differ.
        * This improves the content of logs when running Approval Tests in CI builds. (#106)
    * ApprovalTests.cpp's tests and examples should now never be built when used as a sub-project. (#179)
* **Other changes**
    * Added new documentation sections:
        * [Code to copy for your first Boost.Test Approvals test](/doc/UsingBoostTest.md#code-to-copy-for-your-first-boosttest-approvals-test)
        * [Code to copy for your first Catch2 Approvals test](/doc/UsingCatch.md#code-to-copy-for-your-first-catch2-approvals-test)
        * [Code to copy for your first CppUTest Approvals test](/doc/UsingCppUTest.md#code-to-copy-for-your-first-cpputest-approvals-test)
        * [Code to copy for your first doctest Approvals test](/doc/UsingDoctest.md#code-to-copy-for-your-first-doctest-approvals-test)
        * [Code to copy for your first Google Test Approvals test](/doc/UsingGoogleTests.md#code-to-copy-for-your-first-google-test-approvals-test)
        * [Code to copy for your first \[Boost\].UT Approvals test](/doc/UsingUT.md#code-to-copy-for-your-first-boostut-approvals-test)
    * Removed CI builds for clang and gcc < v9
    * Some of our internal tests now use [gulrak's filesystem](https://github.com/gulrak/filesystem). Thanks @gulrak!