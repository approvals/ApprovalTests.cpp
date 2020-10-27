<a id="top"></a>

# How to Select a Reporter with an Environment Variable

<!-- toc -->
## Contents

  * [Introduction](#introduction)
    * [Why](#why)
    * [Warning!](#warning)
  * [Setting the Environment Variable](#setting-the-environment-variable)
  * [Available Values](#available-values)
  * [Acceptable Variations](#acceptable-variations)<!-- endToc -->

## Introduction

This guide is for selecting a Reporter at run-time, by setting the value of an [Environment Variable](https://en.wikipedia.org/wiki/Environment_variable).

### Why

Sometimes different members of your team will want to use different diff programs for reporting. This feature allows everyone to have a different choice.

Alternatively, sometimes you might want to view the results of a failing test result in a different diff tool, without having to recompile your code.

### Warning!

Please don't use this as your first option, as it can add inconsistency with your build and someone else's. For example, if you are working alone on code, you can just set your reporter in code.

It's generally considered [poor practice](https://peterlyons.com/problog/2010/02/environment-variables-considered-harmful/) to use environment variables to control the behaviour of software builds and execution.

## Setting the Environment Variable

The environment value `APPROVAL_TESTS_USE_REPORTER` can be set, to select the diff tool to use to show differences, if an Approval Test fails.

For example, to set Araxis Merge as your reporter, set the `APPROVAL_TESTS_USE_REPORTER` environment value to `AraxisMerge`.

## Available Values

The following values of `APPROVAL_TESTS_USE_REPORTER` are currently recognised. See the next section for alternative variations on these names.

<!-- snippet: ReporterFactoryTests.Verify_all_valid_env_variable_values_-_on_Windows.approved.txt -->
<a id='snippet-ReporterFactoryTests.Verify_all_valid_env_variable_values_-_on_Windows.approved.txt'></a>
```txt
[0] = AutoApproveIfMissingReporter
[1] = AutoApproveReporter
[2] = CIBuildOnlyReporter
[3] = ClipboardReporter
[4] = DefaultFrontLoadedReporter
[5] = DefaultReporter
[6] = DiffReporter
[7] = EnvironmentVariableReporter
[8] = Linux::BeyondCompareReporter
[9] = Linux::KDiff3Reporter
[10] = Linux::MeldReporter
[11] = Linux::SublimeMergeReporter
[12] = Mac::AraxisMergeReporter
[13] = Mac::BeyondCompareReporter
[14] = Mac::CLionDiffReporter
[15] = Mac::DiffMergeReporter
[16] = Mac::KDiff3Reporter
[17] = Mac::KaleidoscopeReporter
[18] = Mac::P4MergeReporter
[19] = Mac::SublimeMergeReporter
[20] = Mac::TkDiffReporter
[21] = Mac::VisualStudioCodeReporter
[22] = QuietReporter
[23] = TextDiffReporter
[24] = Windows::AraxisMergeReporter
[25] = Windows::BeyondCompareReporter
[26] = Windows::CodeCompareReporter
[27] = Windows::KDiff3Reporter
[28] = Windows::SublimeMergeReporter
[29] = Windows::TortoiseDiffReporter
[30] = Windows::TortoiseGitDiffReporter
[31] = Windows::VisualStudioCodeReporter
[32] = Windows::WinMergeReporter

```
<sup><a href='/tests/DocTest_Tests/reporters/approval_tests/ReporterFactoryTests.Verify_all_valid_env_variable_values_-_on_Windows.approved.txt#L1-L34' title='File snippet `ReporterFactoryTests.Verify_all_valid_env_variable_values_-_on_Windows.approved.txt` was extracted from'>snippet source</a> | <a href='#snippet-ReporterFactoryTests.Verify_all_valid_env_variable_values_-_on_Windows.approved.txt' title='Navigate to start of snippet `ReporterFactoryTests.Verify_all_valid_env_variable_values_-_on_Windows.approved.txt`'>anchor</a></sup>
<!-- endSnippet -->

## Acceptable Variations

A fully qualified name is:

`Windows::AraxisMergerReporter`

This breaks down in to:

`{Windows::}{AraxisMerger}{Reporter}`

or:

`{OS::}{Program}{Reporter}`

1.  `{OS::}`
    * This is optional: it is one of `Mac::`, `Linux::` and `Windows::` and will be inferred if left out
    * Some reporters, such as `AutoApproveReporter`, don't have this component.
1.  `{Program}`
    * This is **required**.
1.  `{Reporter}`
    * This is optional, and is added if missing.

So, for example, on Windows, you can select `Windows::AraxisMergerReporter` by setting `APPROVAL_TESTS_USE_REPORTER` to any of the following values:

* `Windows::AraxisMergerReporter`
* `Windows::AraxisMerge`
* `AraxisMergerReporter`
* `AraxisMerge`

---

[Back to User Guide](/doc/README.md#top)
