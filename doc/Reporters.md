<!--
This file was generate by MarkdownSnippets.
Source File: /doc/mdsource/Reporters.source.md
To change this file edit the source file and then re-run the generation using either the dotnet global tool (https://github.com/SimonCropp/MarkdownSnippets#markdownsnippetstool) or using the api (https://github.com/SimonCropp/MarkdownSnippets#running-as-a-unit-test).
-->
<a id="top"></a>

# Reporter



<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Contents**

- [DiffReporter](#diffreporter)
  - [Mac](#mac)
  - [Linux](#linux)
  - [Windows](#windows)
- [Registering a default reporter](#registering-a-default-reporter)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## DiffReporter

DiffReporter go through a chain of possible reporters to find the first option installed on your system.
Currently the search goes in this order:

### Mac

<!-- snippet: mac_diff_reporters -->
```h
new BeyondCompareReporter(),
new DiffMergeReporter(),
new KaleidoscopeReporter(),
new P4MergeReporter(),
new KDiff3Reporter(),
new TkDiffReporter(),
new VisualStudioCodeReporter()
```
<sup>[snippet source](/ApprovalTests/reporters/MacReporters.h#L48-L56)</sup>
<!-- endsnippet -->

### Linux

<!-- snippet: linux_diff_reporters -->
```h
new MeldReporter(),
new KDiff3Reporter()
```
<sup>[snippet source](/ApprovalTests/reporters/LinuxReporters.h#L25-L28)</sup>
<!-- endsnippet -->

### Windows

<!-- snippet: windows_diff_reporters -->
```h
new TortoiseDiffReporter(),
new BeyondCompareReporter(),
new WinMergeReporter(),
new AraxisMergeReporter(),
new CodeCompareReporter(),
new KDiff3Reporter(),
new VisualStudioCodeReporter(),
```
<sup>[snippet source](/ApprovalTests/reporters/WindowsReporters.h#L71-L79)</sup>
<!-- endsnippet -->

## Registering a default reporter

At present, the default Reporter is the DiffReporter. Whenever you call Approvals, you have the chance to pass in your own Reporter. However, if you would like to change what the default reporter is when you don't pass in a specific Reporter, you can do this at a global or per-test level, by adding the line:

<!-- snippet: use_as_default_reporter_in_main -->
```cpp
// main.cpp:
#include <memory>
auto defaultReporterDisposer = Approvals::useAsDefaultReporter( std::make_shared<DiffReporter>() );
```
<sup>[snippet source](/ApprovalTests_Catch2_Tests/main.cpp#L14-L18)</sup>
<!-- endsnippet -->

The return value will restore the original reporter when the object destructs. Because of this, if you do not store the result in a variable, it will immediately undo itself by the end of the line.


---

[Back to User Guide](/doc/README.md#top)
