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

For catch (1 and 2), it's these two lines:

snippet: catch_2_main

For all other test files, you need:
``` cpp
#include "ApprovalTests.hpp"
```

### Details 

* [Catch 1 and 2](/doc/UsingCatch.md#getting-started-with-catch-1-and-2)
* [Google Test](/doc/UsingGoogleTests.md#getting-started-with-google-test)
* [doctest](/doc/UsingDoctest.md#getting-started-with-doctest)

## Choosing a testing framework

If you are already using one of the above testing frameworks, that is the one you should use.

If not, Approval Tests works well with all the above. Here are factors to consider.

| Framework | Ease of setup | IDE Integration | Compile and link time |
| --- | --- | --- | --- |
| Catch | Very easy (single-header). [StarterProject](https://github.com/approvals/ApprovalTests.Cpp.StarterProject) | Widely supported | Not bad - has options to speed up |
| doctest | Very easy (single-header) | Unknown | Fast |
| Google Test | Difficult (requires | Very widely supported | Fast |

---

[Back to User Guide](/doc/README.md#top)
