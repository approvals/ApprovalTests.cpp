<a id="top"></a>

# Multiple output files per test

<!-- toc -->
## Contents

  * [Introduction](#introduction)
  * [Scenarios](#scenarios)
  * [Mechanisms](#mechanisms)
    * [Catch2](#catch2)
    * [doctest](#doctest)
    * [Approval Tests](#approval-tests)
  * [Approving multiple files in one test](#approving-multiple-files-in-one-test)<!-- endToc -->

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

<!-- snippet: catch2_multiple_output_files_dynamic -->
<a id='snippet-catch2_multiple_output_files_dynamic'></a>
```cpp
TEST_CASE("MultipleOutputFiles-DataDriven")
{
    // This is an example of how to write multiple different files in a single test.
    // Note: For data as small as this, in practice we would recommend passing the
    // greetings container in to Approvals::verifyAll(), with a lambda to format the output,
    // in order to write all data to a single file.
    std::vector<Greeting> greetings{
        Greeting(British), Greeting(American), Greeting(French)};
    for (auto greeting : greetings)
    {
        SECTION(greeting.getNationality())
        {
            ApprovalTests::Approvals::verify(greeting.getGreeting());
        }
    }
}
```
<sup><a href='/tests/Catch2_Tests/docs/Catch2DocsSamples.cpp#L59-L76' title='Snippet source file'>snippet source</a> | <a href='#snippet-catch2_multiple_output_files_dynamic' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Or hard-coded, with multiple sections:

<!-- snippet: catch2_multiple_output_files_hard_coded -->
<a id='snippet-catch2_multiple_output_files_hard_coded'></a>
```cpp
TEST_CASE("MultipleOutputFiles-ForOneObject")
{
    Greeting object_under_test;
    SECTION("British")
    {
        ApprovalTests::Approvals::verify(object_under_test.getGreetingFor(British));
    }
    SECTION("American")
    {
        ApprovalTests::Approvals::verify(object_under_test.getGreetingFor(American));
    }
    SECTION("French")
    {
        ApprovalTests::Approvals::verify(object_under_test.getGreetingFor(French));
    }
}
```
<sup><a href='/tests/Catch2_Tests/docs/Catch2DocsSamples.cpp#L78-L95' title='Snippet source file'>snippet source</a> | <a href='#snippet-catch2_multiple_output_files_hard_coded' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Note: Catch2 sub-sections continue to run even if the previous one failed. This is useful, as it allows you to approve all the files in one test run.

### doctest

You can have a file-per-subcase.

Note: unlike Catch, doctest sub-cases must have static strings for names, so if you want to name things dynamically, you will have to use the native Approval Tests mechanism - see below.

You can have hard-coded, with multiple sections:

<!-- snippet: doctest_multiple_output_files_hard_coded -->
<a id='snippet-doctest_multiple_output_files_hard_coded'></a>
```cpp
TEST_CASE("MultipleOutputFiles-ForOneObject")
{
    using namespace ApprovalTests;

    Greeting object_under_test;
    SUBCASE("British")
    {
        Approvals::verify(object_under_test.getGreetingFor(British));
    }
    SUBCASE("American")
    {
        Approvals::verify(object_under_test.getGreetingFor(American));
    }
    SUBCASE("French")
    {
        Approvals::verify(object_under_test.getGreetingFor(French));
    }
}
```
<sup><a href='/tests/DocTest_Tests/docs/DocTestDocsSamples.cpp#L62-L81' title='Snippet source file'>snippet source</a> | <a href='#snippet-doctest_multiple_output_files_hard_coded' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

### Approval Tests

Approval Tests also allows for multiple files per test, via the `NamerFactory`. This works for all supported test frameworks.

You can either do these dynamically, e.g. in a for-loop:

<!-- snippet: approvals_multiple_output_files_dynamic -->
<a id='snippet-approvals_multiple_output_files_dynamic'></a>
```cpp
TEST_CASE("ApprovalTests-MultipleOutputFiles-DataDriven")
{
    using namespace ApprovalTests;

    // This is an example of how to write multiple different files in a single test.
    // Note: For data as small as this, in practice we would recommend passing the
    // greetings container in to Approvals::verifyAll(), with a lambda to format the output,
    // in order to write all data to a single file.
    std::vector<Greeting> greetings{
        Greeting(British), Greeting(American), Greeting(French)};
    for (auto greeting : greetings)
    {
        auto section = NamerFactory::appendToOutputFilename(greeting.getNationality());
        Approvals::verify(greeting.getGreeting());
    }
}
```
<sup><a href='/tests/DocTest_Tests/docs/DocTestDocsSamples.cpp#L83-L100' title='Snippet source file'>snippet source</a> | <a href='#snippet-approvals_multiple_output_files_dynamic' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Or hard-coded, with multiple sections:

<!-- snippet: approvals_multiple_output_files_hard_coded -->
<a id='snippet-approvals_multiple_output_files_hard_coded'></a>
```cpp
TEST_CASE("ApprovalTests-MultipleOutputFiles-ForOneObject")
{
    using namespace ApprovalTests;

    Greeting object_under_test;
    {
        auto section = NamerFactory::appendToOutputFilename("British");
        Approvals::verify(object_under_test.getGreetingFor(British));
    }
    {
        auto section = NamerFactory::appendToOutputFilename("American");
        Approvals::verify(object_under_test.getGreetingFor(American));
    }
    {
        auto section = NamerFactory::appendToOutputFilename("French");
        Approvals::verify(object_under_test.getGreetingFor(French));
    }
}
```
<sup><a href='/tests/DocTest_Tests/docs/DocTestDocsSamples.cpp#L102-L121' title='Snippet source file'>snippet source</a> | <a href='#snippet-approvals_multiple_output_files_hard_coded' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Approving multiple files in one test

Often, when you have multiple output files in one test, there is an annoyance that you have to run the test multiple times, once per output file. This is because Approvals throws an exception after each test failure, which the test framework immediately traps as a failure,  stopping your test from writing the remaining files.

There are two things that work well to do this.

First, you can use an [ExceptionCollector](/doc/Utilities.md#exceptioncollector) so that the test does not stop after the first failure.

Second, you can use [AutoApproveIfMissingReporter](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/AutoApproveIfMissingReporter.h) so that the first time a verify is run, it is automatically approving the result. There are more options in [Auto-approving](/doc/Reporters.md#auto-approving)

For example:

<!-- snippet: approvals_multiple_output_files_auto_approving -->
<a id='snippet-approvals_multiple_output_files_auto_approving'></a>
```cpp
TEST_CASE("ApprovalTests-MultipleOutputFiles-AutoApprove")
{
    using namespace ApprovalTests;

    ExceptionCollector exceptions; // Allow all files to be written, regardless of errors
    std::vector<Greeting> greetings{
        Greeting(British), Greeting(American), Greeting(French)};
    for (auto greeting : greetings)
    {
        auto section = NamerFactory::appendToOutputFilename(greeting.getNationality());
        exceptions.gather([&]() {
            Approvals::verify(
                greeting.getGreeting(),
                Options(
                    AutoApproveIfMissingReporter())); // Automatically approve first time
        });
    }
    exceptions.release();
}
```
<sup><a href='/tests/DocTest_Tests/docs/DocTestDocsSamples.cpp#L123-L143' title='Snippet source file'>snippet source</a> | <a href='#snippet-approvals_multiple_output_files_auto_approving' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

---

[Back to User Guide](/doc/README.md#top)
