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
  * [Adding to Existing Options object](#adding-to-existing-options-object)<!-- endToc -->

## Introduction

There are many things you might want to tweak with Approval Tests. `Options` is the entry-point for many of the changes.
It is on all `verify()` methods, as an optional parameter.

**Note:** If you are interested in why we moved from "optional Reporter arguments" to "optional Options arguments", see [Why We Are Converting To Options](/doc/explanations/WhyWeAreConvertingToOptions.md#top).

## Fluent Interface

Options utilizes a fluent interface, allowing you to chain together commands. Each returned object is a new copy.

<!-- snippet: specify_all_the_options -->
<a id='snippet-specify_all_the_options'></a>
```cpp
ApprovalTests::Options()
    .withReporter(ApprovalTests::QuietReporter())
    .withScrubber(ApprovalTests::Scrubbers::scrubGuid)
    .fileOptions().withFileExtension(".json")
```
<sup><a href='/tests/DocTest_Tests/DocTestApprovalTestTests.cpp#L50-L55' title='Snippet source file'>snippet source</a> | <a href='#snippet-specify_all_the_options' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Reporters

[Reporters](/doc/Reporters.md#top) launch diff tools upon failure. There are two ways to set a Reporter.

1. Pass in a Reporter object to the Options constructor, for example:

<!-- snippet: basic_approval_with_reporter -->
<a id='snippet-basic_approval_with_reporter'></a>
```cpp
using namespace ApprovalTests;
Approvals::verify("text to be verified", Options(Windows::AraxisMergeReporter()));
```
<sup><a href='/examples/googletest_existing_main/GoogleTestApprovalsTests.cpp#L13-L16' title='Snippet source file'>snippet source</a> | <a href='#snippet-basic_approval_with_reporter' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

2. Call `.withReporter()` on an existing Options object, for example:

<!-- snippet: basic_approval_with_reporter_2 -->
<a id='snippet-basic_approval_with_reporter_2'></a>
```cpp
using namespace ApprovalTests;
Approvals::verify("text to be verified",
                  Options().withReporter(Mac::AraxisMergeReporter()));
```
<sup><a href='/examples/googletest_existing_main/GoogleTestApprovalsTests.cpp#L21-L25' title='Snippet source file'>snippet source</a> | <a href='#snippet-basic_approval_with_reporter_2' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Scrubbers

[Scrubbers](/doc/explanations/Scrubbers.md#top) clean output to help remove inconsistent pieces of text, such as dates.
There are two ways to set a Scrubber.

1. Pass in a function pointer to the Options constructor, for example:

<!-- snippet: basic_approval_with_scrubber -->
<a id='snippet-basic_approval_with_scrubber'></a>
```cpp
using namespace ApprovalTests;
Approvals::verifyAll("IDs", v, Options(Scrubbers::scrubGuid));
```
<sup><a href='/tests/DocTest_Tests/scrubbers/GuidScrubberTests.cpp#L59-L62' title='Snippet source file'>snippet source</a> | <a href='#snippet-basic_approval_with_scrubber' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

2. Call `.withScrubber()` with a function pointer, for example:

<!-- snippet: basic_approval_with_scrubber_2 -->
<a id='snippet-basic_approval_with_scrubber_2'></a>
```cpp
using namespace ApprovalTests;
Approvals::verifyAll("IDs", v, Options().withScrubber(Scrubbers::scrubGuid));
```
<sup><a href='/tests/DocTest_Tests/scrubbers/GuidScrubberTests.cpp#L70-L73' title='Snippet source file'>snippet source</a> | <a href='#snippet-basic_approval_with_scrubber_2' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## File Options

The `Options::FileOptions` class exists to customise the `.approved` and `.received` files in various ways.

For now, it just controls the file extension. 

### File Extensions

If you want to change the file extension of both the approved and received files, use `withFileExtension()`.

<!-- snippet: basic_approval_with_file_extension -->
<a id='snippet-basic_approval_with_file_extension'></a>
```cpp
using namespace ApprovalTests;

Approvals::verify("text to be verified",
                  Options().fileOptions().withFileExtension(".xyz"));
```
<sup><a href='/tests/DocTest_Tests/core/OptionsExamples.cpp#L7-L12' title='Snippet source file'>snippet source</a> | <a href='#snippet-basic_approval_with_file_extension' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

**Note:** `withFileExtension()` returns an `Options` object, so it's possible to keep appending more `with...()` calls.  

## Defaults

The default constructor for Options does:

* no scrubbing
* uses file extension `.txt`
* uses whatever is currently set as [the default reporter](#registering-a-default-reporter).

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
