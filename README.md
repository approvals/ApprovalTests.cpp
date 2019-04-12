<!--
This file was generate by MarkdownSnippets.
Source File: /README.source.md
To change this file edit the source file and then re-run the generation using either the dotnet global tool (https://github.com/SimonCropp/MarkdownSnippets#githubmarkdownsnippets) or using the api (https://github.com/SimonCropp/MarkdownSnippets#running-as-a-unit-test).
-->
<a id="top"></a>

# CppApprovals



<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Contents**

- [Introduction](#introduction)
- [Getting Started](#getting-started)
- [Main File](#main-file)
- [Examples](#examples)
  - [ToString (ostream insertion)](#tostring-ostream-insertion)
  - [Suggested Examples](#suggested-examples)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## Introduction

[![Build Status](https://api.travis-ci.org/approvals/ApprovalTests.cpp.svg?branch=master)](https://travis-ci.org/approvals/ApprovalTests.cpp)

[![Build status](https://ci.appveyor.com/api/projects/status/lf3i76ije89oihi5?svg=true)](https://ci.appveyor.com/project/isidore/approvaltests-cpp)

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

Native ApprovalTests for C++

The Approvaltests library helps you write **ApprovalTests**, which are unit tests for complex objects that most people think can't be tested.

ApprovalTests are also known as **Golden Master Tests**.

Here is an intro to learn more about the [concept of ApprovalTesting](doc/ApprovalTestingConcept.md#top).

ApprovalTests are great for testing objects with lots of fields, or lists of objects.

![Intro Graphic](doc/images/ApprovalTests.cpp.IntroGraphic.gif?raw=true)

Currently working in Mac/Linux/Windows with
* [Catch1](https://github.com/catchorg/Catch2/tree/Catch1.x)  
* [Catch2](https://github.com/catchorg/Catch2)   
* [Okra](https://github.com/JayBazuzi/Okra) & C++ 11  
* [GoogleTest](https://github.com/google/googletest)



## Getting Started

The video [Quickly Testing Legacy Code](https://youtu.be/dtm8V3TIB6k) gives an introduction both to Approval Tests and to this library. The slides from the talk are available in [PowerPoint](https://www.slideshare.net/ClareMacrae/quickly-testing-legacy-code) and  [PDF](https://github.com/philsquared/cpponsea-slides/raw/master/2019/Clare%20Macrae%20-%20Quickly%20Testing%20Legacy%20Code.pdf) formats. Sample code from the talk is available on [Github](https://github.com/claremacrae/cpponsea2019).

See [Getting Started](doc/GettingStarted.md#top) and the evolving [User Guide](doc/README.md#top).

I highly suggest you clone [The Approval.cpp Starter Project](https://github.com/approvals/ApprovalTests.Cpp.StarterProject)

## Main File

You need to include 2 lines for your main file to work.

For catch (1 and 2), it's these two lines:

<!-- snippet: catch_2_main -->
```cpp
// main.cpp:
#define APPROVALS_CATCH // This tells Approval Tests to provide a main() - only do this in one cpp file
#include "ApprovalTests.hpp"
```
<sup>[snippet source](/ApprovalTests_Catch2_Tests/main.cpp#L4-L8)</sup>
<!-- endsnippet -->

For Google Test, it's these:

<!-- snippet: googletest_main -->
```cpp
// main.cpp:
#define APPROVALS_GOOGLETEST // This tells Approval Tests to provide a main() - only do this in one cpp file
#include "ApprovalTests.hpp"
```
<sup>[snippet source](/ApprovalTests_GoogleTest_Tests/main.cpp#L2-L6)</sup>
<!-- endsnippet -->

For all other test files, you need:
``` cpp
#include "ApprovalTests.hpp"
```

## Examples
ApprovalTests uses ApprovalTests to test ApprovalTests (it's turtles all the way down).  
[Checkout our own tests](https://github.com/approvals/ApprovalTests.cpp/tree/master/ApprovalTests_Catch2_Tests) to see how we do it.

### ToString (ostream insertion)
Often, you will need to create functions to allow objects to print their state. This is commonly done with on ostream `<< operator`.
You can find examples here: [To String](doc/ToString.md#top)

### Suggested Examples
* [ApprovalTests](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests_Catch2_Tests/ApprovalsTests.cpp)
* [VectorTests](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests_Catch2_Tests/VectorTests.cpp)
* [CombinationTests](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests_Catch2_Tests/CombinationTests.cpp)  


Feedback: If you have any comment or suggestion on this documentation, please email me at: isidore@setgame.com
