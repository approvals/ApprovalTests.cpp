<a id="top"></a>

# Features



toc

## Customizing Google Tests Approval File Names

See [Using Approval Tests With Google Tests](/doc/UsingGoogleTests.md#customizing-google-tests-approval-file-names)

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

See [Using sub-directories for approved files](/doc/Configuration.md#using-sub-directories-for-approved-files)


---

[Back to User Guide](/doc/README.md#top)
