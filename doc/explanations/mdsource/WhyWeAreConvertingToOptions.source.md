<a id="top"></a>

# Why We Are Converting To Options

toc

## Scrubbers

With the addition of Scrubbers, we realised that ApprovalTests has some optional parameters. The only one we had of these before was reporter. Because of that, we decided to group together all of the options in to a single container object. This gives us a few advantages:

1. We can expand in the future without changing the API.
2. Adding functionality becomes simpler, because it passes through to a single place.

It is effectively preparing to use the "Introduce Parameter Object" refactoring pattern.

## API

Our current pattern is to have an optional Reporter at the end of any verify() method.

We are switching this to have an option Options object instead.

This temporarily doubles our API interface, and we are deprecating the Reporter overloads.
When enabled, these deprecation warnings will show up as:
 
* compiler C++14 and above, using the `[[deprecated("..."]]` feature
* messages on std::cout in C++11

## The Plan

Historically, we have found that it is easier for users to update code for breaking changes if these changes are rolled out in a graduated way. This allows users to select which version of the library to use, to have the ability to update code incrementally.

Our plan is therefore to do a short series of quick releases:

1. deprecation warnings are off: users can opt-in
1. deprecation warnings are on: users can opt-out
1. deprecation warnings are forced, code still exists 
1. the deprecated methods are hidden: users can opt-in
1. the deprecated methods are removed

| Step | Deprecation Warnings<br />See `APPROVAL_TESTS_SHOW_DEPRECATION_WARNINGS` | Deprecated Code<br />See `APPROVAL_TESTS_HIDE_DEPRECATED_CODE` |
| ---- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 1    | Optional: off                                                | Optional: enabled                                            |
| 2    | Optional: on                                                 | Optional: enabled                                            |
| 3    | Always on                                                    | Optional: enabled                                            |
| 4    | Always on                                                    | Optional: hidden                                             |
| 5    | Not applicable                                               | Removed                                                      |

### Suggested strategy

We suggest that any time you want to remove the deprecations, you jump ahead and toggle hide-deprecations, and let the compiler help you find the code you need to update.

## Opting in

Currently (2020-04-21), deprecation warnings are turned off by default.

To change that, see [How To Toggle Enabling or Disabling of Deprecated Code](/doc/how_tos/ToggleDeprecatedCode.md#top).

## How to Update Calls to Deprecated Code

include: updating_deprecated_code

### Updating verify(..., Reporter)

Instead of passing in a `Reporter` instance, you are now going to pass in an Options object containing the Reporter instance, for example `Options(MyReporter())`.

This is an example what the new code would look like:

snippet: basic_approval_with_reporter

### Updating verifyWithExtension(..., fileExtensionWithDot, Reporter)

Before, we had a special method to set the file extension to be used when verifying a piece of text, for when `.txt` was not wanted.

Because Options allows the file extension to be specified, all verify methods now have this capability.

As such, this specialised method is redundant, and is being removed.

This is an example what the new code would look like:

snippet: use_custom_file_extension

---

[Back to User Guide](/doc/README.md#top)
