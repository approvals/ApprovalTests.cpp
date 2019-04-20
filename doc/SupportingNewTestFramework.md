<!--
This file was generate by MarkdownSnippets.
Source File: /doc/SupportingNewTestFramework.source.md
To change this file edit the source file and then re-run the generation using either the dotnet global tool (https://github.com/SimonCropp/MarkdownSnippets#markdownsnippetstool) or using the api (https://github.com/SimonCropp/MarkdownSnippets#running-as-a-unit-test).
-->
<a id="top"></a>

# Supporting a new test framework



<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Contents**

- [Introduction](#introduction)
- [Test Framework Requirements](#test-framework-requirements)
- [Steps to add support](#steps-to-add-support)
- [Examples](#examples)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## Introduction

ApprovalTests.cpp is designed to work with multiple C++ test frameworks.

If your test framework is not already supported, this section offers help to add that support. 

## Test Framework Requirements

ApprovalTests.cpp can be made to work with any test framework that supplies the following:

* The current test's name 
* The current test's source file (with correct case of filename) 
* Ability to report unexpected exceptions as test failures 

## Steps to add support

* Provide some code to add to the test's `main()` function, to list out for the running of test cases
* Give that code a `TestName` instance, that will store information about the test being executed
* As each test case starts, update the `TestName` instance with details of the source file name, and test case name
* Ideally, provide a mechanism (such as a macro) that makes it easy for users to use this code in their own tests

## Examples

This is perhaps best understood by reviewing the implementations for frameworks that are already supported:
 
* [Catch2Approvals.h](../ApprovalTests/Catch2Approvals.h)
* [GoogleTestApprovals.h](../ApprovalTests/GoogleTestApprovals.h)
* [OkraApprovals.h](../ApprovalTests/OkraApprovals.h)

The following lines can be ignored in the above files - they are for this project's release process:

```cpp
// <SingleHpp unalterable>
// </SingleHpp>
``` 

---

[Back to User Guide](README.md#top)
