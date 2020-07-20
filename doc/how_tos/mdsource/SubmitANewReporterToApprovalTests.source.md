<a id="top"></a>

# How to Submit a New Reporter to ApprovalTests

toc

This guide is for figuring out how to make a more robust custom reporter, that you might want to submit back to us as a Pull Request.

For creating the ability to use a custom reporter that works on your machine, see [How to Use A Custom Reporter](/doc/how_tos/UseACustomReporter.md#top)

## Adding a new Mac reporter

By way of an example, for supporting a new Reporter on macOS, the steps are:

### Edit [ApprovalTests/reporters/DiffPrograms.h](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/DiffPrograms.h)

* Add a declaration for the new function to the `Mac` namespace.
* If you are adding a tool that is already supported on an existing platform, please try to be consistent with naming.

snippet: add_reporter_macro_header

### Edit [ApprovalTests/reporters/DiffPrograms.cpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/DiffPrograms.cpp)

* Add a new `APPROVAL_TESTS_MACROS_ENTRY` value to the `Mac` namespace, to create the definition for the new function.

snippet: add_reporter_macro_implementation

### Edit [ApprovalTests/reporters/MacReporters.h](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/MacReporters.h)

* Add a declaration for the new reporter.
* In the most common case, this will be a new implementation of `GenericDiffReporter`

snippet: add_reporter_class_header

### Edit [ApprovalTests/reporters/MacReporters.cpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/MacReporters.cpp)

* Add a definition for the new reporter.
* This will use the `APPROVAL_TESTS_MACROS_ENTRY` you added in the first step.

snippet: add_reporter_class_implementation

* Scroll to the end of this file, and add an instance of the new reporter class to the `MacDiffReporter`
    * The reporters are searched in order, so more commonly-used or highly-featured ones should go nearer the start.
    * Paid-for ones should go before free ones.

snippet: mac_diff_reporters

### Edit [tests/DocTest_Tests/reporters/CommandLineReporterTests.cpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/tests/DocTest_Tests/reporters/CommandLineReporterTests.cpp)

* Add an instance of the new Reporter class

snippet: add_reporter_command_test

* Run this test, review and accept the changes.

## Adding a new Windows reporter

The steps are the same as above, except that in the second step, you will edit:
 
* [ApprovalTests/reporters/WindowsReporters.h](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/WindowsReporters.h)
* [ApprovalTests/reporters/WindowsReporters.cpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/WindowsReporters.cpp)

## Adding a new Linux reporter

The steps are the same as above, except that in the second step, you will edit:

* [ApprovalTests/reporters/LinuxReporters.h](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/LinuxReporters.h)
* [ApprovalTests/reporters/LinuxReporters.cpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/LinuxReporters.cpp)


---

[Back to User Guide](/doc/README.md#top)
