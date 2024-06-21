<a id="top"></a>

# Using Approval Tests With Catch2 v3
*Note*: This is explicitly for Catch2 v3. Click [here for Catch2 v2](/doc/UsingCatch2v2.md#top).

<!-- toc -->
## Contents

  * [Introduction](#introduction)
  * [Requirements](#requirements)
  * [Getting Started With Catch2 v3](#getting-started-with-catch2-v3)
    * [Starter Project](#starter-project)
    * [New Project](#new-project)
    * [Existing Project - with your main()](#existing-project---with-your-main)
  * [Code to copy for your first Catch2 Approvals test](#code-to-copy-for-your-first-catch2-approvals-test)<!-- endToc -->

## Introduction

The [Catch2](https://github.com/catchorg/Catch2) test framework works well with Approval Tests.

This section describes the various ways of using Approval Tests with Catch2.

## Requirements

Approval Tests requires that a file called the following is found:

<!-- snippet: required_header_for_catch_2_v3 -->
<a id='snippet-required_header_for_catch_2_v3'></a>
```h
#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>
#include <catch2/catch_test_case_info.hpp>
```
<sup><a href='/ApprovalTests/integrations/catch/Catch2v3Approvals.h#L9-L14' title='Snippet source file'>snippet source</a> | <a href='#snippet-required_header_for_catch_2_v3' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Getting Started With Catch2 v3

### Starter Project

The quickest way to start experimenting with Approval Tests will soon be:

1. Download the project [ApprovalTests.cpp.StarterProject](https://github.com/approvals/ApprovalTests.cpp.StarterProject) - via the green "Clone or Download" button at the top-right of the project site.
2. Opening the project in the C++ IDE of your choice.

Each time we release a new version of Approval Tests, we update this project, so it always has the latest features. 

### New Project

Create a file `main.cpp` and add just the following two lines:

<!-- snippet: catch_2_v3_main -->
<a id='snippet-catch_2_v3_main'></a>
```cpp
// main.cpp:
#define APPROVALS_CATCH2_V3 // This tells Approval Tests to provide a main() - only do this in one cpp file
#include "ApprovalTests.hpp"
```
<sup><a href='/tests/Catch2v3_Tests/main.cpp#L4-L8' title='Snippet source file'>snippet source</a> | <a href='#snippet-catch_2_v3_main' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

<!-- todo: document use of sections -->

### Using an amalgamated release

Catch2 distributes amalgamated releases, which need a slight modification in the
`.hpp` file.

<!-- snippet: catch_2_v3_main -->
<a id='snippet-catch_2_v3_amalgam_diff></a>
```diff
diff --git a/client/thirdparty/ApprovalTests.hpp b/client/thirdparty/ApprovalTests.hpp
index 35199074..025c94e6 100644
--- a/client/thirdparty/ApprovalTests.hpp
+++ b/client/thirdparty/ApprovalTests.hpp
@@ -2235,7 +2235,7 @@ namespace ApprovalTests
 #ifdef APPROVALS_CATCH
 #define APPROVAL_TESTS_INCLUDE_CPPS
 
-#include "catch2/catch_amalgamated.hpp"
+#include <catch2/catch.hpp>
 
 //namespace ApprovalTests {
 struct Catch2ApprovalListener : Catch::TestEventListenerBase
@@ -2307,7 +2307,10 @@ CATCH_REGISTER_LISTENER(Catch2TestCommitRevert)
 #ifdef APPROVALS_CATCH2_V3
 #define APPROVAL_TESTS_INCLUDE_CPPS
 
-#include "catch2/catch_amalgamated.hpp"
+#include <catch2/reporters/catch_reporter_event_listener.hpp>
+#include <catch2/catch_test_macros.hpp>
+#include <catch2/reporters/catch_reporter_registrars.hpp>
+#include <catch2/catch_test_case_info.hpp>
 
 //namespace ApprovalTests {
 struct Catch2ApprovalListener : Catch::EventListenerBase
```
<sup><a href='/tests/Catch2v3_Tests/amalgamated.diff' title='Diff source file'>snippet source</a> | <a href='#snippet-catch_2_v3_difftitle='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

### Existing Project - with your main()

If you have [supplied your own `main()` for Catch](https://github.com/catchorg/Catch2/blob/master/docs/own-main.md#top), you will need to teach it how to supply test names to Approval Tests.

You should make the following additions to your own source file that contains `main()`.  

<!-- snippet: catch2_v3_existing_main -->
<a id='snippet-catch2_v3_existing_main'></a>
```cpp
// Add these two lines to the top of your main.cpp file:
#define APPROVALS_CATCH2_V3
#include "ApprovalTests.hpp"
#include <catch2/catch_session.hpp>
```
<sup><a href='/examples/catch2_v3_existing_main/main.cpp#L1-L6' title='Snippet source file'>snippet source</a> | <a href='#snippet-catch2_v3_existing_main' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Code to copy for your first Catch2 Approvals test

Here is sample code to create your `main()` function, to set up Approval Tests' Catch2 integration.

We called this file `catch2_v3_starter_main.cpp`:

<!-- snippet: catch2_v3_starter_main.cpp -->
<a id='snippet-catch2_v3_starter_main.cpp'></a>
```cpp
#define APPROVALS_CATCH2_V3
#include "ApprovalTests.hpp"

// This puts "received" and "approved" files in approval_tests/ sub-directory,
// keeping the test source directory tidy:
auto directoryDisposer =
    ApprovalTests::Approvals::useApprovalsSubdirectory("approval_tests");
```
<sup><a href='/examples/catch2_v3_starter/catch2_v3_starter_main.cpp#L1-L7' title='Snippet source file'>snippet source</a> | <a href='#snippet-catch2_v3_starter_main.cpp' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Here is sample code to create your first test. We called this file `catch2_v3_starter_test.cpp`:

<!-- snippet: catch2_v3_starter_test.cpp -->
<a id='snippet-catch2_v3_starter_test.cpp'></a>
```cpp
#include "catch2/catch_all.hpp"
#include "ApprovalTests.hpp"

TEST_CASE("catch2_starter sample")
{
    // TODO Replace 42 with the value or object whose contents you are verifying.
    // For help, see:
    // https://approvaltestscpp.readthedocs.io/en/latest/generated_docs/ToString.html
    ApprovalTests::Approvals::verify(42);
}
```
<sup><a href='/examples/catch2_v3_starter/catch2_v3_starter_test.cpp#L1-L10' title='Snippet source file'>snippet source</a> | <a href='#snippet-catch2_v3_starter_test.cpp' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

And finally, here is sample code to put in your `CMakeLists.txt` file:

<!-- snippet: catch2_v3_starter_cmake -->
<a id='snippet-catch2_v3_starter_cmake'></a>
```txt
set(EXE_NAME catch2_v3_starter)
set(CMAKE_CXX_STANDARD 14)
add_executable(${EXE_NAME}
        catch2_v3_starter_main.cpp
        catch2_v3_starter_test.cpp
        )
target_link_libraries(${EXE_NAME} ApprovalTests::ApprovalTests Catch2::Catch2WithMain)

add_test(NAME ${EXE_NAME} COMMAND ${EXE_NAME})
```
<sup><a href='/examples/catch2_v3_starter/CMakeLists.txt#L5-L15' title='Snippet source file'>snippet source</a> | <a href='#snippet-catch2_v3_starter_cmake' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

---

[Back to User Guide](/doc/README.md#top)
