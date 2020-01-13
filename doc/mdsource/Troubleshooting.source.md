<a id="top"></a>

# Troubleshooting


toc


## Test gives "You have forgotten to configure your test framework..."

**Root Cause**:

A problem in your test program's `main()` means that ApprovalTests.cpp is not correctly set up for your test framework. 

**Symptom**

Running tests gives the following output:

snippet: ForgottenToConfigure.HelpMessage.approved.txt 

**Things to check:**

* Have you created a `main.cpp` that sets up ApprovalTests?
    * If not, the default Google Test `main()` will be used, which will not set up Approval Tests
    * To fix, copy in the non-comment code from [tests/GoogleTest_Tests/main.cpp](/tests/GoogleTest_Tests/main.cpp)
* Is your `main.cpp` included in your project's build?
    * If not, the default Google Test `main()` will be used, which will not set up Approval Tests
    * To fix, e.g. check your `CMakeLists.txt` file
* Does your Google Test have its own custom `main.cpp`?
    * If so, perhaps you haven't yet added the code to set up Approval Tests?
    * To fix, copy in the Approvals-specific lines from [examples/googletest_existing_main/main.cpp](/examples/googletest_existing_main/main.cpp)
* Is your code calling `Approvals::verify()` or any other methods in this library from outside a Google Test?
    * This is much less likely to be the cause, but the file-naming code in Approval Tests (`ApprovalTestNamer`) does require that approvals are used from inside a test method in a supported test framework. 

## Test gives "There seems to be a problem with your build configuration"

**Symptom 1: Compilation Error**

Compiling tests in Ninja-generated builds gives a compilation failure, with this message:

snippet: compiler_error_for_misconfigured_build

**Symptom 2: Test Failure**

Running tests in Ninja-generated builds gives output such as the following:

snippet: ForgottenToConfigure.HelpMessageForIncorrectBuildConfig.approved.txt

**Things to check:**

See [Troubleshooting Misconfigured Build](/doc/TroubleshootingMisconfiguredBuild.md#top).

## My custom reporter works in development, but not CI

Check your test code - especially your main - for any uses of `Approvals::useAsFrontLoadedReporter()` that are specific to running on a Continuous Integration system.

If that's the case, and you do still want to use a custom reporter in an individual test, you can use `Approvals::useAsFrontLoadedReporter()` in the test, passing in your custom reporter, to take precedence over the CI-specific reporter in your main.

---

[Back to User Guide](/doc/README.md#top)
