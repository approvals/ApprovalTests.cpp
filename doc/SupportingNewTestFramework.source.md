<a id="top"></a>

# Supporting a new test framework

**Contents**

<!-- vscode-markdown-toc -->
* [Introduction](#Introduction)
* [Test Framework Requirements](#TestFrameworkRequirements)
* [Steps to add support](#Stepstoaddsupport)
* [Examples](#Examples)

<!-- vscode-markdown-toc-config
	numbering=false
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->

## <a name='Introduction'></a>Introduction

ApprovalTests.cpp is designed to work with multiple C++ test frameworks.

If your test framework is not already supported, this section offers help to add that support. 

## <a name='TestFrameworkRequirements'></a>Test Framework Requirements

ApprovalTests.cpp can be made to work with any test framework that supplies the following:

* The current test's name 
* The current test's source file (with correct case of filename) 
* Ability to report unexpected exceptions as test failures 

## <a name='Stepstoaddsupport'></a>Steps to add support

* Provide some code to add to the test's `main()` function, to list out for the running of test cases
* Give that code a `TestName` instance, that will store information about the test being executed
* As each test case starts, update the `TestName` instance with details of the source file name, and test case name
* Ideally, provide a mechanism (such as a macro) that makes it easy for users to use this code in their own tests

## <a name='Examples'></a>Examples

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
