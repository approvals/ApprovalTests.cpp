<a id="top"></a>

# Utilities

toc

## DateUtils

You can easily create and print C++11 dates and times.

For example:

snippet: date_and_time

will produce:

snippet: DateUtilsTests.createDateTime.approved.txt

Times are printed in UTC, as this is a testing utility and consistency across machines is desirable.

There is an overload of `DateUtils::toString()` that takes a format string, should you wish to print it differently.


## ExceptionCollector

ExceptionCollector is a utility that allows you to have multiple exceptions thrown, without stopping the execution of the program, and then throw them all later.

snippet: exception_collector_template

**Use with Approval Tests**: See [Approving multiple files in one test](/doc/MultipleOutputFilesPerTest.md#approving-multiple-files-in-one-test).

---

[Back to User Guide](/doc/README.md#top)
