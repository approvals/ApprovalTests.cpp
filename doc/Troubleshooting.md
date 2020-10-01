<a id="top"></a>

# Troubleshooting


<!-- toc -->
## Contents

  * [Test gives "You have forgotten to configure your test framework..."](#test-gives-you-have-forgotten-to-configure-your-test-framework)
  * [Test gives "There seems to be a problem with your build configuration"](#test-gives-there-seems-to-be-a-problem-with-your-build-configuration)
  * [My custom reporter works in development, but not CI](#my-custom-reporter-works-in-development-but-not-ci)
  * [Running Catch2 tests in CLion gives 'unexpected exception'](#running-catch2-tests-in-clion-gives-unexpected-exception)<!-- endToc -->


## Test gives "You have forgotten to configure your test framework..."

**Symptom**

Running tests gives the following output:

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
<sup><a href='/tests/DocTest_Tests/docs/approval_tests/ForgottenToConfigure.HelpMessage.approved.txt#L1-L35' title='File snippet `ForgottenToConfigure.HelpMessage.approved.txt` was extracted from'>snippet source</a> | <a href='#snippet-ForgottenToConfigure.HelpMessage.approved.txt' title='Navigate to start of snippet `ForgottenToConfigure.HelpMessage.approved.txt`'>anchor</a></sup>
<!-- endSnippet -->

**Things to check:**

See [Troubleshooting Misconfigured Main](/doc/TroubleshootingMisconfiguredMain.md#top).

## Test gives "There seems to be a problem with your build configuration"

**Symptom 1: Compilation Error**

Compiling tests in Ninja-generated builds gives a compilation failure, with this message:

<!-- snippet: compiler_error_for_misconfigured_build -->
<a id='snippet-compiler_error_for_misconfigured_build'></a>
```h
"There seems to be a problem with your build configuration, probably with Ninja. "
"Please visit https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredBuild.md "
"The filename is: "
__FILE__
```
<sup><a href='/ApprovalTests/integrations/CheckFileMacroIsAbsolute.h#L21-L26' title='File snippet `compiler_error_for_misconfigured_build` was extracted from'>snippet source</a> | <a href='#snippet-compiler_error_for_misconfigured_build' title='Navigate to start of snippet `compiler_error_for_misconfigured_build`'>anchor</a></sup>
<!-- endSnippet -->

**Symptom 2: Test Failure**

Running tests in Ninja-generated builds gives output such as the following:

<!-- snippet: ForgottenToConfigure.HelpMessageForIncorrectBuildConfig.approved.txt -->
<a id='snippet-ForgottenToConfigure.HelpMessageForIncorrectBuildConfig.approved.txt'></a>
```txt
*****************************************************************************
*                                                                           *
* Welcome to Approval Tests.
*
* There seems to be a problem with your build configuration.
* We cannot find the test source file at:
*   ../../../tests/Catch2_Tests/ApprovalsTests.cpp
*
* For details on how to fix this, please visit:
* https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredBuild.md
*                                                                           *
*****************************************************************************
```
<sup><a href='/tests/DocTest_Tests/docs/approval_tests/ForgottenToConfigure.HelpMessageForIncorrectBuildConfig.approved.txt#L1-L12' title='File snippet `ForgottenToConfigure.HelpMessageForIncorrectBuildConfig.approved.txt` was extracted from'>snippet source</a> | <a href='#snippet-ForgottenToConfigure.HelpMessageForIncorrectBuildConfig.approved.txt' title='Navigate to start of snippet `ForgottenToConfigure.HelpMessageForIncorrectBuildConfig.approved.txt`'>anchor</a></sup>
<!-- endSnippet -->

**Things to check:**

See [Troubleshooting Misconfigured Build](/doc/TroubleshootingMisconfiguredBuild.md#top).

## My custom reporter works in development, but not CI

Check your test code - especially your main - for any uses of `Approvals::useAsFrontLoadedReporter()` that are specific to running on a Continuous Integration system.

If that's the case, and you do still want to use a custom reporter in an individual test, you can use `Approvals::useAsFrontLoadedReporter()` in the test, passing in your custom reporter, to take precedence over the CI-specific reporter in your main.

## Running Catch2 tests in CLion gives 'unexpected exception'

**Note: Updating to CLion 2020.2 EAP or later fixes this bug.**

----

If there are problems with code that uses Approval Tests, or test failures, the library takes care to issue helpful information via the text in an exception (via `exception.what()`). This text is then displayed by the test framework.

However, some Catch2 users have reported not always seeing these messages, and instead seeing output like:

```
.../TestFileName.cpp:32: Failure:
unexpected exception
```

This turns out to be due to a bug in CLion's Catch2 plugin: [Catch2 unexpected exception instead of detailed message](https://youtrack.jetbrains.com/issue/CPP-11919).

There are various options to work around this:

* Try updating CLion or reviewing the linked ticket above, to see if the CLion problem has been fixed.
* Run the test executable in a console window, instead of in CLion, to see what the error is, and fix it.
* Use CLion's "Edit Configurations" to run the test program as a "CMake Application" instead of via the "Catch" test runner.

---

[Back to User Guide](/doc/README.md#top)
