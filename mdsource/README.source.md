<a id="top"></a>

# CppApprovals


toc

## Introduction

[![Build Status](https://api.travis-ci.org/approvals/ApprovalTests.cpp.svg?branch=master)](https://travis-ci.org/approvals/ApprovalTests.cpp) [![Build status](https://ci.appveyor.com/api/projects/status/lf3i76ije89oihi5?svg=true)](https://ci.appveyor.com/project/isidore/approvaltests-cpp) [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

Native ApprovalTests for C++

The Approvaltests library helps you write **ApprovalTests**, which are unit tests for complex objects that most people think can't be tested.

ApprovalTests are also known as **Golden Master Tests**.

Here is an intro to learn more about the [concept of ApprovalTesting](/doc/ApprovalTestingConcept.md#top).

ApprovalTests are great for testing objects with lots of fields, or lists of objects.

## Requirements

* C++11 (or above) compiler
* Mac/Linux/Windows
* One of:  [GoogleTest](https://github.com/google/googletest), [Catch1](https://github.com/catchorg/Catch2/tree/Catch1.x), [Catch2](https://github.com/catchorg/Catch2), [doctest](https://github.com/onqtam/doctest), [Okra](https://github.com/JayBazuzi/Okra)  

## Getting Started

* Download [The Approval.cpp Starter Project](https://github.com/approvals/ApprovalTests.Cpp.StarterProject)
* Read the [Getting Started](/doc/GettingStarted.md#top) page
* Read the [User Guide](/doc/README.md#top).
* Watch the [Videos](/doc/Videos.md#top)

### ToString (ostream insertion)
Often, you will need to create functions to allow objects to print their state. This is commonly done with on ostream `<< operator`.
You can find examples here: [To String](/doc/ToString.md#top)

## Main File

You need to include 2 lines for your main file to work.

For catch (1 and 2), it's these two lines:

snippet: catch_2_main

For all other test files, you need:
``` cpp
#include "ApprovalTests.hpp"
```

For other frameworks, check out our [Getting Started](/doc/GettingStarted.md#top) page. 




Feedback: If you have any comment or suggestion on this documentation, please email me at: llewellyn.falco@gmail.com