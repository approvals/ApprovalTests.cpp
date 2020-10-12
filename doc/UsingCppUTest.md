<a id="top"></a>

# Using Approval Tests With CppUTest

<!-- toc -->
## Contents

  * [Introduction](#introduction)
  * [Getting Started With CppUTest](#getting-started-with-cpputest)
    * [Starter Project](#starter-project)
    * [New Project](#new-project)
    * [Existing Project - with your main()](#existing-project---with-your-main)<!-- endToc -->

## Introduction

The [CppUTest](http://cpputest.github.io/) test framework works well with Approval Tests.

This section describes the various ways of using Approval Tests with CppUTest.

**Note:** Approval Tests's use of STL objects triggers test failures from CppUTest's memory-leak checking, and so our integration with CppUTest currently **turns of its memory leak checks**.

**Note:** Approval Tests has some specific build requirements if it is built with
the [Ninja build generator](https://ninja-build.org/). **If you use Ninja with Approval Tests, special care is needed
when setting up builds**, to avoid compilation errors or test failures. If you have any problems with this, please
see [Troubleshooting Misconfigured Build](/doc/TroubleshootingMisconfiguredBuild.md#top)
**Note:** Approval Tests has some specific build requirements if it is built with the [Ninja build generator](https://ninja-build.org/). **If you use Ninja with Approval Tests, special care is needed when setting up builds**, to avoid compilation errors or test failures. If you have any problems with this, please see [Troubleshooting Misconfigured Build](/doc/TroubleshootingMisconfiguredBuild.md#top). <!-- singleLineInclude: include_ninja_warning_note. path: /doc/include_ninja_warning_note.include.md -->

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
<sup><a href='/tests/CppUTest_Tests/main.cpp#L1-L4' title='File snippet `cpputest_main` was extracted from'>snippet source</a> | <a href='#snippet-cpputest_main' title='Navigate to start of snippet `cpputest_main`'>anchor</a></sup>
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
<sup><a href='/examples/cpputest_existing_main/main.cpp#L1-L17' title='File snippet `cpputest_existing_main` was extracted from'>snippet source</a> | <a href='#snippet-cpputest_existing_main' title='Navigate to start of snippet `cpputest_existing_main`'>anchor</a></sup>
<!-- endSnippet -->

---

[Back to User Guide](/doc/README.md#top)
