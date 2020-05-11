<a id="top"></a>

<!-- Type: How to customise with options -->

# Options

toc

## Introduction

There are many things you might want to tweak with Approval Tests. `Options` is the entry-point for many of the changes.
It is on all `verify()` methods, as an optional parameter.

**Note:** If you are interested in why we moved from "optional Reporter arguments" to "optional Options arguments", see [Why We Are Converting To Options](/doc/explanations/WhyWeAreConvertingToOptions.md#top).

## Fluent Interface

Options utilizes a fluent interface, allowing you to chain together commands. Each returned object is a new copy.

snippet: specify_all_the_options

## Reporters

[Reporters](/doc/Reporters.md#top) launch diff tools upon failure. There are two ways to set a Reporter.

1. Pass in a Reporter object to the Options constructor, for example:

snippet: basic_approval_with_reporter

2. Call `.withReporter()` on an existing Options object, for example:

snippet: basic_approval_with_reporter_2

## Scrubbers

[Scrubbers](/doc/Scrubbers.md#top) clean output to help remove inconsistent pieces of text, such as dates.
There are two ways to set a Scrubber.

1. Pass in a function pointer to the Options constructor, for example:

snippet: basic_approval_with_scrubber

2. Call `.withScrubber()` with a function pointer, for example:

snippet: basic_approval_with_scrubber_2

## File Options

The `Options::FileOptions` class exists to customise the `.approved` and `.received` files in various ways.

For now, it just controls the file extension. 

### File Extensions

If you want to change the file extension of both the approved and received files, use `withFileExtension()`.

snippet: basic_approval_with_file_extension

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
