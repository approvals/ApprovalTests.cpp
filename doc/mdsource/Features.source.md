<a id="top"></a>

# Features



<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Contents**

- [Blocking Reporter](#blocking-reporter)
- [Machine Blockers](#machine-blockers)
- [Front Loaded Reporters](#front-loaded-reporters)
- [Using sub-directories for approved files](#using-sub-directories-for-approved-files)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## Blocking Reporter

Blocking reporters are a simple class, designed for use with FrontLoadedReporters, to prevent launching of reporters in certain environments.

snippet: do_not_report_on_ci

## Machine Blockers

Sometimes you will want tests to only run on certain machines. Machine blockers are a great way to do this.

snippet: machine_specific_test_runner

## Front Loaded Reporters

Other times, you will want to run the tests on all machines, but only report if certain conditions are true. Front loaded reporters allow a mechanism to jump in front of the standard Reporter path, and divert early.

Here is an example of not launching any reporters of you are on the CI machine.

snippet: do_not_report_on_ci

Once you have added that, even calling approvals with a specific Reporter will not launch it on the CI system (but will for all other systems). For example:

snippet: basic_approval_with_reporter 

## Using sub-directories for approved files

If you have a lot of approval files, you might want to put them in a subdirectory, to prevent them cluttering up your source files. You can do this at a global or per-test level, by adding the line:

snippet: use_subdirectory_in_main

The return value will restore the original directory when the object destructs. Because of this, if you do not store the result in a variable, it will immediately undo itself by the end of the line.

This mechanism allows you to select a different sub-directory in individual tests.


---

[Back to User Guide](/doc/README.md#top)
