<a id="top"></a>

# Using Approval Tests With \[Boost\].UT


<!-- toc -->
## Contents

  * [Introduction](#introduction)
  * [Requirements](#requirements)
  * [Usage examples](#usage-examples)<!-- endToc -->


## Introduction

The [\[Boost\].UT](https://github.com/boost-experimental/ut) test framework works well with Approval Tests.

\[Boost\].UT is a single header/single module, macro-free μ(micro)/Unit Testing Framework that requires C++17 / C++20

**Note:** Approval Tests has some specific build requirements if it is built with the [Ninja build generator](https://ninja-build.org/). **If you use Ninja with Approval Tests, special care is needed when setting up builds**, to avoid compilation errors or test failures. If you have any problems with this, please see [Troubleshooting Misconfigured Build](/doc/TroubleshootingMisconfiguredBuild.md#top). <!-- singleLineInclude: include_ninja_warning_note. path: /doc/mdsource/include_ninja_warning_note.include.md -->

## Requirements

Approval Tests for \[Boost\].UT requires that a file called the following is found:

<!-- snippet: required_header_for_ut -->
<a id='snippet-required_header_for_ut'></a>
```h
#include <boost/ut.hpp>
```
<sup><a href='/ApprovalTests/integrations/ut/UTApprovals.h#L13-L15' title='File snippet `required_header_for_ut` was extracted from'>snippet source</a> | <a href='#snippet-required_header_for_ut' title='Navigate to start of snippet `required_header_for_ut`'>anchor</a></sup>
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
<sup><a href='/tests/UT_Tests/UTApprovalTestTests.cpp#L1-L4' title='File snippet `ut_main` was extracted from'>snippet source</a> | <a href='#snippet-ut_main' title='Navigate to start of snippet `ut_main`'>anchor</a></sup>
<!-- endSnippet -->

Below is an example of a call to an approval test inside a \[Boost\].UT test:

<!-- snippet: ut_main_usage -->
<a id='snippet-ut_main_usage'></a>
```cpp
"ItCanVerifyAFile"_test = []() {
    Approvals::verify("Approval Tests can verify text via the golden master method");
};
```
<sup><a href='/tests/UT_Tests/UTApprovalTestTests.cpp#L48-L52' title='File snippet `ut_main_usage` was extracted from'>snippet source</a> | <a href='#snippet-ut_main_usage' title='Navigate to start of snippet `ut_main_usage`'>anchor</a></sup>
<!-- endSnippet -->

In the following example, two instances of ApprovalTests are called inside the same test. We need to use sections with different names, to prevent Approval Tests from using the same output file for both tests:

<!-- snippet: ut_main_multiple -->
<a id='snippet-ut_main_multiple'></a>
```cpp
"ItCanUseMultipleVerify"_test = []() {
    {
        // Here we simulate test sections, so that Approval Tests uses different
        // output file names for the different verify() calls.
        auto section = NamerFactory::appendToOutputFilename("section 1");
        Approvals::verify(
            "Approval Tests can verify text via the golden master method");
    }
    {
        auto section = NamerFactory::appendToOutputFilename("section 2");
        Approvals::verify("Approval Tests can verify different text via "
                          "the golden master method");
    }
};
```
<sup><a href='/tests/UT_Tests/UTApprovalTestTests.cpp#L58-L73' title='File snippet `ut_main_multiple` was extracted from'>snippet source</a> | <a href='#snippet-ut_main_multiple' title='Navigate to start of snippet `ut_main_multiple`'>anchor</a></sup>
<!-- endSnippet -->

---

[Back to User Guide](/doc/README.md#top)
