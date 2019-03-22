<a id="top"></a>
# ApprovalTests.cpp User Guide

**Feedback requested!** This page is currently a proposal for how to structure the user documentation
for this library, to seek feedback on it.

**Please add any feedback or suggestions** to [Issue 8: Set up outline structure for User Guide](https://github.com/approvals/ApprovalTests.cpp/issues/8).
Thank you!

<!-- To get the most out of ApprovalTests, start with the Tutorial.
Once you're up and running, consider the following reference material. -->

## Introduction

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
    * Starter project
    * Cloning repo and using CMake
* [Getting Started](GettingStarted.md#top)
* Getting Started with Catch 1 and 2
* Getting Started with Google Test

## Writing Tests

* Tutorial
* Testing single objects
* Testing containers
* Testing combinations - containers of containers (of containers...)
* [To String](ToString.md#top)
* Worked example of getting to 'make the thing; verify the thing' - 'do; verify'
* [Features](Features.md#top)

## Customising behaviour

* Reporters
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

* [Troubleshooting](Troubleshooting.md#top)
* 4 benefits of testing
    * Spec
    * Feedback
    * Regression
    * Granularity

## Advanced Topics

* Supporting a new test framework
* Contributing to ApprovalTests.cpp
