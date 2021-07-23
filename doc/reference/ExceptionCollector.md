<a id="top"></a>

# ExceptionCollector

<!-- toc -->
## Contents

  * [Scrubbers](#scrubbers)
  * [Lambda example](#lambda-example)
  * [Pre-made Scrubbers](#pre-made-scrubbers)
    * [Regular Expressions (regex)](#regular-expressions-regex)
      * [API for scrubbing with regex](#api-for-scrubbing-with-regex)
      * [Using a regex search term](#using-a-regex-search-term)
      * [Using a lambda for greater control of replacement text](#using-a-lambda-for-greater-control-of-replacement-text)
      * [See also](#see-also)
    * [GUID](#guid)<!-- endToc -->

## Usage

ExceptionCollector is a utility that allows you to have multiple exceptions thrown, without stopping the execution of the program, and then throw them all later.

<!-- snippet: exception_collector_template -->
<a id='snippet-exception_collector_template'></a>
```cpp
ExceptionCollector exceptions;
for (int i = 1; i <= 4; ++i)
{
    exceptions.gather([&]() { /* Code that may throw errors here */ });
}
exceptions.release(); // All errors actually thrown together here
```
<sup><a href='/tests/DocTest_Tests/utilities/ExceptionCollectorTests.cpp#L25-L32' title='Snippet source file'>snippet source</a> | <a href='#snippet-exception_collector_template' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

**Use with Approval Tests**: See [Approving multiple files in one test](/doc/MultipleOutputFilesPerTest.md#approving-multiple-files-in-one-test).

---

[Back to User Guide](/doc/README.md#top)
