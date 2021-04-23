<a id="top"></a>

# Troubleshooting Misconfigured Main

<!-- toc -->
## Contents

  * [Symptoms](#symptoms)
    * [Linker errors about missing symbols](#linker-errors-about-missing-symbols)
    * [Error when running tests](#error-when-running-tests)
  * [Solutions](#solutions)
    * [Check the instructions for your test framework](#check-the-instructions-for-your-test-framework)
    * [Check Google Test Framework](#check-google-test-framework)
    * [Other Issues](#other-issues)<!-- endToc -->

## Symptoms

### Linker errors about missing symbols

When you link your test program - using ApprovalTest v.10.1.1 or later - you get linker errors about missing symbols, such as these:

* `ApprovalTests::FileApprover::verify(...)`
* `ApprovalTests::StringWriter::StringWriter(...)`
* `ApprovalTests::DefaultNamerFactory::getDefaultNamer()`
* `ApprovalTests::Options::defaultReporter()`
* `ApprovalTests::Scrubbers::doNothing(...)`
* `ApprovalTests::Options::FileOptions::getFileExtension() const`
* `ApprovalTests::Options::fileOptions() const`
* `ApprovalTests::Options::getReporter() const`
* `ApprovalTests::Options::scrub(...) const`

### Error when running tests

Running tests - using ApprovalTest v.10.1.0 or earlier - gives the following output:

<!-- snippet: ForgottenToConfigure.HelpMessage.approved.txt -->
<a id='snippet-ForgottenToConfigure.HelpMessage.approved.txt'></a>
```txt
*****************************************************************************
*                                                                           *
* Welcome to Approval Tests.
*
* You have forgotten to configure your test framework for Approval Tests.
*
* To do this in Catch, add the following to your main.cpp:
*
*     #define APPROVALS_CATCH
*     #include "ApprovalTests.hpp"
*
* To do this in Google Test, add the following to your main.cpp:
*
*     #define APPROVALS_GOOGLETEST
*     #include "ApprovalTests.hpp"
*
* To do this in doctest, add the following to your main.cpp:
*
*     #define APPROVALS_DOCTEST
*     #include "ApprovalTests.hpp"
*
* To do this in Boost.Test, add the following to your main.cpp:
*
*     #define APPROVALS_BOOSTTEST
*     #include "ApprovalTests.hpp"
*
* To do this in CppUTest, add the following to your main.cpp:
*
*     #define APPROVALS_CPPUTEST
*     #include "ApprovalTests.hpp"
*
* To do this in [Boost].UT, add the following to your main.cpp:
*
*     #define APPROVALS_UT
*     #include "ApprovalTests.hpp"
*
* For more information, please visit:
* https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredMain.md
*                                                                           *
*****************************************************************************
```
<sup><a href='/tests/DocTest_Tests/docs/approval_tests/ForgottenToConfigure.HelpMessage.approved.txt#L1-L40' title='Snippet source file'>snippet source</a> | <a href='#snippet-ForgottenToConfigure.HelpMessage.approved.txt' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Solutions

These are the things to check.

### Check the instructions for your test framework

Approval Tests needs to know which test framework to connect to, and that usually involves making small changes to the `main()` function for your test program.

This error usually indicates that a problem in your test program's `main()` means that ApprovalTests.cpp is not correctly set up for your test framework. 

The following resources should help:

* The text in the error message above may be enough to get you going.
* If not, see [Getting Started - Creating your main()](/doc/GettingStarted.md#top) to find out what you need to do for your chosen test framework, or to select one, if you have not yet done so.

### Check Google Test Framework

* Have you created a `main.cpp` that sets up ApprovalTests?
    * If not, the default Google Test `main()` will be used, which will not set up Approval Tests
    * To fix, copy in the non-comment code from [tests/GoogleTest_Tests/main.cpp](/tests/GoogleTest_Tests/main.cpp)
* Is your `main.cpp` included in your project's build?
    * If not, the default Google Test `main()` will be used, which will not set up Approval Tests
    * To fix, e.g. check your `CMakeLists.txt` file
* Does your Google Test have its own custom `main.cpp`?
    * If so, perhaps you haven't yet added the code to set up Approval Tests?
    * To fix, copy in the Approvals-specific lines from [examples/googletest_existing_main/main.cpp](/examples/googletest_existing_main/main.cpp)

### Other Issues

* Is your code calling `Approvals::verify()` or any other methods in this library from outside a Google Test?
    * This is much less likely to be the cause, but the file-naming code in Approval Tests (`ApprovalTestNamer`) does require that approvals are used from inside a test method in a supported test framework. 

---

[Back to User Guide](/doc/README.md#top)
