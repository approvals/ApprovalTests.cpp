<a id="top"></a>

# Using Approval Tests With Boost.Test


<!-- toc -->
## Contents

  * [Introduction](#introduction)
  * [Requirements](#requirements)
  * [Getting Started With Boost.Test](#getting-started-with-boosttest)
    * [Adding ApprovalTests to your Boost.Test](#adding-approvaltests-to-your-boosttest)
      * [Understanding Boost.Test Entry points](#understanding-boosttest-entry-points)<!-- endToc -->

## Introduction

The [Boost.Test](https://www.boost.org/doc/libs/1_72_0/libs/test/doc/html/index.html) test framework works well with Approval Tests.

**Note:** this document assumes the reader is familiar with the Boost.Test framework.

## Requirements

Approval Tests for Boost.Test requires that you specify the `#include <.../unit_test.hpp>`  
This allows ApprovalTests to work with all the different configurations of boost.  

Approval Tests needs Boost.Test version 1.60.0 or above.

## Getting Started With Boost.Test

### Adding ApprovalTests to your Boost.Test

To enable any Boost.Test test files to use ApprovalTests,
find the corresponding entry point and  
add the following lines of code to your [Test module's entry point](https://www.boost.org/doc/libs/1_72_0/libs/test/doc/html/boost_test/adv_scenarios/entry_point_overview.html) 
after the boost headers:

<!-- snippet: boost_test_main -->
<a id='snippet-boost_test_main'></a>
```cpp
// test_entry_point.cpp file[s] (after #including boost.test)
#define APPROVALS_BOOSTTEST
#include "ApprovalTests.hpp"
```
<sup><a href='/tests/Boost_Tests/main.cpp#L8-L12' title='File snippet `boost_test_main` was extracted from'>snippet source</a> | <a href='#snippet-boost_test_main' title='Navigate to start of snippet `boost_test_main`'>anchor</a></sup>
<!-- endSnippet -->

#### Understanding Boost.Test Entry points

A directory of Boost.Test source files can either have multiple or a single entry point[s]. 
The entry point is any file that will contain the line:

<!-- snippet: boost_test_entry_point -->
<a id='snippet-boost_test_entry_point'></a>
```cpp
#define BOOST_TEST_MODULE ModuleName
```
<sup><a href='/tests/Boost_Tests/main.cpp#L1-L3' title='File snippet `boost_test_entry_point` was extracted from'>snippet source</a> | <a href='#snippet-boost_test_entry_point' title='Navigate to start of snippet `boost_test_entry_point`'>anchor</a></sup>
<!-- endSnippet -->


---

[Back to User Guide](/doc/README.md#top)
