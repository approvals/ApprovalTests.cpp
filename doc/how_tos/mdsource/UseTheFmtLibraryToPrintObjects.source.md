<a id="top"></a>

# How to Use the Fmt Library To Print Objects

toc

## Introduction

[{fmt}](https://fmt.dev/) is a useful library for printing objects with many default types formatted out of the box.

## Usage

Simply use `FmtApproval::`

For example, vectors are not `ostream (<<)` printable by default. However, they are with {fmt}. so :

snippet: fmt_approvals

This will produce the following output:

snippet: FmtTests.FmtContainers.approved.txt

**note:** it is important that we included fmt before approvaltests.

snippet: fmt_includes

## Installation

### Bring your own

ApprovalTests assumes you will add the {fmt} library **before** including `ApprovalTests.hpp`. As such it makes no assumptions about fmt.

If you would like to see we added fmt to our build, check out:

snippet: fmt_cmake

[fmt/CmakeList.txt]()  

[fmt/CmakeList.txt.in]()




---

[Back to User Guide](/doc/README.md#top)
