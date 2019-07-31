<a id="top"></a>

# Setup

toc

There are three different places you might be starting your setup from.

Here's how to set up from:

## I have nothing

If you just want to start doing some TDD with Approval Tests:

1.  download the [ApprovalTests.cpp.StarterProject](https://github.com/approvals/ApprovalTests.cpp.StarterProject)
1. download a [Supported Diff Tool](/doc/Reporters.md#supported-diff-tools)
1. Run the existing tests from the project (they should pass).
1. Then open the file [`tests/NewTest.cpp`](https://github.com/approvals/ApprovalTests.cpp.StarterProject/blob/master/tests/NewTest.cpp), choose which of the three starting points you want, and Go!

## I have code but no tests

[Choose a testing framework](/doc/GettingStarted.md#choosing-a-testing-framework).

Then continue to the next section... 

## I have tests and code and want to add Approval Tests

1. [Download the single header file](https://github.com/approvals/ApprovalTests.cpp/releases)
1. Do one of:
    * [Add a wrapper header](https://raw.githubusercontent.com/approvals/ApprovalTests.cpp.StarterProject/master/lib/ApprovalTests.hpp)
    * Rename the header file to `ApprovalTests.hpp` (removing its version number)
1. Set up your `main()` (this is framework-dependent:
    * [Using Approval Tests With Catch](/doc/UsingCatch.md#top)
    * [Using Approval Tests With Google Tests](/doc/UsingGoogleTests.md#top)
    * [Using Approval Tests With Doctest](/doc/UsingDoctest.md#top)
1. Download a [Supported Diff Tool](/doc/Reporters.md#supported-diff-tools)

If you current test framework is not supported, see [Supporting a new test framework](/doc/SupportingNewTestFramework.md#top)

---

[Back to User Guide](/doc/README.md#top)
