<a id="top"></a>

# How to Use the Fmt Library To Print Objects

toc

## Introduction

[{fmt}](https://fmt.dev/) is a useful library for printing objects with many default types formatted out of the box.

## Usage

Simply use `FmtApprovals::`

For example, vectors are not `ostream (<<)` printable by default. However, they are with {fmt}. so :

snippet: fmt_approvals

This will produce the following output:

snippet: FmtTests.FmtContainers.approved.txt

**note:** it is important that we included fmt before approvaltests.

snippet: fmt_includes

## Installation

### Bring your own

ApprovalTests assumes you will add the {fmt} library **before** including `ApprovalTests.hpp`. As such it makes no assumptions about fmt. We suggest you read [their docs](https://fmt.dev/latest/usage.html).

If you would like to see how we added fmt to our build, check out:

snippet: fmt_cmake

[fmt/CmakeList.txt](/CMake/fmt/CMakeLists.txt)  

[fmt/CmakeList.txt.in](/CMake/fmt/CMakeLists.txt.in)

### Set as default for Approvals

If you wish, you can set FmtApprovals to be the default Approvals with the following line before including `ApprovalTests.hpp`

snippet: fmt_set_as_default


---

[Back to User Guide](/doc/README.md#top)
