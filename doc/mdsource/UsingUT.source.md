<a id="top"></a>

# Using Approval Tests With \[Boost\].UT


toc


## Getting Started With \[Boost\].UT

The [\[Boost\].UT](https://github.com/boost-experimental/ut) test framework works well with Approval Tests.

\[Boost\].UT is a single header/single module, macro-free μ(micro)/Unit Testing Framework that requires C++17 / C++20

### Requirements

Approval Tests for \[Boost\].UT requires that a file called the following is found:

snippet: required_header_for_ut

Approval Tests needs \[Boost\].UT version [b970a20](https://github.com/boost-experimental/ut/commit/b970a201aa88f087a997eed05bc4c1aae3592cd3) or above.

### Usage examples

Add the following two lines to your source code:

snippet: ut_main

Below is an example of a call to an approval test inside a \[Boost\].UT test:

snippet: ut_main_usage

In the following example, two instances of ApprovalTests are called inside the same test. We need to use sections with different names, to prevent Approval Tests from using the same output file for both tests:

snippet: ut_main_multiple

---

[Back to User Guide](/doc/README.md#top)
