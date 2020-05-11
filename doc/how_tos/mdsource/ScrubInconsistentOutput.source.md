<a id="top"></a>

# How to Scrub Inconsistent Output

toc

## Introduction

If you are having trouble getting tests running reproducibly, you might need to use a "scrubber" to convert the non-deterministic text to something stable.

## GUID

You can scrub GUIDs by using a pointer to the function `Scrubbers::scrubGuid`, for example the following code:

snippet: guid_scrubbing

will produce:

snippet: GuidScrubberTests.Input_with_multiple_GUIDs.approved.txt

Notice that when GUIDs are repeated within the same file, they are replaced with the same text.


---

[Back to User Guide](/doc/README.md#top)
