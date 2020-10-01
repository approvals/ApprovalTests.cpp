<a id="top"></a>

# Using Approval Tests With Catch


<!-- toc -->
## Contents

  * [Introduction](#introduction)
  * [Requirements](#requirements)
  * [Getting Started With Catch2](#getting-started-with-catch2)
    * [Starter Project](#starter-project)
    * [New Project](#new-project)
    * [Existing Project - with CATCH_CONFIG_MAIN](#existing-project---with-catch_config_main)
    * [Existing Project - with your main()](#existing-project---with-your-main)<!-- endToc -->

## Introduction

The [Catch2](https://github.com/catchorg/Catch2) test framework works well with Approval Tests.

This section describes the various ways of using Approval Tests with Catch2.

**Note:** Approval Tests has some specific build requirements if it is built with the [Ninja build generator](https://ninja-build.org/). **If you use Ninja with Approval Tests, special care is needed when setting up builds**, to avoid compilation errors or test failures. If you have any problems with this, please see [Troubleshooting Misconfigured Build](/doc/TroubleshootingMisconfiguredBuild.md#top). <!-- singleLineInclude: include_ninja_warning_note. path: /doc/mdsource/include_ninja_warning_note.include.md -->

## Requirements

Approval Tests requires that a file called the following is found:

<!-- snippet: required_header_for_catch -->
<a id='snippet-required_header_for_catch'></a>
```h
#include <catch2/catch.hpp>
```
<sup><a href='/ApprovalTests/integrations/catch/Catch2Approvals.h#L17-L19' title='File snippet `required_header_for_catch` was extracted from'>snippet source</a> | <a href='#snippet-required_header_for_catch' title='Navigate to start of snippet `required_header_for_catch`'>anchor</a></sup>
<!-- endSnippet -->

(Before v7.0.0, it required `Catch.hpp`)

## Getting Started With Catch2

### Starter Project

The quickest way to start experimenting with Approval Tests is to:

1. Download the project [ApprovalTests.cpp.StarterProject](https://github.com/approvals/ApprovalTests.cpp.StarterProject) - via the green "Clone or Download" button at the top-right of the project site.
2. Opening the project in the C++ IDE of your choice.

Each time we release a new version of Approval Tests, we update this project, so it always has the latest features. 

### New Project

Create a file `main.cpp` and add just the following two lines:

<!-- snippet: catch_2_main -->
<a id='snippet-catch_2_main'></a>
```cpp
// main.cpp:
#define APPROVALS_CATCH // This tells Approval Tests to provide a main() - only do this in one cpp file
#include "ApprovalTests.hpp"
```
<sup><a href='/tests/Catch2_Tests/main.cpp#L6-L10' title='File snippet `catch_2_main` was extracted from'>snippet source</a> | <a href='#snippet-catch_2_main' title='Navigate to start of snippet `catch_2_main`'>anchor</a></sup>
<!-- endSnippet -->

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

<!-- snippet: catch_existing_main -->
<a id='snippet-catch_existing_main'></a>
```cpp
// Add these two lines to the top of your main.cpp file:
#define APPROVALS_CATCH_EXISTING_MAIN
#include "ApprovalTests.hpp"
```
<sup><a href='/examples/catch2_existing_main/main.cpp#L1-L5' title='File snippet `catch_existing_main` was extracted from'>snippet source</a> | <a href='#snippet-catch_existing_main' title='Navigate to start of snippet `catch_existing_main`'>anchor</a></sup>
<!-- endSnippet -->


---

[Back to User Guide](/doc/README.md#top)
