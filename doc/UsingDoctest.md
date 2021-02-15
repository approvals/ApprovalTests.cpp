<a id="top"></a>

# Using Approval Tests With doctest


<!-- toc -->
## Contents

  * [Introduction](#introduction)
  * [Requirements](#requirements)
  * [Getting Started With doctest](#getting-started-with-doctest)
      * [New Project](#new-project)
      * [Existing Project - with your main()](#existing-project---with-your-main)<!-- endToc -->

## Introduction

The [doctest](https://github.com/onqtam/doctest) test framework works well with Approval Tests.

**Notes pre-v.10.8.0:** <!-- include: include_ninja_warning_note. path: /doc/include_ninja_warning_note.include.md -->

Earlier versions of Approval Tests had issues with Ninja. Read more
at [Troubleshooting Misconfigured Build](/doc/TroubleshootingMisconfiguredBuild.md#top). <!-- endInclude -->

Doctest is similar to Catch, but claims to give faster compilation times.

## Requirements

Approval Tests for doctest requires that a file called the following is found:

<!-- snippet: required_header_for_doctest -->
<a id='snippet-required_header_for_doctest'></a>
```h
#include <doctest/doctest.h>
```
<sup><a href='/ApprovalTests/integrations/doctest/DocTestApprovals.h#L16-L18' title='Snippet source file'>snippet source</a> | <a href='#snippet-required_header_for_doctest' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Approval Tests needs doctest version 2.3.4 or above.

## Getting Started With doctest

### New Project

Create a file `main.cpp` and add just the following two lines:

<!-- snippet: doctest_main -->
<a id='snippet-doctest_main'></a>
```cpp
// main.cpp:
#define APPROVALS_DOCTEST // This tells Approval Tests to provide a main() - only do this in one cpp file
#include "ApprovalTests.hpp"
```
<sup><a href='/tests/DocTest_Tests/main.cpp#L1-L5' title='Snippet source file'>snippet source</a> | <a href='#snippet-doctest_main' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

<!-- todo: document use of sections -->

### Existing Project - with your main()

If you have [supplied your own `main()` for doctest](https://github.com/onqtam/doctest/blob/master/doc/markdown/main.md#top), you will need to teach it how to supply test names to Approval Tests.

You should make the following additions to your own source file that contains `main()`.  

<!-- snippet: doctest_existing_main -->
<a id='snippet-doctest_existing_main'></a>
```cpp
// Add these two lines to the top of your main.cpp file:
#define APPROVALS_DOCTEST_EXISTING_MAIN
#include "ApprovalTests.hpp"
```
<sup><a href='/examples/doctest_existing_main/main.cpp#L1-L5' title='Snippet source file'>snippet source</a> | <a href='#snippet-doctest_existing_main' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

---

[Back to User Guide](/doc/README.md#top)
