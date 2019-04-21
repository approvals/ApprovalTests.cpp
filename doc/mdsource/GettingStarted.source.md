<a id="top"></a>

# Getting Started - Creating your main()



<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Contents**

- [Introduction](#introduction)
- [Catch 1 and 2](#catch-1-and-2)
  - [Starter Project](#starter-project)
  - [New Project](#new-project)
  - [Existing Project - with CATCH_CONFIG_MAIN](#existing-project---with-catch_config_main)
  - [Existing Project - with your main()](#existing-project---with-your-main)
- [Google Test](#google-test)
  - [Starter Project](#starter-project-1)
  - [New Project](#new-project-1)
  - [Existing Project - no main()](#existing-project---no-main)
  - [Existing Project - with your main()](#existing-project---with-your-main-1)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## Introduction

This page shows how to set up the `main()` for test programs that use Approval Tests.

These steps are needed in order to teach Approval Tests how to name its output files automatically.

If, after following these steps, you need help with running your program, please see [Troubleshooting](Troubleshooting.md#top).

## Catch 1 and 2

The [Catch2](https://github.com/catchorg/Catch2) test framework works well with Approval Tests.

This section describes the various ways of using Approval Tests with Catch 2.

These steps also work with the earlier version, Catch 1, which is on the [Catch 1.x branch](https://github.com/catchorg/Catch2/tree/Catch1.x), and is still provided for those on pre-C++11 compilers. (Please note that the Approval Tests library requires C++11 or newer, however). 

### Starter Project

The quickest way to start experimenting with Approval Tests is to:

1. Download the project [ApprovalTests.cpp.StarterProject](https://github.com/approvals/ApprovalTests.cpp.StarterProject) - via the green "Clone or Download" button at the top-right of the project site.
2. Opening the project in the C++ IDE of your choice.

Each time we release a new version of Approval Tests, we update this project, so it always has the latest features. 

### New Project

Create a file `main.cpp` and add just the following two lines:

snippet: catch_2_main

### Existing Project - with CATCH_CONFIG_MAIN

If you have a Catch (1 or 2) project with your own `main.cpp` that contains the following lines, you will need to replace them with the code in the previous section.

```cpp
#define CATCH_CONFIG_MAIN // remove these lines, and replace with Approval Tests lines
#include "catch.hpp"
```

### Existing Project - with your main()

If you have [supplied your own `main()` for Catch](https://github.com/catchorg/Catch2/blob/master/docs/own-main.md#top), you will need to teach it how to supply test names to Approval Tests.

There is not yet a streamlined way of doing this.

For now, please see the code in [ApprovalTests/Catch2Approvals.h](/ApprovalTests/Catch2Approvals.h) for the code you will need to add to your `main.cpp`.

If it would be helpful for us to provide an easier way to do this, please let us know, via the contact details in [Contributing to ApprovalTests.cpp](Contributing.md#top). 

## Google Test

The [Google Test](https://github.com/google/googletest) test framework works well with Approval Tests.

This section describes the various ways of using Approval Tests with Google Test.

### Starter Project

We haven't yet provided a Starter Project for using Approval Tests with Google Tests.

This is partly based on the assumption that anyone already using Google Tests will have their own project set up, and anyone else would probably use Catch 2 instead.
 
If it would be helpful for us to such a Starter Project, please let us know, via the contact details in [Contributing to ApprovalTests.cpp](Contributing.md#top). 


### New Project

Create a file `main.cpp` and add just the following two lines:

snippet: googletest_main

### Existing Project - no main()

Google Test has a `gtest_main` library that provides a `main()` function, and then runs all your tests.

If your existing Google Test application uses the `gtest_main` library, Approval Tests will not be able to obtain the names to use output files. You will then see the help message shown in [Troubleshooting](Troubleshooting.md#top).

To fix this, please add a new `main.cpp`, as shown in the previous section.


### Existing Project - with your main()

If you have an existing Google Test-based test program that provides its own `main()`, you won't be able to use the approach above.

Instead, you should make the following additions to your own source file that contains `main()`.  

snippet: googletest_existing_main

---

[Back to User Guide](/doc/README.md#top)
