<a id="top"></a>

# Using Approval Tests With doctest


toc


## Getting Started With \[Boost\].UT

The [\[Boost\].UT](https://github.com/boost-experimental/ut) test framework works well with Approval Tests.

\[Boost\].UT is a single header/single module, macro-free μ(micro)/Unit Testing Framework that requires C++17 / C++20

### Requirements

Approval Tests for \[Boost\].UT requires that a file called `ut.hpp` is found.

Approval Tests needs \[Boost\].UT version 1.1.4 or above.

### Usage example

Add the following two lines to your source code:

snippet: ut_main

Bellow is an example of a call to an approval test inside a \[Boost\].UT test:

snippet: ut_main_usage

In the following example, two instances of ApprovalTests are called inside the same test:

snippet: ut_main_multiple

<!-- todo: document use of sections -->

---

[Back to User Guide](/doc/README.md#top)
