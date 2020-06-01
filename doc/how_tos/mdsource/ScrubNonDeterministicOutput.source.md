<a id="top"></a>

# How to Scrub Non-Deterministic Output

toc

## Introduction

If you are having trouble getting tests running reproducibly, you might need to use a "scrubber" to convert the non-deterministic text to something stable.

## Interface

Fundamentally, a scrubber is function that takes a string and returns a string. You can create ones by passing in a function or a lambda. We also have some pre-made ones for your convenience.

## Lambda example

snippet: scrubbing_via_lambda

This would produce:

snippet: GuidScrubberTests.Scrubbing_via_Lambda.approved.txt

(In the real world, scrubbers are generally used to remove text that is expected to differ between test runs... Here, we use a trivial example for ease of explanation.)

## Pre-made Scrubbers

### Regular Expressions (regex)

Approval Tests provides lots of convenience methods to scrub text based on regular expressions.

For example, here is an example where random numbers are scrubbed:

snippet: simple_regex_scrubbing

This will produce:

snippet: ScrubberTests.test_createRegexScrubber_with_string_input_and_fixed_result.approved.txt

**Note**: In the above example, the caller passes in a `std::string`, and for convenience of the calling code, Approval Tests
converts that to a `std::regex`. The calling code is responsible for making sure that the string contains a valid
regular expression.

There are many combinations of these parameters, that allow for customization at whatever level you
need, the most complex being:

snippet: complex_regex_scrubbing

This will produce:

snippet: ScrubberTests.test_createRegexScrubber.approved.txt

### GUID

You can scrub GUIDs by using a pointer to the function `Scrubbers::scrubGuid`.
 
For example the following code:

snippet: guid_scrubbing

will produce:

snippet: GuidScrubberTests.Input_with_multiple_GUIDs.approved.txt

Notice that when GUIDs are repeated within the same file, they are replaced with the same text.

---

[Back to User Guide](/doc/README.md#top)
