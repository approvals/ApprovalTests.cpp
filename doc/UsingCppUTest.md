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
    * [Existing Project - with your main()](#existing-project---with-your-main)<!-- endToc -->

## Introduction

The [CppUTest](http://cpputest.github.io/) test framework works well on most platforms with Approval Tests.

This section describes the various ways of using Approval Tests with CppUTest.

**Note:** Approval Tests has some specific build requirements if it is built with the [Ninja build generator](https://ninja-build.org/). **If you use Ninja with Approval Tests, special care is needed when setting up builds**, to avoid compilation errors or test failures. If you have any problems with this, please see [Troubleshooting Misconfigured Build](/doc/TroubleshootingMisconfiguredBuild.md#top). <!-- singleLineInclude: include_ninja_warning_note. path: /doc/include_ninja_warning_note.include.md -->

### CppUTest Integration Limitations

**Note:** This integration is not tested on CygWin. The CppUTest integration with Approval Tests does not build on this platform, CygWin, therefore our tests of it are disabled.

**Note:** Approval Tests's use of STL objects triggers test failures from CppUTest's memory-leak checking, and so our integration with CppUTest currently **turns of its memory leak checks**.

## Requirements

Approval Tests requires that the following are found:

<!-- snippet: required_headers_for_cpputest -->
<a id='snippet-required_headers_for_cpputest'></a>
```h
#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestPlugin.h>
#include <CppUTest/TestRegistry.h>
```
<sup><a href='/ApprovalTests/integrations/cpputest/CppUTestApprovals.h#L13-L17' title='Snippet source file'>snippet source</a> | <a href='#snippet-required_headers_for_cpputest' title='Start of snippet'>anchor</a></sup>
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

---

[Back to User Guide](/doc/README.md#top)
