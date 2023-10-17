<a id="top"></a>

# How to Submit a New Reporter to ApprovalTests

<!-- toc -->
## Contents

  * [Adding a new Mac reporter](#adding-a-new-mac-reporter)
    * [Implement the reporter](#implement-the-reporter)
      * [Edit ApprovalTests/reporters/DiffPrograms.h](#edit-approvaltestsreportersdiffprogramsh)
      * [Edit ApprovalTests/reporters/DiffPrograms.cpp](#edit-approvaltestsreportersdiffprogramscpp)
      * [Edit ApprovalTests/reporters/MacReporters.h](#edit-approvaltestsreportersmacreportersh)
      * [Edit ApprovalTests/reporters/MacReporters.cpp](#edit-approvaltestsreportersmacreporterscpp)
    * [Other files to edit](#other-files-to-edit)
      * [Edit ApprovalTests/reporters/ReporterFactory.cpp](#edit-approvaltestsreportersreporterfactorycpp)
      * [Edit tests/DocTest_Tests/reporters/CommandLineReporterTests.cpp](#edit-testsdoctest_testsreporterscommandlinereportertestscpp)
  * [Adding a new Windows reporter](#adding-a-new-windows-reporter)
  * [Adding a new Linux reporter](#adding-a-new-linux-reporter)
  * [Adding a new Cross Platform reporter](#adding-a-new-cross-platform-reporter)<!-- endToc -->

This guide is for figuring out how to make a more robust custom reporter, that you might want to submit back to us as a Pull Request.

For creating the ability to use a custom reporter that works on your machine, see [How to Use A Custom Reporter](/doc/how_tos/UseACustomReporter.md#top)

## Adding a new Mac reporter

By way of an example, for supporting a new Reporter on macOS, the steps are:

### Implement the reporter

#### Edit [ApprovalTests/reporters/DiffPrograms.h](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/DiffPrograms.h)

* Add a declaration for the new function to the `Mac` namespace.
* If you are adding a tool that is already supported on an existing platform, please try to be consistent with naming.

<!-- snippet: add_reporter_macro_header -->
<a id='snippet-add_reporter_macro_header'></a>
```h
DiffInfo ARAXIS_MERGE();
```
<sup><a href='/ApprovalTests/reporters/DiffPrograms.h#L18-L20' title='Snippet source file'>snippet source</a> | <a href='#snippet-add_reporter_macro_header' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

#### Edit [ApprovalTests/reporters/DiffPrograms.cpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/DiffPrograms.cpp)

* Add a new `APPROVAL_TESTS_MACROS_ENTRY` value to the `Mac` namespace, to create the definition for the new function.

<!-- snippet: add_reporter_macro_implementation -->
<a id='snippet-add_reporter_macro_implementation'></a>
```cpp
APPROVAL_TESTS_MACROS_ENTRY(
    ARAXIS_MERGE,
    DiffInfo("/Applications/Araxis Merge.app/Contents/Utilities/compare",
             Type::TEXT_AND_IMAGE))
```
<sup><a href='/ApprovalTests/reporters/DiffPrograms.cpp#L30-L35' title='Snippet source file'>snippet source</a> | <a href='#snippet-add_reporter_macro_implementation' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

#### Edit [ApprovalTests/reporters/MacReporters.h](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/MacReporters.h)

* Add a declaration for the new reporter.
* In the most common case, this will be a new implementation of `GenericDiffReporter`

<!-- snippet: add_reporter_class_header -->
<a id='snippet-add_reporter_class_header'></a>
```h
class AraxisMergeReporter : public GenericDiffReporter
{
public:
    AraxisMergeReporter();
};
```
<sup><a href='/ApprovalTests/reporters/MacReporters.h#L16-L22' title='Snippet source file'>snippet source</a> | <a href='#snippet-add_reporter_class_header' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

#### Edit [ApprovalTests/reporters/MacReporters.cpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/MacReporters.cpp)

* Add a definition for the new reporter.
* This will use the `APPROVAL_TESTS_MACROS_ENTRY` you added in the first step.

<!-- snippet: add_reporter_class_implementation -->
<a id='snippet-add_reporter_class_implementation'></a>
```cpp
AraxisMergeReporter::AraxisMergeReporter()
    : GenericDiffReporter(DiffPrograms::Mac::ARAXIS_MERGE())
{
}
```
<sup><a href='/ApprovalTests/reporters/MacReporters.cpp#L14-L19' title='Snippet source file'>snippet source</a> | <a href='#snippet-add_reporter_class_implementation' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

* Scroll to the end of this file, and add an instance of the new reporter class to the `MacDiffReporter`
    * The reporters are searched in order, so more commonly-used or highly-featured ones should go nearer the start.
    * Paid-for ones should go before free ones.

<!-- snippet: mac_diff_reporters -->
<a id='snippet-mac_diff_reporters'></a>
```cpp
new AraxisMergeReporter(),
new BeyondCompareReporter(),
new DiffMergeReporter(),
new KaleidoscopeReporter(),
new P4MergeReporter(),
new SublimeMergeReporter(),
new KDiff3Reporter(),
new TkDiffReporter(),
new VisualStudioCodeReporter(),
new CLionDiffReporter()
```
<sup><a href='/ApprovalTests/reporters/MacReporters.cpp#L63-L74' title='Snippet source file'>snippet source</a> | <a href='#snippet-mac_diff_reporters' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

### Other files to edit

#### Edit [ApprovalTests/reporters/ReporterFactory.cpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/ReporterFactory.cpp)

* Add a new `APPROVAL_TESTS_REGISTER_REPORTER` line, for your reporter class.

<!-- snippet: register_reporter_with_factory -->
<a id='snippet-register_reporter_with_factory'></a>
```cpp
APPROVAL_TESTS_REGISTER_REPORTER(Mac::AraxisMergeReporter);
APPROVAL_TESTS_REGISTER_REPORTER(Mac::BeyondCompareReporter);
APPROVAL_TESTS_REGISTER_REPORTER(Mac::DiffMergeReporter);
APPROVAL_TESTS_REGISTER_REPORTER(Mac::KaleidoscopeReporter);
APPROVAL_TESTS_REGISTER_REPORTER(Mac::P4MergeReporter);
APPROVAL_TESTS_REGISTER_REPORTER(Mac::SublimeMergeReporter);
APPROVAL_TESTS_REGISTER_REPORTER(Mac::KDiff3Reporter);
APPROVAL_TESTS_REGISTER_REPORTER(Mac::TkDiffReporter);
APPROVAL_TESTS_REGISTER_REPORTER(Mac::VisualStudioCodeReporter);
APPROVAL_TESTS_REGISTER_REPORTER(Mac::CLionDiffReporter);
```
<sup><a href='/ApprovalTests/reporters/ReporterFactory.cpp#L68-L79' title='Snippet source file'>snippet source</a> | <a href='#snippet-register_reporter_with_factory' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

#### Edit [tests/DocTest_Tests/reporters/CommandLineReporterTests.cpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/tests/DocTest_Tests/reporters/CommandLineReporterTests.cpp)

* Add an instance of the new Reporter class

<!-- snippet: add_reporter_command_test -->
<a id='snippet-add_reporter_command_test'></a>
```cpp
// Mac
std::make_shared<Mac::AraxisMergeReporter>(),
std::make_shared<Mac::BeyondCompareReporter>(),
std::make_shared<Mac::DiffMergeReporter>(),
std::make_shared<Mac::KaleidoscopeReporter>(),
std::make_shared<Mac::P4MergeReporter>(),
std::make_shared<Mac::SublimeMergeReporter>(),
std::make_shared<Mac::KDiff3Reporter>(),
std::make_shared<Mac::TkDiffReporter>(),
std::make_shared<Mac::VisualStudioCodeReporter>(),
std::make_shared<Mac::CLionDiffReporter>(),
```
<sup><a href='/tests/DocTest_Tests/reporters/CommandLineReporterTests.cpp#L27-L39' title='Snippet source file'>snippet source</a> | <a href='#snippet-add_reporter_command_test' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

* Run this test, review and accept the changes.

## Adding a new Windows reporter

The steps are the same as above, except that in the second step, you will edit:
 
* [ApprovalTests/reporters/WindowsReporters.h](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/WindowsReporters.h)
* [ApprovalTests/reporters/WindowsReporters.cpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/WindowsReporters.cpp)

## Adding a new Linux reporter

The steps are the same as above, except that in the second step, you will edit:

* [ApprovalTests/reporters/LinuxReporters.h](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/LinuxReporters.h)
* [ApprovalTests/reporters/LinuxReporters.cpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/LinuxReporters.cpp)

## Adding a new Cross Platform reporter

To add a reporter that will run on all 3 platforms, the steps are the same as above, except that in the second step, you will edit:

* [ApprovalTests/reporters/CrossPlatformReporters.h](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/CrossPlatformReporters.h)
* [ApprovalTests/reporters/CrossPlatformReporters.cpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/CrossPlatformReporters.cpp)

---

[Back to User Guide](/doc/README.md#top)
