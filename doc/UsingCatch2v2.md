<a id="top"></a>

# Using Approval Tests With Catch2 v2

*Note*: This is explicitly for Catch2 v2. Click [here for Catch2 v3](/doc/UsingCatch2v3.md#top).

<!-- toc -->
## Contents

  * [Introduction](#introduction)
  * [Requirements](#requirements)
  * [Getting Started With Catch2 v2](#getting-started-with-catch2-v2)
    * [Starter Project](#starter-project)
    * [New Project](#new-project)
    * [Existing Project - with CATCH_CONFIG_MAIN](#existing-project---with-catch_config_main)
    * [Existing Project - with your main()](#existing-project---with-your-main)
  * [Code to copy for your first Catch2 Approvals test](#code-to-copy-for-your-first-catch2-approvals-test)<!-- endToc -->

## Introduction

The [Catch2](https://github.com/catchorg/Catch2) test framework works well with Approval Tests.

This section describes the various ways of using Approval Tests with Catch2.

**Notes pre-v.10.8.0:**<!-- include: include_ninja_warning_note. path: /doc/include_ninja_warning_note.include.md -->

Earlier versions of Approval Tests had issues with Ninja. Read more
at [Troubleshooting Misconfigured Build](/doc/TroubleshootingMisconfiguredBuild.md#top).<!-- endInclude -->

## Requirements

Approval Tests requires that a file called the following is found:

<!-- snippet: required_header_for_catch -->
<a id='snippet-required_header_for_catch'></a>
```h
#include <catch2/catch.hpp>
```
<sup><a href='/ApprovalTests/integrations/catch/Catch2Approvals.h#L17-L19' title='Snippet source file'>snippet source</a> | <a href='#snippet-required_header_for_catch' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

(Before v7.0.0, it required `Catch.hpp`)

## Getting Started With Catch2 v2

### Starter Project

The quickest way to start experimenting with Approval Tests is to do the following:

*Note*: The current version of the starter project uses Catch2_v3. We are linking to a historical branch if you want to use Catch2_v2.

1. Download the project [ApprovalTests.cpp.StarterProject](https://github.com/approvals/ApprovalTests.cpp.StarterProject/tree/Catch2_v2) - via the green "Download" button at the top-right of the project site.
2. Opening the project in the C++ IDE of your choice.

Each time we release a new version of Approval Tests, we update this project, so it always has the latest features. 

### New Project

Create a file `main.cpp` and add just the following two lines:

<!-- snippet: catch_2_main -->
<a id='snippet-catch_2_main'></a>
```cpp
// main.cpp:
#define APPROVALS_CATCH // This tells Approval Tests to provide a main() - only do this in one cpp file
#include "ApprovalTests.hpp"
```
<sup><a href='/tests/Catch2_Tests/main.cpp#L6-L10' title='Snippet source file'>snippet source</a> | <a href='#snippet-catch_2_main' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

### Existing Project - with CATCH_CONFIG_MAIN

If you have a Catch2 project with your own `main.cpp` that contains the following lines, you will need to replace them with the code in the previous section.

```cpp
#define CATCH_CONFIG_MAIN // remove these lines, and replace with Approval Tests lines
#include "catch2/catch.hpp"
```

<!-- todo: document use of sections -->

### Existing Project - with your main()

If you have [supplied your own `main()` for Catch](https://github.com/catchorg/Catch2/blob/master/docs/own-main.md#top), you will need to teach it how to supply test names to Approval Tests.

You should make the following additions to your own source file that contains `main()`.  

<!-- snippet: catch_existing_main -->
<a id='snippet-catch_existing_main'></a>
```cpp
// Add these two lines to the top of your main.cpp file:
#define APPROVALS_CATCH_EXISTING_MAIN
#include "ApprovalTests.hpp"
```
<sup><a href='/examples/catch2_existing_main/main.cpp#L1-L5' title='Snippet source file'>snippet source</a> | <a href='#snippet-catch_existing_main' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Code to copy for your first Catch2 Approvals test

Here is sample code to create your `main()` function, to set up Approval Tests' Catch2 integration.

We called this file `catch2_v2_starter_main.cpp`:

<!-- snippet: catch2_v2_starter_main.cpp -->
<a id='snippet-catch2_v2_starter_main.cpp'></a>
```cpp
#define APPROVALS_CATCH
#include "ApprovalTests.hpp"

// This puts "received" and "approved" files in approval_tests/ sub-directory,
// keeping the test source directory tidy:
auto directoryDisposer =
    ApprovalTests::Approvals::useApprovalsSubdirectory("approval_tests");
```
<sup><a href='/examples/catch2_starter/catch2_v2_starter_main.cpp#L1-L7' title='Snippet source file'>snippet source</a> | <a href='#snippet-catch2_v2_starter_main.cpp' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Here is sample code to create your first test. We called this file `catch2_v2_starter_test.cpp`:

<!-- snippet: catch2_v2_starter_test.cpp -->
<a id='snippet-catch2_v2_starter_test.cpp'></a>
```cpp
#include "catch2/catch.hpp"
#include "ApprovalTests.hpp"

TEST_CASE("catch2_starter sample")
{
    // TODO Replace 42 with the value or object whose contents you are verifying.
    // For help, see:
    // https://approvaltestscpp.readthedocs.io/en/latest/generated_docs/ToString.html
    ApprovalTests::Approvals::verify(42);
}
```
<sup><a href='/examples/catch2_starter/catch2_v2_starter_test.cpp#L1-L10' title='Snippet source file'>snippet source</a> | <a href='#snippet-catch2_v2_starter_test.cpp' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

And finally, here is sample code to put in your `CMakeLists.txt` file:

<!-- snippet: catch2_v2_starter_cmake -->
<a id='snippet-catch2_v2_starter_cmake'></a>
```txt
set(EXE_NAME catch2_starter)
set(CMAKE_CXX_STANDARD 11)
add_executable(${EXE_NAME}
        catch2_v2_starter_main.cpp
        catch2_v2_starter_test.cpp
        )
target_link_libraries(${EXE_NAME} ApprovalTests::ApprovalTests Catch2v2::Catch2v2)

add_test(NAME ${EXE_NAME} COMMAND ${EXE_NAME})
```
<sup><a href='/examples/catch2_starter/CMakeLists.txt#L5-L15' title='Snippet source file'>snippet source</a> | <a href='#snippet-catch2_v2_starter_cmake' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

---

[Back to User Guide](/doc/README.md#top)
