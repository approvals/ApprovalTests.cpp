<!--
This file was generate by MarkdownSnippets.
Source File: /doc/README.source.md
To change this file edit the source file and then re-run the generation using either the dotnet global tool (https://github.com/SimonCropp/MarkdownSnippets#markdownsnippetstool) or using the api (https://github.com/SimonCropp/MarkdownSnippets#running-as-a-unit-test).
-->
<a id="top"></a>

# ApprovalTests.cpp User Guide

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Contents**

- [Introduction](#introduction)
- [Setup](#setup)
- [Writing Tests](#writing-tests)
- [Customising behaviour](#customising-behaviour)
- [Common Challenges](#common-challenges)
- [Common Scenarios](#common-scenarios)
- [Extras](#extras)
- [Advanced Topics](#advanced-topics)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

<!-- To get the most out of ApprovalTests, start with the Tutorial.
Once you're up and running, consider the following reference material. -->

## Introduction

* [Approval Testing (the concept)](ApprovalTestingConcept.md#top)
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
* [Getting Started](GettingStarted.md#top) - setting up `main()`
* Getting Started with Catch 1 and 2
* Getting Started with Google Test

## Writing Tests

* Tutorial
* Testing single objects
* Testing containers
* [Testing exceptions](TestingExceptions.md#top)
* Testing combinations - containers of containers (of containers...)
* [To String](ToString.md#top)
* Worked example of getting to 'make the thing; verify the thing' - 'do; verify'
* [Features](Features.md#top)

## Customising behaviour

* [Reporters](Reporters.md#top)
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

* [Supporting a new test framework](SupportingNewTestFramework.md#top)
* [Contributing to ApprovalTests.cpp](Contributing.md#top)
