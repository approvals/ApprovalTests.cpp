<a id="top"></a>

# ApprovalTests.cpp User Guide

toc


<!-- To get the most out of ApprovalTests, start with the Tutorial.
Once you're up and running, consider the following reference material. -->

## Introduction

* [Approval Testing (the concept)](/doc/ApprovalTestingConcept.md#top)
* What is Approval Testing?
* Why Approval Tests?
    * The Path to Approval Testing
        * Verify numbers
            * Have lots of numbers, like an array
        * Strings - turn the array of numbers in to a string
            * Those strings become long
        * Files - Golden Master
            * Managing them - coming up with names
        * Some sort of naming convention
        * Can be hard to understand what's in the files
            * Start using diff tools
        * Start creating custom methods for the things you are testing
            * verifyThing

## Setup

* Obtaining ApprovalTests.cpp
    * Get a test framework
    * Downloading the latest release
        * Adding a wrapper header
        * Renaming the header file to remove version number
    * [ApprovalTests.cpp.StarterProject](https://github.com/approvals/ApprovalTests.cpp.StarterProject)
    * Cloning repo and using CMake
* [Getting Started](/doc/GettingStarted.md#top) - setting up `main()`
* [Using Approval Tests With Catch](/doc/UsingCatch.md#top)
* [Using Approval Tests With Google Tests](/doc/UsingGoogleTests.md#top)
* [Using Approval Tests With Doctest](/doc/UsingDoctest.md#top)

## Writing Tests

* Tutorial
* Testing single objects
* Testing containers
* [Testing exceptions](/doc/TestingExceptions.md#top)
* Testing combinations - containers of containers (of containers...)
* [To String](/doc/ToString.md#top)
* Worked example of getting to 'make the thing; verify the thing' - 'do; verify'
* [Features](/doc/Features.md#top)

## Customising behaviour

* [Reporters](/doc/Reporters.md#top)
* Custom Comparators
* Writers
* Namers

## Common Challenges

* Unstable output, e.g. with Dates and Times
* Non-deterministic code
* Multiple output files per test
* Testing images
* Embedded development

## Common Scenarios

* Non-graphical environments
* Build Machines and Continuous Integration servers

## Extras

* [Videos](/doc/Videos.md#top)
* [Troubleshooting](/doc/Troubleshooting.md#top)
* 4 benefits of testing
    * Spec
    * Feedback
    * Regression
    * Granularity

## Advanced Topics

* [Supporting a new test framework](/doc/SupportingNewTestFramework.md#top)
* [Contributing to ApprovalTests.cpp](/doc/Contributing.md#top)

### Suggested Examples
* [ApprovalTests](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests_Catch2_Tests/ApprovalsTests.cpp)
* [VectorTests](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests_Catch2_Tests/VectorTests.cpp)
* [CombinationTests](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests_Catch2_Tests/CombinationTests.cpp)  