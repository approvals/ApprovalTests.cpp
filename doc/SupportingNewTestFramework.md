<a id="top"></a>

# Supporting a new test framework

<!-- toc -->
## Contents

  * [Introduction](#introduction)
  * [Test Framework Requirements](#test-framework-requirements)
  * [Steps to add support](#steps-to-add-support)
  * [Examples](#examples)
  * [Adding new framework to documentation](#adding-new-framework-to-documentation)
  * [Update Package Managers](#update-package-managers)<!-- endToc -->

## Introduction

ApprovalTests.cpp is designed to work with multiple C++ test frameworks.

If your test framework is not already supported, this section offers help to add that support. 

## Test Framework Requirements

ApprovalTests.cpp can be made to work with any test framework that supplies the following:

* The current test's name 
* The current test's full source file path (with correct case of filename) 
* Ability to report unexpected exceptions as test failures, including reporting the text in `exception.what()`, and ideally also the exception type.
* Ability to return a non-zero exit status from the test program if there were any unexpected exceptions.

## Steps to add support

* Provide some code to add to the test's `main()` function, to listen out for the running of test cases
* Give that code a `TestName` instance, that will store information about the test being executed
* As each test case starts, update the `TestName` instance with details of the source file name, and test case name
* Add a call to `ApprovalTests::FrameworkIntegrations::setTestPassedNotification()` so that the test framework is aware
  that a check has been executed
* Ideally, provide a mechanism (such as a macro) that makes it easy for users to use this code in their own tests

## Examples

This is perhaps best understood by reviewing the implementations for frameworks that are already supported - see [/ApprovalTests/integrations/](/ApprovalTests/integrations/).

## Adding new framework to documentation

1. Add a new file about the customisation, such as [UsingCatch.md](/doc/UsingCatch.md#top)
2. Record the new framework support in:
   * The `getMisconfiguredMainHelp()` help message in [HelpMessages.cpp](/ApprovalTests/namers/HelpMessages.cpp)
   * [README.md](/README.md#top) - see the links to supported test frameworks in the "Requirements" section
   * [include_using_test_frameworks_list.include.md](/doc/include_using_test_frameworks_list.include.md#top)
   * [GettingStarted.md](/doc/GettingStarted.md#top) - see "Choosing a testing framework"
   * [Setup.md](/doc/Setup.md#top) - see the bullet list starting "Set up your `main()`"
   * Other documentation links: see [Definition of Done](/doc/Contributing.md#definition-of-done)

## Update Package Managers

* Optionally, if the new library is supported by Conan, then update
  the  [ApprovalTests.cpp conan-center-index](https://github.com/conan-io/conan-center-index/commits/master/recipes/approvaltests.cpp)
  to add support for the new integration.

---

[Back to User Guide](/doc/README.md#top)
