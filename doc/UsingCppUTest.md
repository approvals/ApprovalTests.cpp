<a id="top"></a>

# Using Approval Tests With CppUTest

<!-- toc -->
## Contents

  * [Introduction](#introduction)
    * [CppUTest Integration Limitations](#cpputest-integration-limitations)
  * [Requirements](#requirements)
  * [Getting Started With CppUTest](#getting-started-with-cpputest)
    * [Starter Project](#starter-project)
    * [New Project](#new-project)
    * [Existing Project - with your main()](#existing-project---with-your-main)
  * [Code to copy for your first CppUTest Approvals test](#code-to-copy-for-your-first-cpputest-approvals-test)<!-- endToc -->

## Introduction

The [CppUTest](http://cpputest.github.io/) test framework works well on most platforms with Approval Tests.

This section describes the various ways of using Approval Tests with CppUTest.

---

**Notes pre-v.10.8.0:**<!-- include: include_ninja_warning_note. path: /doc/include_ninja_warning_note.include.md -->

Earlier versions of Approval Tests had issues with Ninja. Read more
at [Troubleshooting Misconfigured Build](/doc/TroubleshootingMisconfiguredBuild.md#top).<!-- endInclude -->

### CppUTest Integration Limitations

**Note:** This integration is not tested on CygWin. The CppUTest integration with Approval Tests does not build on this
platform, CygWin, therefore our tests of it are disabled.

**Note:** Approval Tests's use of STL objects triggers test failures from CppUTest's memory-leak checking, and so our
integration with CppUTest currently **turns of its memory leak checks**.

## Requirements

Approval Tests requires that the following are found:

<!-- snippet: required_headers_for_cpputest -->
<a id='snippet-required_headers_for_cpputest'></a>
```h
#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestPlugin.h>
#include <CppUTest/TestRegistry.h>
```
<sup><a href='/ApprovalTests/integrations/cpputest/CppUTestApprovals.h#L14-L18' title='Snippet source file'>snippet source</a> | <a href='#snippet-required_headers_for_cpputest' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Approval Tests is tested with CppUTest v4.0. 

## Getting Started With CppUTest

### Starter Project

We haven't yet provided a Starter Project for using Approval Tests with CppUTest.

This is partly based on the assumption that anyone already using CppUTest will have their own project set up, and anyone
else would probably use Catch2 instead.

If it would be helpful for us to such a Starter Project, please let us know, via the contact details
in [Contributing to ApprovalTests.cpp](/doc/Contributing.md#top).

### New Project

Create a file `main.cpp` and add just the following two lines:

<!-- snippet: cpputest_main -->
<a id='snippet-cpputest_main'></a>
```cpp
#define APPROVALS_CPPUTEST
#include "ApprovalTests.hpp"
```
<sup><a href='/tests/CppUTest_Tests/main.cpp#L1-L4' title='Snippet source file'>snippet source</a> | <a href='#snippet-cpputest_main' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

### Existing Project - with your main()

If you have an existing CppUTest-based test program that provides its own `main()`, you won't be able to use the
approach above.

Instead, you should make the following additions to your own source file that contains `main()`.

<!-- snippet: cpputest_existing_main -->
<a id='snippet-cpputest_existing_main'></a>
```cpp
// main.cpp:

// 1. Add these two lines to your main:
#define APPROVALS_CPPUTEST_EXISTING_MAIN
#include "ApprovalTests.hpp"

int main(int argc, char** argv)
{
    // 2. Add this line to your main:
    ApprovalTests::initializeApprovalTestsForCppUTest();

    int result = CommandLineTestRunner::RunAllTests(argc, argv);
    TestRegistry::getCurrentRegistry()->resetPlugins();
    return result;
}
```
<sup><a href='/examples/cpputest_existing_main/main.cpp#L1-L17' title='Snippet source file'>snippet source</a> | <a href='#snippet-cpputest_existing_main' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Code to copy for your first CppUTest Approvals test

Here is sample code to create your `main()` function, to set up Approval Tests' CppUTest integration.

We called this file `cpputest_starter_main.cpp`:

<!-- snippet: cpputest_starter_main.cpp -->
<a id='snippet-cpputest_starter_main.cpp'></a>
```cpp
#define APPROVALS_CPPUTEST
#include "ApprovalTests.hpp"

// This puts "received" and "approved" files in approval_tests/ sub-directory,
// keeping the test source directory tidy:
auto directoryDisposer =
    ApprovalTests::Approvals::useApprovalsSubdirectory("approval_tests");
```
<sup><a href='/examples/cpputest_starter/cpputest_starter_main.cpp#L1-L7' title='Snippet source file'>snippet source</a> | <a href='#snippet-cpputest_starter_main.cpp' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Here is sample code to create your first test. We called this file `cpputest_starter_test.cpp`:

<!-- snippet: cpputest_starter_test.cpp -->
<a id='snippet-cpputest_starter_test.cpp'></a>
```cpp
#include "ApprovalTests.hpp"
#include "CppUTest/TestHarness.h"

TEST_GROUP(CppUTestStarter){};

TEST(CppUTestStarter, Sample)
{
    // TODO Replace 42 with the value or object whose contents you are verifying.
    // For help, see:
    // https://approvaltestscpp.readthedocs.io/en/latest/generated_docs/ToString.html
    ApprovalTests::Approvals::verify(42);
}
```
<sup><a href='/examples/cpputest_starter/cpputest_starter_test.cpp#L1-L12' title='Snippet source file'>snippet source</a> | <a href='#snippet-cpputest_starter_test.cpp' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

And finally, here is sample code to put in your `CMakeLists.txt` file:

<!-- snippet: cpputest_starter_cmake -->
<a id='snippet-cpputest_starter_cmake'></a>
```txt
set(EXE_NAME cpputest_starter)
set(CMAKE_CXX_STANDARD 11)
add_executable(${EXE_NAME}
        cpputest_starter_main.cpp
        cpputest_starter_test.cpp
        )
target_link_libraries(${EXE_NAME} ApprovalTests::ApprovalTests CppUTest)

add_test(NAME ${EXE_NAME} COMMAND ${EXE_NAME})
```
<sup><a href='/examples/cpputest_starter/CMakeLists.txt#L5-L15' title='Snippet source file'>snippet source</a> | <a href='#snippet-cpputest_starter_cmake' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

---

[Back to User Guide](/doc/README.md#top)
