<a id="top"></a>

# Using Approval Tests With \[Boost\].UT


toc


## Requirements

Approval Tests for \[Boost\].UT requires that a file called the following is found:

snippet: required_header_for_ut

It also requires:

* A C++ compiler that supports the C++ 20 [`std::source_location`](https://en.cppreference.com/w/cpp/utility/source_location). See [C++ compiler support](https://en.cppreference.com/w/cpp/compiler_support).
* A build that enables C++20 - for example, with: `set(CMAKE_CXX_STANDARD 20)`
* A \[Boost\].UT version that is compatible with the version of ApprovalTests.cpp being used. See the version we test against: 
[third_party/ut/include/boost/ut.hpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/third_party/ut/include/boost/ut.hpp)

## Getting Started With \[Boost\].UT

The [\[Boost\].UT](https://github.com/boost-experimental/ut) test framework works well with Approval Tests.

\[Boost\].UT is a single header/single module, macro-free μ(micro)/Unit Testing Framework that requires C++17 / C++20

include: include_ninja_warning_note

## Usage examples

Add the following two lines to your source code:

snippet: ut_main

Below is an example of a call to an approval test inside a \[Boost\].UT test:

snippet: ut_main_usage

In the following example, two instances of ApprovalTests are called inside the same test. We need to use sections with different names, to prevent Approval Tests from using the same output file for both tests:

snippet: ut_main_multiple

---

[Back to User Guide](/doc/README.md#top)
