<a id="top"></a>

# Using Approval Tests With Catch


toc

## Introduction

The [Catch2](https://github.com/catchorg/Catch2) test framework works well with Approval Tests.

This section describes the various ways of using Approval Tests with Catch2.

include: include_ninja_warning_note

## Requirements

Approval Tests requires that a file called the following is found:

snippet: required_header_for_catch

(Before v7.0.0, it required `Catch.hpp`)

## Getting Started With Catch2

### Starter Project

The quickest way to start experimenting with Approval Tests is to:

1. Download the project [ApprovalTests.cpp.StarterProject](https://github.com/approvals/ApprovalTests.cpp.StarterProject) - via the green "Clone or Download" button at the top-right of the project site.
2. Opening the project in the C++ IDE of your choice.

Each time we release a new version of Approval Tests, we update this project, so it always has the latest features. 

### New Project

Create a file `main.cpp` and add just the following two lines:

snippet: catch_2_main

### Existing Project - with CATCH_CONFIG_MAIN

If you have a Catch2 project with your own `main.cpp` that contains the following lines, you will need to replace them with the code in the previous section.

```cpp
#define CATCH_CONFIG_MAIN // remove these lines, and replace with Approval Tests lines
#include "catch2/catch.hpp"
```

<!-- todo: document use of sections -->

### Existing Project - with your main()

If you have [supplied your own `main()` for Catch](https://github.com/catchorg/Catch2/blob/master/docs/own-main.md#top), you will need to teach it how to supply test names to Approval Tests.

You should make the following additions to your own source file that contains `main()`.  

snippet: catch_existing_main


---

[Back to User Guide](/doc/README.md#top)
