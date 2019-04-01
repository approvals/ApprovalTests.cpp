<a id="top"></a>

# ApprovalTests.cpp User Guide

**Contents**

<!-- vscode-markdown-toc -->
* [Introduction](#Introduction)
* [Setup](#Setup)
* [Writing Tests](#WritingTests)
* [Customising behaviour](#Customisingbehaviour)
* [Common Challenges](#CommonChallenges)
* [Common Scenarios](#CommonScenarios)
* [Extras](#Extras)
* [Advanced Topics](#AdvancedTopics)

<!-- vscode-markdown-toc-config
	numbering=false
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->


<!-- To get the most out of ApprovalTests, start with the Tutorial.
Once you're up and running, consider the following reference material. -->

## <a name='Introduction'></a>Introduction

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

## <a name='Setup'></a>Setup

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

## <a name='WritingTests'></a>Writing Tests

* Tutorial
* Testing single objects
* Testing containers
* [Testing exceptions](TestingExceptions.md#top)
* Testing combinations - containers of containers (of containers...)
* [To String](ToString.md#top)
* Worked example of getting to 'make the thing; verify the thing' - 'do; verify'
* [Features](Features.md#top)

## <a name='Customisingbehaviour'></a>Customising behaviour

* Reporters
* Custom Comparators
* Writers
* Namers

## <a name='CommonChallenges'></a>Common Challenges

* Unstable output, e.g. with Dates and Times
* Non-deterministic code
* Multiple output files per test
* Testing images
* Embedded development

## <a name='CommonScenarios'></a>Common Scenarios

* Non-graphical environments
* Build Machines and Continuous Integration servers

## <a name='Extras'></a>Extras

* [Troubleshooting](Troubleshooting.md#top)
* 4 benefits of testing
    * Spec
    * Feedback
    * Regression
    * Granularity

## <a name='AdvancedTopics'></a>Advanced Topics

* [Supporting a new test framework](SupportingNewTestFramework.md#top)
* [Contributing to ApprovalTests.cpp](Contributing.md#top)
