<a id="top"></a>

# Getting Started - Creating your main()


toc


## Introduction

This page shows how to set up the `main()` for test programs that use Approval Tests.

These steps are needed in order to teach Approval Tests how to name its output files automatically.

If, after following these steps, you need help with running your program, please see [Troubleshooting](/doc/Troubleshooting.md#top).

## Main File

### The Basics

You need to include 2 lines for your main file to work.

For Catch2, it's these two lines:

snippet: catch_2_main

For all other test files, you need:
``` cpp
#include "ApprovalTests.hpp"
```

### Details 

include: include_using_test_frameworks_list

## Choosing a testing framework

If you are already using one of the above testing frameworks, that is the one you should use.

If not, Approval Tests works well with all the above. Here are factors to consider.

| Framework    |  Min C++  | Ease of setup                         | IDE Support           | Build time  |
| ------------ | :-------: | ------------------------------------- | --------------------- | ----------- |
| Catch2       |   C++11   | Very easy [1], [2]                    | Widely supported      | Not bad [3] |
| doctest      |   C++11   | Very easy [1]                         | Unknown               | Fast        |
| Google Test  |   C++11   | Difficult                             | Very widely supported | Fast        |
| Boost.Test   |   C++11   | Very easy (if you already have boost) | Unknown               | Fast        |
| \[Boost\].UT | C++20 [4] | Very easy [1]                         | Unknown               | Fast        |

1. Approval Tests.cpp is [released](https://github.com/approvals/ApprovalTests.cpp/releases) as a single header file
2. See the [Starter Project](https://github.com/approvals/ApprovalTests.Cpp.StarterProject)
3. Catch2 has [options to speed up its builds](https://github.com/catchorg/Catch2/blob/master/docs/slow-compiles.md)
4. \[Boost\].UT works with C++17, but the ApprovalTests interface to that library depends on [std::source_location](https://en.cppreference.com/w/cpp/utility/source_location), which is a C++ 20 feature. 

---

[Back to User Guide](/doc/README.md#top)
