<a id="top"></a>

# Multiple output files per test

toc

## Introduction

ApprovalTests uses the name of the current test to determine the names of output files that it writes. This means that **by default, there is only one approval file per test case**.

However, sometimes it is useful to be able to verify multiple files in one test case, or have a file per OS or other environment configuration.

## Scenarios

Here are some examples of files you might want.

&nbsp;

**Multiple data inputs:**

In this scenario, your test creates 3 files, all of which are being checked when you run the test.

```text
TestProteinGeneration.createImage.protein1.approved.png
TestProteinGeneration.createImage.protein2.approved.png
TestProteinGeneration.createImage.protein3.approved.png
```

&nbsp;

**Multiple outputs:**

In this scenario, the code under test creates three different types of files, all of which are being checked.

```text
TestProtein.processInput.logOutput.approved.txt
TestProtein.processInput.calculationResults.approved.txt
TestProtein.processInput.renderedResult.approved.png
```

&nbsp;

**Multiple environments:**

In this scenario, your test only creates one file, and which one it is checked against is dependent on which OS the test is running on.

```text
TestQtDialog.loginScreen.onMacOSX.approved.png
TestQtDialog.loginScreen.onWindows.approved.png
TestQtDialog.loginScreen.onLinux.approved.png
```

&nbsp;

## Mechanisms

Here are a few ways to do that.

### Catch2

You can have a file-per-subsection.

You can either do these dynamically, e.g. in a for-loop:

snippet: catch2_multiple_output_files_dynamic

Or hard-coded, with multiple sections:

snippet: catch2_multiple_output_files_hard_coded

Note: Catch2 sub-sections continue to run even if the previous one failed. This is useful, as it allows you to approve all the files in one test run.

### doctest

You can have a file-per-subcase.

Note: unlike Catch, doctest sub-cases must have static strings for names, so if you want to name things dynamically, you will have to use the native Approval Tests mechanism - see below.

You can have hard-coded, with multiple sections:

snippet: doctest_multiple_output_files_hard_coded

### Approval Tests

Approval Tests also allows for multiple files per test, via the `NamerFactory`. This works for all supported test frameworks.

You can either do these dynamically, e.g. in a for-loop:

snippet: approvals_multiple_output_files_dynamic

Or hard-coded, with multiple sections:

snippet: approvals_multiple_output_files_hard_coded

## Approving multiple files in one test

Often, when you have multiple output files in one test, there is an annoyance that you have to run the test multiple times, once per output file. This is because Approvals throws an exception after each test failure, which the test framework immediately traps as a failure,  stopping your test from writing the remaining files.

There are two things that work well to do this.

First, you can use an [ExceptionCollector](/doc/Utilities.md#exceptioncollector) so that the test does not stop after the first failure.

Second, you can use [AutoApproveIfMissingReporter](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/AutoApproveIfMissingReporter.h) so that the first time a verify is run, it is automatically approving the result. There are more options in [Auto-approving](/doc/Reporters.md#auto-approving)

For example:

snippet: approvals_multiple_output_files_auto_approving
 


---

[Back to User Guide](/doc/README.md#top)
