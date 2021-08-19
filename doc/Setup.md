<a id="top"></a>

# Setup Options

<!-- toc -->
## Contents

  * [I have nothing](#i-have-nothing)
  * [I have code but no tests](#i-have-code-but-no-tests)
  * [I have tests and code and want to add Approval Tests](#i-have-tests-and-code-and-want-to-add-approval-tests)
    * [Next Steps](#next-steps)<!-- endToc -->

There are three different places you might be starting your setup from.

Here's how to set up from:

## I have nothing

This is when you are interested in how Approval Tests work and want to see Approval Tests in action using our provided examples.

If you just want to start doing some TDD with Approval Tests, the [Tutorial will walk you through the following broad steps](/doc/Tutorial.md#top):

1. download the [ApprovalTests.cpp.StarterProject](https://github.com/approvals/ApprovalTests.cpp.StarterProject)
1. download a [Supported Diff Tool](/doc/Reporters.md#supported-diff-tools)
1. Run the existing tests from the project (they should pass).
1. Then open the file [`tests/NewTest.cpp`](https://github.com/approvals/ApprovalTests.cpp.StarterProject/blob/master/tests/NewTest.cpp), choose which of the three starting points you want, and Go!

## I have code but no tests

This is when you have an existing code base that you would like to start testing, as you don't yet have any tests at all.

Start by [choose a testing framework](/doc/GettingStarted.md#choosing-a-testing-framework).

Then continue to the next section... 

## I have tests and code and want to add Approval Tests

This is when you have an existing code base that has some tests already, and you would like to improve test coverage.

1. [Download the single header file](https://github.com/approvals/ApprovalTests.cpp/releases)
1. Do one of:
    * [Add a wrapper header](https://raw.githubusercontent.com/approvals/ApprovalTests.cpp.StarterProject/master/lib/ApprovalTests.hpp)
    * Rename the header file to `ApprovalTests.hpp` (removing its version number)
1. Set up your `main()` (this is framework-dependent):
    * [Using Approval Tests With Catch](/doc/UsingCatch.md#top)
    * [Using Approval Tests With CppUTest](/doc/UsingCppUTest.md#top)
    * [Using Approval Tests With Google Tests](/doc/UsingGoogleTests.md#top)
    * [Using Approval Tests With Doctest](/doc/UsingDoctest.md#top)
    * [Using Approval Tests With Boost.Test](/doc/UsingBoostTest.md#top)
    * [Using Approval Tests With \[Boost\].UT](/doc/UsingUT.md#top)
1. Download a [Supported Diff Tool](/doc/Reporters.md#supported-diff-tools)

If you current test framework is not supported, see [Supporting a new test framework](/doc/SupportingNewTestFramework.md#top)

### Next Steps

*  Try the [Tutorial](/doc/Tutorial.md#top)
---

[Back to User Guide](/doc/README.md#top)
