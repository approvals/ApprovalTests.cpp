<a id="top"></a>

# Why We Are Converting To Options

<!-- toc -->
## Contents

  * [Introduction](#introduction)
  * [Scrubbers](#scrubbers)
  * [API](#api)
  * [The Plan](#the-plan)
    * [Suggested strategy](#suggested-strategy)
  * [Opting in](#opting-in)
  * [How to Update Calls to Deprecated Code](#how-to-update-calls-to-deprecated-code)
    * [Updating verify(..., Reporter)](#updating-verify-reporter)
    * [Updating verifyWithExtension(..., fileExtensionWithDot, Reporter)](#updating-verifywithextension-fileextensionwithdot-reporter)<!-- endToc -->

## Introduction

We have introduced an optional `Options` parameter, instead of the optional `Reporter` parameter. The following is the history and reasoning for making this change, as well as our plans to roll it out.

For information on using Options itself, see [Options](/doc/Options.md#top).

## Scrubbers

With the addition of Scrubbers, we realised that ApprovalTests has some optional parameters. The only one we had of these before was reporter. Because of that, we decided to group together all of the options in to a single container object. This gives us a few advantages:

1. We can expand in the future without changing the API.
2. Adding functionality becomes simpler, because it passes through to a single place.

It is effectively preparing to use the "Introduce Parameter Object" refactoring pattern.

## API

**Note**: The following series of releases was completed with the release of v.10.0.0. We are retaining this documentation to help out anyone who has yet to update from one of the earlier release.

Our current pattern is to have an optional Reporter at the end of any verify() method.

We are switching this to have an option `Options` object instead.

This temporarily doubles our API interface, and we are deprecating the Reporter overloads.
When enabled, these deprecation warnings will show up as:

* compiler C++14 and above, using the `[[deprecated("..."]]` feature
* messages on std::cout in C++11

## The Plan

Historically, we have found that it is easier for users to update code for breaking changes if these changes are rolled out in a graduated way. This allows users to select which version of the library to use, to have the ability to update code incrementally.

We how now finished our short series of quick releases to release this:

1. deprecation warnings are off: users can opt-in (v.8.7.0)
1. deprecation warnings are on: users can opt-out (v.8.9.1)
1. deprecation warnings are forced, code still exists  (v.8.9.2)
1. the deprecated methods are hidden: users can opt-in (v.9.0.0)
1. the deprecated methods are removed (v.10.0.0)

| Step | Deprecation Warnings                           | Deprecated Code                           |
| ---- | ---------------------------------------------- | ----------------------------------------- |
|      | See `APPROVAL_TESTS_SHOW_DEPRECATION_WARNINGS` | See `APPROVAL_TESTS_HIDE_DEPRECATED_CODE` |
| 1    | Optional: off                                  | Optional: enabled                         |
| 2    | Optional: on                                   | Optional: enabled                         |
| 3    | Always on                                      | Optional: enabled                         |
| 4    | Always on                                      | Optional: hidden                          |
| 5    | Not applicable                                 | Removed                                   |

### Suggested strategy

We suggest that any time you want to remove the deprecations, you jump ahead and toggle hide-deprecations, and let the compiler help you find the code you need to update.

## Opting in

Currently (2020-06-04), all deprecated code is removed.

If you are are using an earlier version, see [How to Toggle Enabling or Disabling of Deprecated Code](/doc/how_tos/ToggleDeprecatedCode.md#top).

## How to Update Calls to Deprecated Code

Whenever we deprecate a method, the implementation of the deprecated method will always contain a single line, which is how we want the code to be called in the future.<!-- include: updating_deprecated_code. path: /doc/how_tos/updating_deprecated_code.include.md -->

As such, you can always open up the method to see how to convert your code.

If you IDE supports inlining, you can also select your old function call, and inline just that one line, and your IDE will update the code for you.

**Note** If you are reading this after we have removed the deprecated methods, please download a slightly earlier release, and then follow one of the steps above.<!-- endInclude -->

### Updating verify(..., Reporter)

Instead of passing in a `Reporter` instance, you are now going to pass in an `Options` object containing the Reporter instance, for example `Options(MyReporter())`.

This is an example what the new code would look like:

<!-- snippet: basic_approval_with_reporter -->
<a id='snippet-basic_approval_with_reporter'></a>
```cpp
using namespace ApprovalTests;
Approvals::verify("text to be verified", Options(Windows::AraxisMergeReporter()));
```
<sup><a href='/examples/googletest_existing_main/GoogleTestApprovalsTests.cpp#L13-L16' title='Snippet source file'>snippet source</a> | <a href='#snippet-basic_approval_with_reporter' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

### Updating verifyWithExtension(..., fileExtensionWithDot, Reporter)

Before, we had several overloads of a special method - `verifyWithExtension()` - to set the file extension to be used when verifying a piece of text, for when `.txt` was not appropriate.

Because `Options` allows the file extension to be specified, all verify methods now have this capability.

As such, this specialised method is redundant, and is being removed.

This is an example what the new code would look like:

<!-- snippet: use_custom_file_extension -->
<a id='snippet-use_custom_file_extension'></a>
```cpp
ApprovalTests::Approvals::verify(
    "<h1>hello world</h1>",
    ApprovalTests::Options().fileOptions().withFileExtension(".html"));
```
<sup><a href='/tests/DocTest_Tests/DocTestApprovalTestTests.cpp#L17-L21' title='Snippet source file'>snippet source</a> | <a href='#snippet-use_custom_file_extension' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

---

[Back to User Guide](/doc/README.md#top)
