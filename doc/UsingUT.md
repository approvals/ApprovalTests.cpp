<a id="top"></a>

# Using Approval Tests With \[Boost\].UT

<!-- toc -->
## Contents

  * [Introduction](#introduction)
  * [Requirements](#requirements)
  * [Usage examples](#usage-examples)
  * [Code to copy for your first \[Boost\].UT Approvals test](#code-to-copy-for-your-first-boostut-approvals-test)<!-- endToc -->

## Introduction

The [\[Boost\].UT](https://github.com/boost-experimental/ut) test framework works well with Approval Tests.

\[Boost\].UT is a single header/single module, macro-free μ(micro)/Unit Testing Framework that requires C++17 / C++20

**Notes pre-v.10.8.0:**<!-- include: include_ninja_warning_note. path: /doc/include_ninja_warning_note.include.md -->

Earlier versions of Approval Tests had issues with Ninja. Read more
at [Troubleshooting Misconfigured Build](/doc/TroubleshootingMisconfiguredBuild.md#top).<!-- endInclude -->

## Requirements

Approval Tests for \[Boost\].UT requires that a file called the following is found:

<!-- snippet: required_header_for_ut -->
<a id='snippet-required_header_for_ut'></a>
```h
#include <boost/ut.hpp>
```
<sup><a href='/ApprovalTests/integrations/ut/UTApprovals.h#L14-L16' title='Snippet source file'>snippet source</a> | <a href='#snippet-required_header_for_ut' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

It also requires:

* A C++ compiler that supports the C++ 20 [`std::source_location`](https://en.cppreference.com/w/cpp/utility/source_location). See [C++ compiler support](https://en.cppreference.com/w/cpp/compiler_support).
* A build that enables C++20 - for example, with: `set(CMAKE_CXX_STANDARD 20)`
* A \[Boost\].UT version that is compatible with the version of ApprovalTests.cpp being used. See the version we test against: 
  [third_party/ut/include/boost/ut.hpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/third_party/ut/include/boost/ut.hpp)

## Usage examples

Add the following two lines to your source code:

<!-- snippet: ut_main -->
<a id='snippet-ut_main'></a>
```cpp
#define APPROVALS_UT
#include "ApprovalTests.hpp"
```
<sup><a href='/tests/UT_Tests/UTApprovalTestTests.cpp#L1-L4' title='Snippet source file'>snippet source</a> | <a href='#snippet-ut_main' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Below is an example of a call to an approval test inside a \[Boost\].UT test:

<!-- snippet: ut_main_usage -->
<a id='snippet-ut_main_usage'></a>
```cpp
"ItCanVerifyAFile"_test = []() {
    ApprovalTests::Approvals::verify(
        "Approval Tests can verify text via the golden master method");
};
```
<sup><a href='/tests/UT_Tests/UTApprovalTestTests.cpp#L47-L52' title='Snippet source file'>snippet source</a> | <a href='#snippet-ut_main_usage' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

In the following example, two instances of ApprovalTests are called inside the same test. We need to use sections with different names, to prevent Approval Tests from using the same output file for both tests:

<!-- snippet: ut_main_multiple -->
<a id='snippet-ut_main_multiple'></a>
```cpp
"ItCanUseMultipleVerify"_test = []() {
    {
        // Here we simulate test sections, so that Approval Tests uses different
        // output file names for the different verify() calls.
        auto section =
            ApprovalTests::NamerFactory::appendToOutputFilename("section 1");
        ApprovalTests::Approvals::verify(
            "Approval Tests can verify text via the golden master method");
    }
    {
        auto section =
            ApprovalTests::NamerFactory::appendToOutputFilename("section 2");
        ApprovalTests::Approvals::verify(
            "Approval Tests can verify different text via "
            "the golden master method");
    }
};
```
<sup><a href='/tests/UT_Tests/UTApprovalTestTests.cpp#L59-L77' title='Snippet source file'>snippet source</a> | <a href='#snippet-ut_main_multiple' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Code to copy for your first \[Boost\].UT Approvals test

Here is sample code to create your `main()` function and your first test, to set up Approval Tests' \[Boost\].UT integration. We called this file `ut_starter_test.cpp`:

<!-- snippet: ut_starter_test.cpp -->
<a id='snippet-ut_starter_test.cpp'></a>
```cpp
#define APPROVALS_UT
#include "ApprovalTests.hpp"

int main()
{
    using namespace boost::ut;
    using namespace ApprovalTests;

    // This puts "received" and "approved" files in approval_tests/ sub-directory,
    // keeping the test source directory tidy:
    auto directory = Approvals::useApprovalsSubdirectory("approval_tests");

    "Starter"_test = []() {
        // TODO Replace 42 with the value or object whose contents you are verifying.
        // For help, see:
        // https://approvaltestscpp.readthedocs.io/en/latest/generated_docs/ToString.html
        Approvals::verify(42);
    };
}
```
<sup><a href='/examples/ut_starter/ut_starter_test.cpp#L1-L19' title='Snippet source file'>snippet source</a> | <a href='#snippet-ut_starter_test.cpp' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

And finally, here is sample code to put in your `CMakeLists.txt` file:

<!-- snippet: ut_starter_cmake -->
<a id='snippet-ut_starter_cmake'></a>
```txt
set(EXE_NAME ut_starter)

set(CMAKE_CXX_STANDARD 20)
add_executable(${EXE_NAME}
        ut_starter_test.cpp
        )
target_link_libraries(${EXE_NAME} ApprovalTests::ApprovalTests boost.ut)

add_test(NAME ${EXE_NAME} COMMAND ${EXE_NAME})
```
<sup><a href='/examples/ut_starter/CMakeLists.txt#L12-L22' title='Snippet source file'>snippet source</a> | <a href='#snippet-ut_starter_cmake' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

---

[Back to User Guide](/doc/README.md#top)
