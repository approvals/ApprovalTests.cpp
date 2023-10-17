<a id="top"></a>

# How to Toggle Enabling or Disabling of Deprecated Code

<!-- toc -->
## Contents

  * [Introduction](#introduction)
  * [Deprecation Mechanics](#deprecation-mechanics)
  * [Opting in](#opting-in)
    * [Show warnings](#show-warnings)
    * [Hide deprecated code](#hide-deprecated-code)
  * [How to Update Calls to Deprecated Code](#how-to-update-calls-to-deprecated-code)<!-- endToc -->

## Introduction

> "To Err is Human, to Deprecate is Divine..."

Shakespeare (paraphrased)

From time to time, we realise that our previous decisions were a mistake, that we don't want to carry with us in the future.
We also don't want to strand our users, who are currently relying on the old code working the way that it does.

Here's how Approval Tests deals with deprecations.

## Deprecation Mechanics

When enabled, these deprecation warnings will show up as:
 
* compiler C++14 and above, using the `[[deprecated("..."]]` feature
* messages on std::cout in C++11

## Opting in

### Show warnings

To opt in to warnings, add this line to your C++ code: 

<!-- snippet: show_deprecation_warnings -->
<a id='snippet-show_deprecation_warnings'></a>
```cpp
#define APPROVAL_TESTS_SHOW_DEPRECATION_WARNINGS 1
```
<sup><a href='/examples/doctest_existing_main/DoctestApprovalsTests.cpp#L1-L3' title='Snippet source file'>snippet source</a> | <a href='#snippet-show_deprecation_warnings' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Or this to your CMakeLists.txt:

<!-- snippet: show_deprecation_warnings_cmake -->
<a id='snippet-show_deprecation_warnings_cmake'></a>
```txt
# Replace ${PROJECT_NAME} with the name of your test executable:
target_compile_definitions(${PROJECT_NAME} PRIVATE -DAPPROVAL_TESTS_SHOW_DEPRECATION_WARNINGS=1)
```
<sup><a href='/tests/DocTest_Tests/CMakeLists.txt#L73-L76' title='Snippet source file'>snippet source</a> | <a href='#snippet-show_deprecation_warnings_cmake' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

### Hide deprecated code

A more extreme version of this is to not even compile the deprecated code. You can do this by adding this line:

<!-- snippet: hide_deprecated_code -->
<a id='snippet-hide_deprecated_code'></a>
```cpp
#define APPROVAL_TESTS_HIDE_DEPRECATED_CODE 1
```
<sup><a href='/examples/doctest_existing_main/DoctestApprovalsTests.cpp#L5-L7' title='Snippet source file'>snippet source</a> | <a href='#snippet-hide_deprecated_code' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Or this to your CMakeLists.txt:

<!-- snippet: hide_deprecated_code_cmake -->
<a id='snippet-hide_deprecated_code_cmake'></a>
```txt
# Replace ${PROJECT_NAME} with the name of your test executable:
target_compile_definitions(${PROJECT_NAME} PRIVATE -DAPPROVAL_TESTS_HIDE_DEPRECATED_CODE=1)
```
<sup><a href='/tests/DocTest_Tests/CMakeLists.txt#L78-L81' title='Snippet source file'>snippet source</a> | <a href='#snippet-hide_deprecated_code_cmake' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## How to Update Calls to Deprecated Code

Whenever we deprecate a method, the implementation of the deprecated method will always contain a single line, which is how we want the code to be called in the future.<!-- include: updating_deprecated_code. path: /doc/how_tos/updating_deprecated_code.include.md -->

As such, you can always open up the method to see how to convert your code.

If you IDE supports inlining, you can also select your old function call, and inline just that one line, and your IDE will update the code for you.

**Note** If you are reading this after we have removed the deprecated methods, please download a slightly earlier release, and then follow one of the steps above.<!-- endInclude -->

---

[Back to User Guide](/doc/README.md#top)
