<a id="top"></a>

# Supporting a new test framework

toc


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

This is perhaps best understood by reviewing the implementations for frameworks that are already supported - see [/ApprovalTests/integrations/](/ApprovalTests/integrations/).
 
The following lines can be ignored in the above files - they are for this project's release process:

```cpp
// <SingleHpp unalterable>
// </SingleHpp>
``` 

## Adding new framework to documentation

1. Add a new file about the customisation, such as [UsingCatch](/doc/UsingCatch.md#top)
2. Record the new framework support in:
    * The Help message in [ApprovalTestNamer.h](/ApprovalTests/namers/ApprovalTestNamer.h)
    * [GettingStarted](/doc/GettingStarted.md#top) - see "Details" list, and "Choosing a testing framework"
    * [User Guide](/doc/README.md#test-frameworks) - see "Test Frameworks" section
    * Other documentation links: see [Definition of Done](/doc/Contributing.md#definition-of-done)


---

[Back to User Guide](/doc/README.md#top)
