<a id="top"></a>

# Using Approval Tests With Google Tests

<!-- toc -->
## Contents

  * [Introduction](#introduction)
  * [Getting Started With Google Test](#getting-started-with-google-test)
    * [Starter Project](#starter-project)
    * [New Project](#new-project)
    * [Existing Project - no main()](#existing-project---no-main)
    * [Existing Project - with your main()](#existing-project---with-your-main)
  * [Customizing Google Tests Approval File Names](#customizing-google-tests-approval-file-names)
    * [Customizing](#customizing)
      * [Custom Suffixes](#custom-suffixes)
      * [Custom Anything](#custom-anything)
  * [Code to copy for your first Google Test Approvals test](#code-to-copy-for-your-first-google-test-approvals-test)<!-- endToc -->

## Introduction

The [Google Test](https://github.com/google/googletest) test framework works well with Approval Tests.

This section describes the various ways of using Approval Tests with Google Test.

**Notes pre-v.10.8.0:**<!-- include: include_ninja_warning_note. path: /doc/include_ninja_warning_note.include.md -->

Earlier versions of Approval Tests had issues with Ninja. Read more
at [Troubleshooting Misconfigured Build](/doc/TroubleshootingMisconfiguredBuild.md#top).<!-- endInclude -->

## Getting Started With Google Test

### Starter Project

We haven't yet provided a Starter Project for using Approval Tests with Google Tests.

This is partly based on the assumption that anyone already using Google Tests will have their own project set up, and
anyone else would probably use Catch2 instead.

If it would be helpful for us to such a Starter Project, please let us know, via the contact details
in [Contributing to ApprovalTests.cpp](/doc/Contributing.md#top).

### New Project

Create a file `main.cpp` and add just the following two lines:

<!-- snippet: googletest_main -->
<a id='snippet-googletest_main'></a>
```cpp
// main.cpp:
#define APPROVALS_GOOGLETEST // This tells Approval Tests to provide a main() - only do this in one cpp file
#include "ApprovalTests.hpp"
```
<sup><a href='/tests/GoogleTest_Tests/main.cpp#L2-L6' title='Snippet source file'>snippet source</a> | <a href='#snippet-googletest_main' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

### Existing Project - no main()

Google Test has a `gtest_main` library that provides a `main()` function, and then runs all your tests.

If your existing Google Test application uses the `gtest_main` library, Approval Tests will not be able to obtain the names to use output files. You will then see the help message shown in [Troubleshooting](/doc/Troubleshooting.md#top).

To fix this, please add a new `main.cpp`, as shown in the previous section.

### Existing Project - with your main()

If you have an existing Google Test-based test program that provides its own `main()`, you won't be able to use the approach above.

Instead, you should make the following additions to your own source file that contains `main()`.  

<!-- snippet: googletest_existing_main -->
<a id='snippet-googletest_existing_main'></a>
```cpp
// main.cpp:

// 1. Add these two lines to your main:
#define APPROVALS_GOOGLETEST_EXISTING_MAIN
#include "ApprovalTests.hpp"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    // 2. Add this line to your main:
    ApprovalTests::initializeApprovalTestsForGoogleTests();

    return RUN_ALL_TESTS();
}
```
<sup><a href='/examples/googletest_existing_main/main.cpp#L1-L17' title='Snippet source file'>snippet source</a> | <a href='#snippet-googletest_existing_main' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Customizing Google Tests Approval File Names

Most testing frameworks have two pieces of naming information: `SourceFileName` and `TestName`.

Google Tests has an additional piece of information: `TestCaseName`.
 
<!-- snippet: googletest_name_parts -->
<a id='snippet-googletest_name_parts'></a>
```cpp
TEST(TestCaseName, TestName)
```
<sup><a href='/tests/GoogleTest_Tests/namers/GoogleFixtureNamerCustomizationTests.cpp#L12-L14' title='Snippet source file'>snippet source</a> | <a href='#snippet-googletest_name_parts' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

With Google Tests, this will result in Approvals creating output files beginning with:

```text
SourceFileName.TestCaseName.TestName
```

Very often, the `SourceFileName` and the `TestCaseName` are redundant, meaning that what you would like is:

```text
SourceFileName.TestName
```

By default, Approval Tests will do this if `TestCaseName` is completely contained within `SourceFileName`, meaning it is a sub-string.

### Customizing

If this is not enough, Approvals allows for customization, in two ways.

**Note:** to be able to add these pieces of code outside of a function, you need to hold on to the result as a variable. This variable is not used, it is only there to allow the method to execute.

**Note:** using these customizations inside a Google `TEST` or `TEST_F`, is too late for that test: they won't take effect until the next executed test.

**Note:** this customization is permanent: it affects all tests run later in the current program run.

**Note:** this customization is cannot be reversed.

#### Custom Suffixes

For example, if you are Google test fixtures, you might have a lot of class names of the format `TestClassNameFixture`. You can tell Approval Tests that these are the same by adding the following to your main:

<!-- snippet: googletest_customize_suffix -->
<a id='snippet-googletest_customize_suffix'></a>
```cpp
// main.cpp
auto customization =
    ApprovalTests::GoogleConfiguration::addIgnorableTestCaseNameSuffix("Fixture");
```
<sup><a href='/tests/GoogleTest_Tests/namers/GoogleFixtureNamerCustomizationTests.cpp#L6-L10' title='Snippet source file'>snippet source</a> | <a href='#snippet-googletest_customize_suffix' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

#### Custom Anything

If you have something more unique, you can write a function that will match if the test case name and the source file names should be considered equal.

For example, let's say you want a special tag `IgnoreThis` to indicate a that a TestCaseName should be ignored, when determining the names of output files.

So:

<!-- snippet: googletest_customize_test -->
<a id='snippet-googletest_customize_test'></a>
```cpp
TEST(TestCaseName_IgnoreThis, TestName)
```
<sup><a href='/tests/GoogleTest_Tests/namers/GoogleFixtureNamerCustomizationTests.cpp#L61-L63' title='Snippet source file'>snippet source</a> | <a href='#snippet-googletest_customize_test' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Would produce an output file beginning with:

<!-- snippet: googletest_customize_test_name -->
<a id='snippet-googletest_customize_test_name'></a>
```cpp
auto outputFileBaseName = "GoogleFixtureNamerCustomizationTests.TestName";
```
<sup><a href='/tests/GoogleTest_Tests/namers/GoogleFixtureNamerCustomizationTests.cpp#L67-L69' title='Snippet source file'>snippet source</a> | <a href='#snippet-googletest_customize_test_name' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

You could achieve this by registering a function pointer like this:

<!-- snippet: googletest_customize_function -->
<a id='snippet-googletest_customize_function'></a>
```cpp
// main.cpp
bool dropTestCaseNamesWithIgnoreThis(const std::string& /*testFileNameWithExtension*/,
                                     const std::string& testCaseName)
{
    return ApprovalTests::StringUtils::contains(testCaseName, "IgnoreThis");
}

auto ignoreNames = ApprovalTests::GoogleConfiguration::addTestCaseNameRedundancyCheck(
    dropTestCaseNamesWithIgnoreThis);
```
<sup><a href='/tests/GoogleTest_Tests/namers/GoogleFixtureNamerCustomizationTests.cpp#L39-L49' title='Snippet source file'>snippet source</a> | <a href='#snippet-googletest_customize_function' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Or by using a lambda like this:

<!-- snippet: googletest_customize_lambda -->
<a id='snippet-googletest_customize_lambda'></a>
```cpp
// main.cpp
auto ignoreNamesLambda =
    ApprovalTests::GoogleConfiguration::addTestCaseNameRedundancyCheck(
        [](const std::string& /*testFileNameWithExtension*/,
           const std::string& testCaseName) {
            return ApprovalTests::StringUtils::contains(testCaseName, "IgnoreThis");
        });
```
<sup><a href='/tests/GoogleTest_Tests/namers/GoogleFixtureNamerCustomizationTests.cpp#L51-L59' title='Snippet source file'>snippet source</a> | <a href='#snippet-googletest_customize_lambda' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Code to copy for your first Google Test Approvals test

Here is sample code to create your `main()` function, to set up Approval Tests' Google Test integration.

We called this file `googletest_starter_main.cpp`:

<!-- snippet: googletest_starter_main.cpp -->
<a id='snippet-googletest_starter_main.cpp'></a>
```cpp
#define APPROVALS_GOOGLETEST
#include "ApprovalTests.hpp"

// This puts "received" and "approved" files in approval_tests/ sub-directory,
// keeping the test source directory tidy:
auto directoryDisposer =
    ApprovalTests::Approvals::useApprovalsSubdirectory("approval_tests");
```
<sup><a href='/examples/googletest_starter/googletest_starter_main.cpp#L1-L7' title='Snippet source file'>snippet source</a> | <a href='#snippet-googletest_starter_main.cpp' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Here is sample code to create your first test. We called this file `googletest_starter_test.cpp`:

<!-- snippet: googletest_starter_test.cpp -->
<a id='snippet-googletest_starter_test.cpp'></a>
```cpp
#include "gtest/gtest.h"
#include "ApprovalTests.hpp"

TEST(GoogleTestStarter, Sample)
{
    // TODO Replace 42 with the value or object whose contents you are verifying.
    // For help, see:
    // https://approvaltestscpp.readthedocs.io/en/latest/generated_docs/ToString.html
    ApprovalTests::Approvals::verify(42);
}
```
<sup><a href='/examples/googletest_starter/googletest_starter_test.cpp#L1-L10' title='Snippet source file'>snippet source</a> | <a href='#snippet-googletest_starter_test.cpp' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

And finally, here is sample code to put in your `CMakeLists.txt` file:

<!-- snippet: googletest_starter_cmake -->
<a id='snippet-googletest_starter_cmake'></a>
```txt
set(EXE_NAME googletest_starter)
set(CMAKE_CXX_STANDARD 11)
add_executable(${EXE_NAME}
        googletest_starter_main.cpp
        googletest_starter_test.cpp
        )
target_link_libraries(${EXE_NAME} ApprovalTests::ApprovalTests gtest gtest_main)

add_test(NAME ${EXE_NAME} COMMAND ${EXE_NAME})
```
<sup><a href='/examples/googletest_starter/CMakeLists.txt#L5-L15' title='Snippet source file'>snippet source</a> | <a href='#snippet-googletest_starter_cmake' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

---

[Back to User Guide](/doc/README.md#top)
