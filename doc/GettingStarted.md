<a id="top"></a>

# Getting Started - Creating your main()

<!-- toc -->
## Contents

  * [Introduction](#introduction)
  * [Main File](#main-file)
    * [The Basics](#the-basics)
    * [Details](#details)
  * [Choosing a testing framework](#choosing-a-testing-framework)<!-- endToc -->

## Introduction

This page shows how to set up the `main()` for test programs that use Approval Tests.

These steps are needed in order to teach Approval Tests how to name its output files automatically.

If, after following these steps, you need help with running your program, please see [Troubleshooting](/doc/Troubleshooting.md#top).

## Main File

### The Basics

You need to include 2 lines for your main file to work.

For Catch2, it's these two lines:

<!-- snippet: catch_2_main -->
<a id='snippet-catch_2_main'></a>
```cpp
// main.cpp:
#define APPROVALS_CATCH // This tells Approval Tests to provide a main() - only do this in one cpp file
#include "ApprovalTests.hpp"
```
<sup><a href='/tests/Catch2_Tests/main.cpp#L6-L10' title='Snippet source file'>snippet source</a> | <a href='#snippet-catch_2_main' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

For all other test files, you need:
``` cpp
#include "ApprovalTests.hpp"
```

### Details 

* [Using Approval Tests With Catch](/doc/UsingCatch.md#top)<!-- include: include_using_test_frameworks_list. path: /doc/include_using_test_frameworks_list.include.md -->
* [Using Approval Tests With CppUTest](/doc/UsingCppUTest.md#top)
* [Using Approval Tests With Google Tests](/doc/UsingGoogleTests.md#top)
* [Using Approval Tests With Doctest](/doc/UsingDoctest.md#top)
* [Using Approval Tests With Boost.Test](/doc/UsingBoostTest.md#top)
* [Using Approval Tests With \[Boost\].UT](/doc/UsingUT.md#top)<!-- endInclude -->

## Choosing a testing framework

If you are already using one of the above testing frameworks, that is the one you should use.

If not, Approval Tests works well with all the above. Here are factors to consider.

| Framework    |  Min C++  | Ease of setup      | IDE Support           | Build time  |
| ------------ | :-------: | ------------------ | --------------------- | ----------- |
| Catch2       |   C++11   | Very easy [1], [2] | Widely supported      | Not bad [3] |
| CppUTest     |   C++11   | Difficult          | Unknown               | Very Fast   |
| doctest      |   C++11   | Very easy [1]      | Unknown               | Fast        |
| Google Test  |   C++11   | Difficult          | Very widely supported | Fast        |
| Boost.Test   |   C++11   | Difficult          | Unknown               | Fast        |
| \[Boost\].UT | C++20 [4] | Very easy [1]      | Unknown               | Fast        |

1. Released as a single header file
2. See the [Starter Project](https://github.com/approvals/ApprovalTests.Cpp.StarterProject)
3. Catch2 has [options to speed up its builds](https://github.com/catchorg/Catch2/blob/master/docs/slow-compiles.md#top)
4. \[Boost\].UT works with C++17, but the ApprovalTests interface to that library depends on [std::source_location](https://en.cppreference.com/w/cpp/utility/source_location), which is a C++ 20 feature. 

---

[Back to User Guide](/doc/README.md#top)
