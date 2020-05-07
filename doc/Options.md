<!--
GENERATED FILE - DO NOT EDIT
This file was generated by [MarkdownSnippets](https://github.com/SimonCropp/MarkdownSnippets).
Source File: /doc/mdsource/Options.source.md
To change this file edit the source file and then execute ./run_markdown_templates.sh.
-->

<a id="top"></a>

<!-- Type: How to customise with options -->

# Options

<!-- toc -->
## Contents

  * [Introduction](#introduction)
  * [Fluent Interface](#fluent-interface)
  * [Reporters](#reporters)
  * [Scrubbers](#scrubbers)
  * [File Options](#file-options)
    * [File Extensions](#file-extensions)
  * [Defaults](#defaults)
  * [Adding to Existing Options object](#adding-to-existing-options-object)<!-- endtoc -->

## Introduction

There are many things you might want to tweak with Approval Tests. `Options` is the entry-point for many of the changes.
It is on all `verify()` methods, as an optional parameter.

## Fluent Interface

Options utilizes a fluent interface, allowing you to chain together commands. Each returned object is a new copy.

<!-- snippet: specify_all_the_options -->
<a id='snippet-specify_all_the_options'/></a>
```cpp
Options()
    .withReporter(QuietReporter())
    .withScrubber(Scrubbers::scrubGuid)
    .fileOptions()
    .withFileExtension(".json")
```
<sup><a href='/tests/DocTest_Tests/DocTestApprovalTestTests.cpp#L46-L52' title='File snippet `specify_all_the_options` was extracted from'>snippet source</a> | <a href='#snippet-specify_all_the_options' title='Navigate to start of snippet `specify_all_the_options`'>anchor</a></sup>
<!-- endsnippet -->

## Reporters

There are two ways to set a Reporter.

1. Pass in a Reporter object to the Options constructor, for example:

<!-- snippet: basic_approval_with_reporter -->
<a id='snippet-basic_approval_with_reporter'/></a>
```cpp
Approvals::verify("text to be verified", Options(Windows::AraxisMergeReporter()));
```
<sup><a href='/examples/googletest_existing_main/GoogleTestApprovalsTests.cpp#L13-L15' title='File snippet `basic_approval_with_reporter` was extracted from'>snippet source</a> | <a href='#snippet-basic_approval_with_reporter' title='Navigate to start of snippet `basic_approval_with_reporter`'>anchor</a></sup>
<!-- endsnippet -->

2. Call `.withReporter()` on an existing Options object, for example:

<!-- snippet: basic_approval_with_reporter_2 -->
<a id='snippet-basic_approval_with_reporter_2'/></a>
```cpp
Approvals::verify("text to be verified",
                  Options().withReporter(Mac::AraxisMergeReporter()));
```
<sup><a href='/examples/googletest_existing_main/GoogleTestApprovalsTests.cpp#L20-L23' title='File snippet `basic_approval_with_reporter_2` was extracted from'>snippet source</a> | <a href='#snippet-basic_approval_with_reporter_2' title='Navigate to start of snippet `basic_approval_with_reporter_2`'>anchor</a></sup>
<!-- endsnippet -->

## Scrubbers

## File Options

### File Extensions

## Defaults

## Adding to Existing Options object

Because of the fluent options, you can modify a specific option from an existing Options object,
while retaining all other settings, and not changing the original object.

```cpp
verifyWithQuietReporter(std::string text, const Options& o)
{
    Approvals::verify(text, o.withReporter(QuietReporter());
}
```


---

[Back to User Guide](/doc/README.md#top)