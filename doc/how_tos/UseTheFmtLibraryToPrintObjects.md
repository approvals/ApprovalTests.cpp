<a id="top"></a>

# How to Use the Fmt Library To Print Objects

<!-- toc -->
## Contents

  * [Introduction](#introduction)
  * [Usage](#usage)
  * [Installation](#installation)
    * [Bring your own](#bring-your-own)
    * [Set as default for Approvals](#set-as-default-for-approvals)<!-- endToc -->

## Introduction

[{fmt}](https://fmt.dev/) is a useful library for printing objects with many default types formatted out of the box.

## Usage

Simply use `FmtApprovals::`

For example, vectors are not `ostream (<<)` printable by default. However, they are with {fmt}. so :

<!-- snippet: fmt_approvals -->
<a id='snippet-fmt_approvals'></a>
```cpp
std::vector<int> numbers = {1, 2, 3};
ApprovalTests::FmtApprovals::verify(numbers);
```
<sup><a href='/examples/fmt_approvals_demo/FmtTests.cpp#L12-L15' title='Snippet source file'>snippet source</a> | <a href='#snippet-fmt_approvals' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

This will produce the following output:

<!-- snippet: FmtTests.FmtContainers.approved.txt -->
<a id='snippet-FmtTests.FmtContainers.approved.txt'></a>
```txt
{1, 2, 3}
```
<sup><a href='/examples/fmt_approvals_demo/approval_tests/FmtTests.FmtContainers.approved.txt#L1-L1' title='Snippet source file'>snippet source</a> | <a href='#snippet-FmtTests.FmtContainers.approved.txt' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

**note:** it is important that we included fmt before approvaltests.

<!-- snippet: fmt_includes -->
<a id='snippet-fmt_includes'></a>
```cpp
#include <fmt/ranges.h>
```
<sup><a href='/examples/fmt_approvals_demo/FmtTests.cpp#L4-L6' title='Snippet source file'>snippet source</a> | <a href='#snippet-fmt_includes' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Installation

### Bring your own

ApprovalTests assumes you will add the {fmt} library **before** including `ApprovalTests.hpp`. As such it makes no assumptions about fmt. We suggest you read [their docs](https://fmt.dev/latest/usage.html).

If you would like to see how we added fmt to our build, check out:

<!-- snippet: fmt_cmake -->
<a id='snippet-fmt_cmake'></a>
```txt
target_link_libraries(${PROJECT_NAME} fmt::fmt)
```
<sup><a href='/examples/fmt_approvals_demo/CMakeLists.txt#L13-L15' title='Snippet source file'>snippet source</a> | <a href='#snippet-fmt_cmake' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

[fmt/CmakeList.txt](/CMake/fmt/CMakeLists.txt)  

[fmt/CmakeList.txt.in](/CMake/fmt/CMakeLists.txt.in)

### Set as default for Approvals

If you wish, you can set FmtApprovals to be the default Approvals with the following line before including `ApprovalTests.hpp`

<!-- snippet: fmt_set_as_default -->
<a id='snippet-fmt_set_as_default'></a>
```h
#define APPROVAL_TESTS_DEFAULT_STREAM_CONVERTER FmtToString
```
<sup><a href='/examples/fmt_approvals_demo/FmtAsDefault.h#L3-L5' title='Snippet source file'>snippet source</a> | <a href='#snippet-fmt_set_as_default' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

---

[Back to User Guide](/doc/README.md#top)
