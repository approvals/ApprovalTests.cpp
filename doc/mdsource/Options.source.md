<a id="top"></a>

<!-- Type: How to customise with options -->

# Options

toc

## Introduction

There are many things you might want to tweak with Approval Tests. `Options` is the entry-point for many of the changes.
It is on all `verify()` methods, as an optional parameter.

## Fluent Interface

Options utilizes a fluent interface, allowing you to chain together commands. Each returned object is a new copy.

snippet: specify_all_the_options

## Reporters

There are two ways to set a Reporter.

1. Pass in a Reporter object to the Options constructor, for example:

snippet: basic_approval_with_reporter

2. Call `.withReporter()` on an existing Options object, for example:

snippet: basic_approval_with_reporter_2

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
