<a id="top"></a>

# How to Select a Reporter with an Environment Variable

<!-- toc -->
## Contents

  * [Introduction](#introduction)
    * [Why](#why)
    * [Warning!](#warning)
  * [Setting the Environment Variable](#setting-the-environment-variable)
  * [Available Values](#available-values)
  * [Acceptable Variations](#acceptable-variations)
  * [Other Information](#other-information)<!-- endToc -->

## Introduction

This guide is for selecting a Reporter at run-time, by setting the value of an [Environment Variable](https://en.wikipedia.org/wiki/Environment_variable).

### Why

Sometimes different members of your team will want to use different diff programs for reporting. This feature allows everyone to have a different choice.

Alternatively, sometimes you might want to view the results of a failing test result in a different diff tool, without having to recompile your code.

### Warning!

Please don't use this as your first option, as it can add inconsistency with your build and someone else's. For example, if you are working alone on code, you can just set your reporter in code.

It's generally considered [poor practice](https://peterlyons.com/problog/2010/02/environment-variables-considered-harmful/) to use environment variables to control the behaviour of software builds and execution.

## Setting the Environment Variable

The environment value `APPROVAL_TESTS_USE_REPORTER` can be set, to select the diff tool to use to show differences, if
an Approval Test fails.

For example, to set Araxis Merge as your reporter, set the `APPROVAL_TESTS_USE_REPORTER` environment value
to `AraxisMerge`.

## Available Values

The following values of `APPROVAL_TESTS_USE_REPORTER` are currently recognised. See the next section for alternative
variations on these names.

<!-- snippet: ReporterFactoryTests.Verify_all_valid_env_var_values.approved.txt -->
<a id='snippet-ReporterFactoryTests.Verify_all_valid_env_var_values.approved.txt'></a>
```txt
AutoApproveIfMissingReporter
AutoApproveReporter
CIBuildOnlyReporter
ClipboardReporter
CrossPlatform::VisualStudioCodeReporter
DefaultFrontLoadedReporter
DefaultReporter
DiffReporter
EnvironmentVariableReporter
Linux::BeyondCompareReporter
Linux::KDiff3Reporter
Linux::MeldReporter
Linux::SublimeMergeReporter
Mac::AraxisMergeReporter
Mac::BeyondCompareReporter
Mac::CLionDiffReporter
Mac::DiffMergeReporter
Mac::KDiff3Reporter
Mac::KaleidoscopeReporter
Mac::P4MergeReporter
Mac::SublimeMergeReporter
Mac::TkDiffReporter
Mac::VisualStudioCodeReporter
QuietReporter
TextDiffReporter
Windows::AraxisMergeReporter
Windows::BeyondCompareReporter
Windows::CodeCompareReporter
Windows::KDiff3Reporter
Windows::SublimeMergeReporter
Windows::TortoiseDiffReporter
Windows::TortoiseGitDiffReporter
Windows::VisualStudioCodeReporter
Windows::WinMergeReporter
```
<sup><a href='/tests/DocTest_Tests/reporters/approval_tests/ReporterFactoryTests.Verify_all_valid_env_var_values.approved.txt#L1-L35' title='Snippet source file'>snippet source</a> | <a href='#snippet-ReporterFactoryTests.Verify_all_valid_env_var_values.approved.txt' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Acceptable Variations

A fully qualified name is:

`Windows::AraxisMergerReporter`

This breaks down in to:

`{Windows::}{AraxisMerger}{Reporter}`

or:

`{OS::}{Program}{Reporter}`

1. `{OS::}`
    * This is optional: it is one of `Mac::`, `Linux::` and `Windows::` and will be inferred if left out
    * Some reporters, such as `AutoApproveReporter`, don't have this component.
1. `{Program}`
    * This is **required**.
1. `{Reporter}`
    * This is optional, and is added if missing.

So, for example, on Windows, you can select `Windows::AraxisMergerReporter` by setting `APPROVAL_TESTS_USE_REPORTER` to any of the following values:

* `Windows::AraxisMergerReporter`
* `Windows::AraxisMerge`
* `AraxisMergerReporter`
* `AraxisMerge`

## Other Information

This environment value is ignored on [Continuous Integration builds](/doc/BuildMachinesAndCI.md#top).

---

[Back to User Guide](/doc/README.md#top)
