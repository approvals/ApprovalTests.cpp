<a id="top"></a>

# ExceptionCollector

<!-- toc -->
## Contents

  * [Usage](#usage)<!-- endToc -->

## Usage

ExceptionCollector is a utility that allows you to have multiple exceptions thrown, without stopping the execution of the program, and then throw them all later.

<!-- snippet: exception_collector_template -->
<a id='snippet-exception_collector_template'></a>
```cpp
ApprovalTests::ExceptionCollector exceptions;

for (int i = 1; i <= 4; ++i)
{
    exceptions.gather([&]() { /* Code that may throw errors here */ });
}
exceptions.release(); // All errors actually thrown together here
```
<sup><a href='/tests/DocTest_Tests/utilities/ExceptionCollectorTests.cpp#L23-L31' title='Snippet source file'>snippet source</a> | <a href='#snippet-exception_collector_template' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

**Use with Approval Tests**: See [Approving multiple files in one test](/doc/MultipleOutputFilesPerTest.md#approving-multiple-files-in-one-test).

---

[Back to User Guide](/doc/README.md#top)
