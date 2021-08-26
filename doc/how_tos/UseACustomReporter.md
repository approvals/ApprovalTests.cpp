<a id="top"></a>

# How to Use A Custom Reporter

<!-- toc -->
<!-- endToc -->

This guide is for creating the ability to use a custom reporter that works on your machine.

For figuring out how to make a more robust custom reporter, that you might want to submit back to us as a Pull Request, check out [How to Submit a New Reporter to ApprovalTests](/doc/how_tos/SubmitANewReporterToApprovalTests.md#top).

Let's say that you really enjoy using Sublime Merge, and on your system it's located in `"/Applications/Sublime Merge.app/Contents/SharedSupport/bin/smerge"`

If you were to run this the command line, the full command would look this this:

<!-- snippet: CustomReporterTests.Creating_Custom_Reporters.approved.txt -->
<a id='snippet-CustomReporterTests.Creating_Custom_Reporters.approved.txt'></a>
```txt
"/Applications/Sublime Merge.app/Contents/SharedSupport/bin/smerge" mergetool --no-wait "test.received.txt" "test.approved.txt" -o "test.approved.txt" &
```
<sup><a href='/tests/DocTest_Tests/reporters/approval_tests/CustomReporterTests.Creating_Custom_Reporters.approved.txt#L1-L1' title='Snippet source file'>snippet source</a> | <a href='#snippet-CustomReporterTests.Creating_Custom_Reporters.approved.txt' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

You can do this simply by creating a Reporter using:

<!-- snippet: use_custom_reporter -->
<a id='snippet-use_custom_reporter'></a>
```cpp
auto path = "/Applications/Sublime Merge.app/Contents/SharedSupport/bin/smerge";
auto arguments = "mergetool --no-wait {Received} {Approved} -o {Approved}";
auto reporter = ApprovalTests::CustomReporter::create(path, arguments);
```
<sup><a href='/tests/DocTest_Tests/reporters/CustomReporterTests.cpp#L7-L11' title='Snippet source file'>snippet source</a> | <a href='#snippet-use_custom_reporter' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

By default, this will run in the background. Most of the time this is what you want.

However, you can force it to run in the foreground with:

<!-- snippet: use_custom_foreground_reporter -->
<a id='snippet-use_custom_foreground_reporter'></a>
```cpp
auto reporter =
    ApprovalTests::CustomReporter::createForegroundReporter(path, arguments);
```
<sup><a href='/tests/DocTest_Tests/reporters/CustomReporterTests.cpp#L39-L42' title='Snippet source file'>snippet source</a> | <a href='#snippet-use_custom_foreground_reporter' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

On Windows, you can specify a search path for the installed location of a program with `{ProgramFiles}`.

<!-- snippet: use_custom_windows_reporter -->
<a id='snippet-use_custom_windows_reporter'></a>
```cpp
auto path = "{ProgramFiles}Beyond Compare 4\\BCompare.exe";
auto reporter = ApprovalTests::CustomReporter::create(path);
```
<sup><a href='/tests/DocTest_Tests/reporters/CustomReporterTests.cpp#L21-L24' title='Snippet source file'>snippet source</a> | <a href='#snippet-use_custom_windows_reporter' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

See [Registering a default reporter](/doc/Reporters.md#registering-a-default-reporter) for wiring up this reporter as default, or you can dereference it and pass it in to individual `verify("text", *reporter)` method calls...

---

[Back to User Guide](/doc/README.md#top)
