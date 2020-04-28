<a id="top"></a>

# How to Toggle Enabling or Disabling of Deprecated Code

toc

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

snippet: show_deprecation_warnings

Or this to your CMakeLists.txt:

snippet: show_deprecation_warnings_cmake

### Hide deprecated code

A more extreme version of this is to not even compile the deprecated code. You can do this by adding this line:

snippet: hide_deprecated_code

Or this to your CMakeLists.txt:

snippet: hide_deprecated_code_cmake

## How to Update Calls to Deprecated Code

include: updating_deprecated_code

---

[Back to User Guide](/doc/README.md#top)
