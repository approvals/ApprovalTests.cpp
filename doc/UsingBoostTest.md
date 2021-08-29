<a id="top"></a>

# Using Approval Tests With Boost.Test

<!-- toc -->
## Contents

  * [Introduction](#introduction)
  * [Requirements](#requirements)
  * [Getting Started With Boost.Test](#getting-started-with-boosttest)
    * [Adding ApprovalTests to your Boost.Test](#adding-approvaltests-to-your-boosttest)
      * [Understanding Boost.Test Entry points](#understanding-boosttest-entry-points)
  * [Code to copy for your first Boost.Test Approvals test](#code-to-copy-for-your-first-boosttest-approvals-test)<!-- endToc -->

## Introduction

The [Boost.Test](https://www.boost.org/doc/libs/1_72_0/libs/test/doc/html/index.html) test framework works well with Approval Tests.

**Note:** this document assumes the reader is familiar with the Boost.Test framework.

## Requirements

Approval Tests for Boost.Test requires that you specify the `#include <.../unit_test.hpp>`  
This allows ApprovalTests to work with all the different configurations of boost.  

Approval Tests needs Boost.Test version 1.60.0 or above.

## Getting Started With Boost.Test

### Adding ApprovalTests to your Boost.Test

To enable any Boost.Test test files to use ApprovalTests,
find the corresponding entry point and  
add the following lines of code to your [Test module's entry point](https://www.boost.org/doc/libs/1_72_0/libs/test/doc/html/boost_test/adv_scenarios/entry_point_overview.html) 
after the boost headers:

<!-- snippet: boost_test_main -->
<a id='snippet-boost_test_main'></a>
```cpp
// test_entry_point.cpp file[s] (after #including boost.test)
#define APPROVALS_BOOSTTEST
#include "ApprovalTests.hpp"
```
<sup><a href='/tests/Boost_Tests/main.cpp#L8-L12' title='Snippet source file'>snippet source</a> | <a href='#snippet-boost_test_main' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

#### Understanding Boost.Test Entry points

A directory of Boost.Test source files can either have multiple or a single entry point[s]. 
The entry point is any file that will contain the line:

<!-- snippet: boost_test_entry_point -->
<a id='snippet-boost_test_entry_point'></a>
```cpp
#define BOOST_TEST_MODULE ModuleName
```
<sup><a href='/tests/Boost_Tests/main.cpp#L1-L3' title='Snippet source file'>snippet source</a> | <a href='#snippet-boost_test_entry_point' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Code to copy for your first Boost.Test Approvals test

Here is sample code to create your `main()` function, to set up Approval Tests' Boost.Test integration.

We called this file `boost_starter_main.cpp`:

<!-- snippet: boost_starter_main.cpp -->
<a id='snippet-boost_starter_main.cpp'></a>
```cpp
#define BOOST_TEST_MODULE ModuleName

//#include <boost/test/unit_test.hpp> // static or dynamic boost build
#include <boost/test/included/unit_test.hpp> // header only boost

#define APPROVALS_BOOSTTEST
#include "ApprovalTests.hpp"

// This puts "received" and "approved" files in approval_tests/ sub-directory,
// keeping the test source directory tidy:
auto directoryDisposer =
    ApprovalTests::Approvals::useApprovalsSubdirectory("approval_tests");
```
<sup><a href='/examples/boost_starter/boost_starter_main.cpp#L1-L12' title='Snippet source file'>snippet source</a> | <a href='#snippet-boost_starter_main.cpp' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Here is sample code to create your first test. We called this file `boost_starter_test.cpp`:

<!-- snippet: boost_starter_test.cpp -->
<a id='snippet-boost_starter_test.cpp'></a>
```cpp
#define BOOST_TEST_INCLUDED
#include <boost/test/unit_test.hpp>

#include "ApprovalTests.hpp"

BOOST_AUTO_TEST_SUITE(SuiteName)
BOOST_AUTO_TEST_CASE(TestCaseName)
{
    ApprovalTests::Approvals::verify(42);
}
BOOST_AUTO_TEST_SUITE_END()
```
<sup><a href='/examples/boost_starter/boost_starter_test.cpp#L1-L11' title='Snippet source file'>snippet source</a> | <a href='#snippet-boost_starter_test.cpp' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

And finally, here is sample code to put in your `CMakeLists.txt` file:

<!-- snippet: boost_starter_cmake -->
<a id='snippet-boost_starter_cmake'></a>
```txt
set(EXE_NAME boost_starter)
set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.60.0 COMPONENTS REQUIRED)
if (NOT Boost_FOUND)
    message(FATAL_ERROR "Cannot find Boost libraries")
endif ()

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

add_executable(${EXE_NAME}
        boost_starter_main.cpp
        boost_starter_test.cpp
        )
target_link_libraries(${EXE_NAME} ApprovalTests::ApprovalTests ${Boost_LIBRARIES})

add_test(NAME ${EXE_NAME} COMMAND ${EXE_NAME})
```
<sup><a href='/examples/boost_starter/CMakeLists.txt#L16-L34' title='Snippet source file'>snippet source</a> | <a href='#snippet-boost_starter_cmake' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

---

[Back to User Guide](/doc/README.md#top)
