<a id="top"></a>

# Scrubbers

<!-- toc -->
## Contents

  * [Introduction](#introduction)
  * [Interface](#interface)
  * [How to use Scrubbers](#how-to-use-scrubbers)
  * [Scrubber concepts](#scrubber-concepts)
  * [See also](#see-also)<!-- endToc -->

## Introduction

![Scrubber Overview](/doc/images/ScrubberOverview.png?raw=true)

If you are having trouble getting tests running reproducibly, you might need to use a "scrubber" to convert the non-deterministic text to something stable.

## Interface

Fundamentally, a scrubber is function that takes a string and returns a string. You can create ones by passing in a function or a lambda. We also have some pre-made ones for your convenience.

## How to use Scrubbers

You can scrub text manually, before passing it in to Approvals::verify(), but the preferred method is to include a
Scrubber as an option.

<!-- snippet: scrubber_in_options_object -->
<a id='snippet-scrubber_in_options_object'></a>
```cpp
ApprovalTests::Approvals::verify(input,
                                 ApprovalTests::Options().withScrubber(scrubber));
```
<sup><a href='/tests/DocTest_Tests/scrubbers/ScrubberTests.cpp#L77-L80' title='Snippet source file'>snippet source</a> | <a href='#snippet-scrubber_in_options_object' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Scrubber concepts

There are several patterns that are commonly used when scrubbing:

* Replace troublesome text
* Replace troublesome text, tracking duplicates
* Combining scrubbers
* Deleting troublesome lines

## See also

* [How to Scrub Non-Deterministic Output](/doc/how_tos/ScrubNonDeterministicOutput.md#top)

---

[Back to User Guide](/doc/README.md#top)
