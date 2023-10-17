<a id="top"></a>

# Using Approval Tests With doctest

<!-- toc -->
## Contents

  * [Introduction](#introduction)
  * [Requirements](#requirements)
  * [Getting Started With doctest](#getting-started-with-doctest)
    * [New Project](#new-project)
    * [Existing Project - with your main()](#existing-project---with-your-main)
  * [Code to copy for your first doctest Approvals test](#code-to-copy-for-your-first-doctest-approvals-test)<!-- endToc -->

## Introduction

The [doctest](https://github.com/onqtam/doctest) test framework works well with Approval Tests.

**Notes pre-v.10.8.0:**<!-- include: include_ninja_warning_note. path: /doc/include_ninja_warning_note.include.md -->

Earlier versions of Approval Tests had issues with Ninja. Read more
at [Troubleshooting Misconfigured Build](/doc/TroubleshootingMisconfiguredBuild.md#top).<!-- endInclude -->

Doctest is similar to Catch, but claims to give faster compilation times.

## Requirements

Approval Tests for doctest requires that a file called the following is found:

<!-- snippet: required_header_for_doctest -->
<a id='snippet-required_header_for_doctest'></a>
```h
#include <doctest/doctest.h>
```
<sup><a href='/ApprovalTests/integrations/doctest/DocTestApprovals.h#L16-L18' title='Snippet source file'>snippet source</a> | <a href='#snippet-required_header_for_doctest' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Approval Tests needs doctest version 2.3.4 or above.

## Getting Started With doctest

### New Project

Create a file `main.cpp` and add just the following two lines:

<!-- snippet: doctest_main -->
<a id='snippet-doctest_main'></a>
```cpp
// main.cpp:
#define APPROVALS_DOCTEST // This tells Approval Tests to provide a main() - only do this in one cpp file
#include "ApprovalTests.hpp"
```
<sup><a href='/tests/DocTest_Tests/main.cpp#L1-L5' title='Snippet source file'>snippet source</a> | <a href='#snippet-doctest_main' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

<!-- todo: document use of sections -->

### Existing Project - with your main()

If you have [supplied your own `main()` for doctest](https://github.com/onqtam/doctest/blob/master/doc/markdown/main.md#top), you will need to teach it how to supply test names to Approval Tests.

You should make the following additions to your own source file that contains `main()`.  

<!-- snippet: doctest_existing_main -->
<a id='snippet-doctest_existing_main'></a>
```cpp
// Add these two lines to the top of your main.cpp file:
#define APPROVALS_DOCTEST_EXISTING_MAIN
#include "ApprovalTests.hpp"
```
<sup><a href='/examples/doctest_existing_main/main.cpp#L1-L5' title='Snippet source file'>snippet source</a> | <a href='#snippet-doctest_existing_main' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Code to copy for your first doctest Approvals test

Here is sample code to create your `main()` function, to set up Approval Tests' doctest integration.

We called this file `doctest_starter_main.cpp`:

<!-- snippet: doctest_starter_main.cpp -->
<a id='snippet-doctest_starter_main.cpp'></a>
```cpp
#define APPROVALS_DOCTEST
#include "ApprovalTests.hpp"

// This puts "received" and "approved" files in approval_tests/ sub-directory,
// keeping the test source directory tidy:
auto directoryDisposer =
    ApprovalTests::Approvals::useApprovalsSubdirectory("approval_tests");
```
<sup><a href='/examples/doctest_starter/doctest_starter_main.cpp#L1-L7' title='Snippet source file'>snippet source</a> | <a href='#snippet-doctest_starter_main.cpp' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Here is sample code to create your first test. We called this file `doctest_starter_test.cpp`:

<!-- snippet: doctest_starter_test.cpp -->
<a id='snippet-doctest_starter_test.cpp'></a>
```cpp
#include "doctest/doctest.h"
#include "ApprovalTests.hpp"

TEST_CASE("doctest_starter sample")
{
    // TODO Replace 42 with the value or object whose contents you are verifying.
    // For help, see:
    // https://approvaltestscpp.readthedocs.io/en/latest/generated_docs/ToString.html
    ApprovalTests::Approvals::verify(42);
}
```
<sup><a href='/examples/doctest_starter/doctest_starter_test.cpp#L1-L10' title='Snippet source file'>snippet source</a> | <a href='#snippet-doctest_starter_test.cpp' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

And finally, here is sample code to put in your `CMakeLists.txt` file:

<!-- snippet: doctest_starter_cmake -->
<a id='snippet-doctest_starter_cmake'></a>
```txt
set(EXE_NAME doctest_starter)
set(CMAKE_CXX_STANDARD 11)
add_executable(${EXE_NAME}
        doctest_starter_main.cpp
        doctest_starter_test.cpp
        )
target_link_libraries(${EXE_NAME} ApprovalTests::ApprovalTests doctest::doctest)

add_test(NAME ${EXE_NAME} COMMAND ${EXE_NAME})
```
<sup><a href='/examples/doctest_starter/CMakeLists.txt#L5-L15' title='Snippet source file'>snippet source</a> | <a href='#snippet-doctest_starter_cmake' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

---

[Back to User Guide](/doc/README.md#top)
