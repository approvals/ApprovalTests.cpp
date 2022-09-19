<a id="top"></a>

# Reporters

<!-- toc -->
## Contents

  * [Supported Diff Tools](#supported-diff-tools)
    * [Mac](#mac)
    * [Linux](#linux)
    * [Windows](#windows)
  * [Cross-platform](#cross-platform)
  * [Registering a default reporter](#registering-a-default-reporter)
  * [Front Loaded Reporters](#front-loaded-reporters)
    * [Blocking Reporters](#blocking-reporters)
  * [Miscellaneous Helper Reporters](#miscellaneous-helper-reporters)
    * [Auto-approving](#auto-approving)
  * [Related Pages](#related-pages)<!-- endToc -->

## Supported Diff Tools

The DiffReporter class goes through a chain of possible reporters to find the first option installed on your system.
Currently the search goes in this order:

### Mac

<!-- snippet: mac_diff_reporters -->
<a id='snippet-mac_diff_reporters'></a>
```cpp
new AraxisMergeReporter(),
new BeyondCompareReporter(),
new DiffMergeReporter(),
new KaleidoscopeReporter(),
new P4MergeReporter(),
new SublimeMergeReporter(),
new KDiff3Reporter(),
new TkDiffReporter(),
new VisualStudioCodeReporter(),
new CLionDiffReporter()
```
<sup><a href='/ApprovalTests/reporters/MacReporters.cpp#L63-L74' title='Snippet source file'>snippet source</a> | <a href='#snippet-mac_diff_reporters' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

### Linux

<!-- snippet: linux_diff_reporters -->
<a id='snippet-linux_diff_reporters'></a>
```cpp
new BeyondCompareReporter(),
new MeldReporter(),
new SublimeMergeReporter(),
new KDiff3Reporter()
```
<sup><a href='/ApprovalTests/reporters/LinuxReporters.cpp#L55-L60' title='Snippet source file'>snippet source</a> | <a href='#snippet-linux_diff_reporters' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

### Windows

<!-- snippet: windows_diff_reporters -->
<a id='snippet-windows_diff_reporters'></a>
```cpp
new TortoiseDiffReporter(), // Note that this uses Tortoise SVN Diff
new TortoiseGitDiffReporter(),
new BeyondCompareReporter(),
new WinMergeReporter(),
new AraxisMergeReporter(),
new CodeCompareReporter(),
new SublimeMergeReporter(),
new KDiff3Reporter(),
new VisualStudioCodeReporter(),
```
<sup><a href='/ApprovalTests/reporters/WindowsReporters.cpp#L94-L104' title='Snippet source file'>snippet source</a> | <a href='#snippet-windows_diff_reporters' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Cross-platform

These are all based on the diff tool being in the [`PATH`](https://en.wikipedia.org/wiki/PATH_(variable)).

<!-- snippet: cross_platform_diff_reporters -->
<a id='snippet-cross_platform_diff_reporters'></a>
```cpp
new VisualStudioCodeReporter(),
```
<sup><a href='/ApprovalTests/reporters/CrossPlatformReporters.cpp#L16-L18' title='Snippet source file'>snippet source</a> | <a href='#snippet-cross_platform_diff_reporters' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Registering a default reporter

At present, the default Reporter is the DiffReporter. Whenever you call Approvals, you have the chance to pass in your own Reporter. However, if you would like to change what the default reporter is when you don't pass in a specific Reporter, you can do this at a global or per-test level, by adding the line:

<!-- snippet: use_as_default_reporter_in_main -->
<a id='snippet-use_as_default_reporter_in_main'></a>
```cpp
// main.cpp:
#include <memory>
auto defaultReporterDisposer = ApprovalTests::Approvals::useAsDefaultReporter(
    std::make_shared<ApprovalTests::DiffReporter>());
```
<sup><a href='/tests/Catch2_Tests/main.cpp#L17-L22' title='Snippet source file'>snippet source</a> | <a href='#snippet-use_as_default_reporter_in_main' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

The return value is ["Disposable"](/doc/DisposableObjects.md#top), meaning it will restore the original reporter when the object destructs. Because of this, if you do not store the result in a variable, it will immediately undo itself by the end of the line.

## Front Loaded Reporters

By default, Approval tests will not launch any reporters on supported CI machines. To do this, we use front loaded reporters...

Front loaded reporters allow you to block all normal reporting behaviour. This is useful in situations like running on a CI Machine, where you wouldn't want a reporter to open.

For more information, see [Build Machines and Continuous Integration servers](/doc/BuildMachinesAndCI.md#top).

Here is an example of not launching any reporters if you are on a machine with a particular name, by using [BlockingReporter](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/BlockingReporter.h).

<!-- snippet: do_not_report_on_named_machine -->
<a id='snippet-do_not_report_on_named_machine'></a>
```cpp
// main.cpp
auto frontLoadedReportDisposer = ApprovalTests::Approvals::useAsFrontLoadedReporter(
    ApprovalTests::BlockingReporter::onMachineNamed("MyCIMachineName"));
```
<sup><a href='/examples/googletest_existing_main/main.cpp#L19-L23' title='Snippet source file'>snippet source</a> | <a href='#snippet-do_not_report_on_named_machine' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Once you have added that, even calling approvals with a specific Reporter will not launch it on the CI system (but will for all other systems). For example:

<!-- snippet: basic_approval_with_reporter -->
<a id='snippet-basic_approval_with_reporter'></a>
```cpp
using namespace ApprovalTests;
Approvals::verify("text to be verified", Options(Windows::AraxisMergeReporter()));
```
<sup><a href='/examples/googletest_existing_main/GoogleTestApprovalsTests.cpp#L13-L16' title='Snippet source file'>snippet source</a> | <a href='#snippet-basic_approval_with_reporter' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

### Blocking Reporters

Blocking reporters are a simple class, designed for use with FrontLoadedReporters, to prevent launching of reporters in certain environments.

<!-- snippet: do_not_report_on_named_machine -->
<a id='snippet-do_not_report_on_named_machine'></a>
```cpp
// main.cpp
auto frontLoadedReportDisposer = ApprovalTests::Approvals::useAsFrontLoadedReporter(
    ApprovalTests::BlockingReporter::onMachineNamed("MyCIMachineName"));
```
<sup><a href='/examples/googletest_existing_main/main.cpp#L19-L23' title='Snippet source file'>snippet source</a> | <a href='#snippet-do_not_report_on_named_machine' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Miscellaneous Helper Reporters

While most reporters open some sort of external program, for the purpose of understanding how the tests went wrong, and verifying the correct answer, there are some reporters that are helpful for specific situations.

### Auto-approving

There are three reporters that can help with the approving of single or multiple tests.

* `AutoApproveIfMissingReporter`: if there is no approved file already, the received file will automatically be copied over the approved one. Otherwise, it does nothing. One possible cause for confusion here is if you ran the test previously with a standard reporter, that will have created an almost-empty approved file, which will then block this from working.
* `ClipboardReporter`: this puts the command-line to moved the approve file on to your computer's clipboard. You then review this, and paste it in to a terminal window. This only works with one test at a time.
* `AutoApproveReporter`: be careful, this will overwrite every existing ".approved" file, with no confirmation. This is best used when you are expecting large numbers of files that are already version-controlled to be updated, and you would rather review the changes in your version control system. 

## Related Pages

* [How to Use A Custom Reporter](/doc/how_tos/UseACustomReporter.md#top)
* [How to Select a Reporter with an Environment Variable](/doc/how_tos/SelectReporterWithEnvironmentVariable.md#top)
* [How to Submit a New Reporter to ApprovalTests](/doc/how_tos/SubmitANewReporterToApprovalTests.md#top)

---

[Back to User Guide](/doc/README.md#top)
