<a id="top"></a>

# Utilities

<!-- toc -->
## Contents

  * [DateUtils](#dateutils)
  * [ExceptionCollector](#exceptioncollector)<!-- endToc -->

## DateUtils

You can easily create and print C++11 dates and times.

For example:

<!-- snippet: date_and_time -->
<a id='snippet-date_and_time'></a>
```cpp
std::chrono::system_clock::time_point dateTime =
    DateUtils::createUtcDateTime(2000, 1, 13, 3, 34, 45);

std::string dateTimeString = DateUtils::toString(dateTime);
```
<sup><a href='/tests/DocTest_Tests/utilities/DateUtilsTests.cpp#L9-L14' title='File snippet `date_and_time` was extracted from'>snippet source</a> | <a href='#snippet-date_and_time' title='Navigate to start of snippet `date_and_time`'>anchor</a></sup>
<!-- endSnippet -->

will produce:

<!-- snippet: DateUtilsTests.createDateTime.approved.txt -->
<a id='snippet-DateUtilsTests.createDateTime.approved.txt'></a>
```txt
Thu 2000-01-13 03:34:45 UTC
```
<sup><a href='/tests/DocTest_Tests/utilities/approval_tests/DateUtilsTests.createDateTime.approved.txt#L1-L1' title='File snippet `DateUtilsTests.createDateTime.approved.txt` was extracted from'>snippet source</a> | <a href='#snippet-DateUtilsTests.createDateTime.approved.txt' title='Navigate to start of snippet `DateUtilsTests.createDateTime.approved.txt`'>anchor</a></sup>
<!-- endSnippet -->

Times are printed in UTC, as this is a testing utility and consistency across machines is desirable.

There is an overload of `DateUtils::toString()` that takes a [format string](https://en.cppreference.com/w/cpp/io/manip/put_time), should you wish to print it differently.


## ExceptionCollector

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
<sup><a href='/tests/DocTest_Tests/utilities/ExceptionCollectorTests.cpp#L25-L32' title='File snippet `exception_collector_template` was extracted from'>snippet source</a> | <a href='#snippet-exception_collector_template' title='Navigate to start of snippet `exception_collector_template`'>anchor</a></sup>
<!-- endSnippet -->

**Use with Approval Tests**: See [Approving multiple files in one test](/doc/MultipleOutputFilesPerTest.md#approving-multiple-files-in-one-test).

---

[Back to User Guide](/doc/README.md#top)
