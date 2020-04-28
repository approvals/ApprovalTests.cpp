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

Our plan is to:
 
1. start with the deprecations being something users can opt in to
1. deprecation warnings are opt-out
1. deprecation warnings are forced
1. the deprecated methods are hidden by default
1. the deprecated methods are removed

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
