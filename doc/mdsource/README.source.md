<a id="top"></a>

# ApprovalTests.cpp User Guide

toc


<!-- To get the most out of ApprovalTests, start with the Tutorial.
Once you're up and running, consider the following reference material. -->

## Introduction

* [Overview](/doc/Overview.md#top)
* [Approval Testing (the concept)](/doc/ApprovalTestingConcept.md#top)
* What is Approval Testing?
* Why Approval Tests?
* [The Path to Approval Testing](/doc/PathToApprovalTesting.md#top)
* Glossary

## Setup

There are three different places you might be starting your setup from.

Here's how to set up from:

* [I have nothing](/doc/Setup.md#i-have-nothing)
* [I have code, but no tests](/doc/Setup.md#i-have-code,-but-no-tests)
* [I have tests and code, and want to add Approval Tests](/doc/Setup.md#i-have-tests-and-code,-and-want-to-add-approval-tests)

## Supported Frameworks

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
* [Custom Comparators](/doc/CustomComparators.md#top)
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

## Suggested Examples
* [ApprovalTests](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests_Catch2_Tests/ApprovalsTests.cpp)
* [VectorTests](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests_Catch2_Tests/VectorTests.cpp)
* [CombinationTests](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests_Catch2_Tests/CombinationTests.cpp)  