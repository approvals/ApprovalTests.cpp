<a id="top"></a>

# DateUtils

<!-- toc -->
## Contents

  * [Usage](#usage)<!-- endToc -->

## Usage

You can easily create and print C++11 dates and times.

For example:

<!-- snippet: date_and_time -->
<a id='snippet-date_and_time'></a>
```cpp
std::chrono::system_clock::time_point dateTime =
    ApprovalTests::DateUtils::createUtcDateTime(2000, 1, 13, 3, 34, 45);

std::string dateTimeString = ApprovalTests::DateUtils::toString(dateTime);
```
<sup><a href='/tests/DocTest_Tests/utilities/DateUtilsTests.cpp#L7-L12' title='Snippet source file'>snippet source</a> | <a href='#snippet-date_and_time' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

will produce:

<!-- snippet: DateUtilsTests.createDateTime.approved.txt -->
<a id='snippet-DateUtilsTests.createDateTime.approved.txt'></a>
```txt
Thu 2000-01-13 03:34:45 UTC
```
<sup><a href='/tests/DocTest_Tests/utilities/approval_tests/DateUtilsTests.createDateTime.approved.txt#L1-L1' title='Snippet source file'>snippet source</a> | <a href='#snippet-DateUtilsTests.createDateTime.approved.txt' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Times are printed in UTC, as this is a testing utility and consistency across machines is desirable.

There is an overload of `DateUtils::toString()` that takes a [format string](https://en.cppreference.com/w/cpp/io/manip/put_time), should you wish to print it differently.


---

[Back to User Guide](/doc/README.md#top)
