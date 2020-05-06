<a id="top"></a>

# Reporters


toc


## Supported Diff Tools

The DiffReporter class goes through a chain of possible reporters to find the first option installed on your system.
Currently the search goes in this order:

### Mac

snippet: mac_diff_reporters

### Linux

snippet: linux_diff_reporters

### Windows

snippet: windows_diff_reporters

## Registering a default reporter

At present, the default Reporter is the DiffReporter. Whenever you call Approvals, you have the chance to pass in your own Reporter. However, if you would like to change what the default reporter is when you don't pass in a specific Reporter, you can do this at a global or per-test level, by adding the line:

snippet: use_as_default_reporter_in_main

The return value is ["Disposable"](/doc/DisposableObjects.md#top), meaning it will restore the original reporter when the object destructs. Because of this, if you do not store the result in a variable, it will immediately undo itself by the end of the line.

## Front Loaded Reporters

By default, Approval tests will not launch any reporters on supported CI machines. To do this, we use front loaded reporters...

Front loaded reporters allow you to block all normal reporting behaviour. This is useful in situations like running on a CI Machine, where you wouldn't want a reporter to open.

For more information, see [Build Machines and Continuous Integration servers](/doc/BuildMachinesAndCI.md#top).

Here is an example of not launching any reporters if you are on a machine with a particular name, by using [BlockingReporter](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/BlockingReporter.h).

snippet: do_not_report_on_named_machine

Once you have added that, even calling approvals with a specific Reporter will not launch it on the CI system (but will for all other systems). For example:

snippet: basic_approval_with_reporter 

### Blocking Reporters

Blocking reporters are a simple class, designed for use with FrontLoadedReporters, to prevent launching of reporters in certain environments.

snippet: do_not_report_on_named_machine

## Miscellaneous Helper Reporters

While most reporters open some sort of external program, for the purpose of understanding how the tests went wrong, and verifying the correct answer, there are some reporters that are helpful for specific situations.

### Auto-approving

There are three reporters that can help with the approving of single or multiple tests.

* `AutoApproveIfMissingReporter`: if there is no approved file already, the received file will automatically be copied over the approved one. Otherwise, it does nothing. One possible cause for confusion here is if you ran the test previously with a standard reporter, that will have created an almost-empty approved file, which will then block this from working.
* `ClipboardReporter`: this puts the command-line to moved the approve file on to your computer's clipboard. You then review this, and paste it in to a terminal window. This only works with one test at a time.
* `AutoApproveReporter`: be careful, this will overwrite every existing ".approved" file, with no confirmation. This is best used when you are expecting large numbers of files that are already version-controlled to be updated, and you would rather review the changes in your version control system. 


---

[Back to User Guide](/doc/README.md#top)
