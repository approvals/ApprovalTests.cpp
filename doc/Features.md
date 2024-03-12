<a id="top"></a>

# Features

<!-- toc -->
## Contents

  * [v.x.y.z](#vxyz)
  * [v.10.13.0](#v10130)
    * [Catch2 v3 support](#catch2-v3-support)
  * [v.10.12.0](#v10120)
    * [EmptyFileCreatorByType::registerCreator](#emptyfilecreatorbytyperegistercreator)
  * [v.10.11.0](#v10110)
    * [useFileNameSanitizer](#usefilenamesanitizer)
    * [useEmptyFileCreator](#useemptyfilecreator)
  * [v.10.10.0](#v10100)
    * [Storyboard](#storyboard)
    * [Grid](#grid)
    * [Vcpkg Integration](#vcpkg-integration)
  * [v.10.9.0](#v1090)
    * [Custom template namer](#custom-template-namer)
    * [Options.withNamer()](#optionswithnamer)
    * [Path](#path)
  * [v.10.8.0](#v1080)
    * [Ninja builds work when inside source tree](#ninja-builds-work-when-inside-source-tree)
  * [v.10.7.0](#v1070)
    * [CombinationApprovals header](#combinationapprovals-header)
  * [v.10.6.0](#v1060)
    * [FrameworkIntegrations class](#frameworkintegrations-class)
    * [Approvals::verify() counts as an assertion in test frameworks](#approvalsverify-counts-as-an-assertion-in-test-frameworks)
  * [v.10.5.0](#v1050)
    * [Support for selecting Reporter at run-time](#support-for-selecting-reporter-at-run-time)
  * [v.10.4.0](#v1040)
    * [Support for CppUTest framework](#support-for-cpputest-framework)
  * [v.10.3.0](#v1030)
    * [Approvals::verifyAll and std::initializer_list](#approvalsverifyall-and-stdinitializer_list)
  * [v.10.2.0](#v1020)
    * [DateUtils](#dateutils)
  * [v.10.1.1](#v1011)
    * [Improved Compilation Speeds](#improved-compilation-speeds)
  * [v.10.0.0](#v1000)
    * [Removed Deprecated Code](#removed-deprecated-code)
  * [v.8.9.0](#v890)
    * [Regex-based Scrubbing](#regex-based-scrubbing)
  * [v.8.8.0](#v880)
    * [FmtApprovals](#fmtapprovals)
  * [v.8.7.0](#v870)
    * [Options](#options)
    * [Scrubbers](#scrubbers)
    * [StringMaker and TApprovals](#stringmaker-and-tapprovals)
    * [Consistent macro names](#consistent-macro-names)
  * [v.8.6.0](#v860)
    * [Support for Boost.Test framework](#support-for-boosttest-framework)
  * [v.8.5.0](#v850)
    * [Support for Sublime Merge](#support-for-sublime-merge)
    * [Support for Beyond Compare on Linux](#support-for-beyond-compare-on-linux)
  * [v.8.3.0](#v830)
    * [Flexibility for adding custom merge tools](#flexibility-for-adding-custom-merge-tools)
    * [Supporting new merge tools.](#supporting-new-merge-tools)
  * [v.8.2.0](#v820)
    * [Conan Integration documented](#conan-integration-documented)
  * [v.8.1.0](#v810)
    * [Version detection](#version-detection)
  * [v.8.0.0](#v800)
    * [CMake Integration documented](#cmake-integration-documented)
    * [Use with Ninja generator documented](#use-with-ninja-generator-documented)
  * [v.7.0.0](#v700)
    * [Support for \[Boost\].UT test framework](#support-for-boostut-test-framework)
  * [v.6.0.0](#v600)
    * [Existing Catch Project - with your main()](#existing-catch-project---with-your-main)
  * [v.5.1.0](#v510)
    * [Continuous Integration Builds](#continuous-integration-builds)
    * [Approving multiple files in one test](#approving-multiple-files-in-one-test)
    * [ExceptionCollector](#exceptioncollector)
    * [Using custom writers](#using-custom-writers)
    * [Using custom filename extensions](#using-custom-filename-extensions)
  * [v.5.0.0](#v500)
    * [Multiple output files per test](#multiple-output-files-per-test)
    * [SeparateApprovedAndReceivedDirectoriesNamer](#separateapprovedandreceiveddirectoriesnamer)
    * [Registering a Custom Namer](#registering-a-custom-namer)
  * [Before v.5.0.0](#before-v500)
    * [Customizing Google Tests Approval File Names](#customizing-google-tests-approval-file-names)
    * [Blocking Reporter](#blocking-reporter)
    * [Machine Blockers](#machine-blockers)
    * [Front Loaded Reporters](#front-loaded-reporters)
    * [Using sub-directories for approved files](#using-sub-directories-for-approved-files)<!-- endToc -->

## v.x.y.z

## v.10.13.0

### Catch2 v3 support

[Catch2v3](/doc/UsingCatch2v3.md#top) is now supported additionally to Catch2v2.

## v.10.12.0

### EmptyFileCreatorByType::registerCreator

[Empty file](/doc/Writers.md#empty-files) creation is now customizable for individual file extensions.

## v.10.11.0

### useFileNameSanitizer

You can now customize how invalid filename characters are converted. See [Converting Test Names to Valid FileNames](/doc/Namers.md#converting-test-names-to-valid-filenames)

### useEmptyFileCreator

[Empty file](/doc/Writers.md#empty-files) creation is now customizable, for when you are verifying non-text files.

## v.10.10.0

### Storyboard

[Storyboard](/doc/reference/Storyboard.md#top) is a utility that allows you to print the changes to an object over time

### Grid

[Grid](/doc/reference/Grid.md#top)  is a utility that creates 2D text in a grid format

### Vcpkg Integration

See [Vcpkg Integration](/doc/VcpkgIntegration.md#top).

## v.10.9.0

### Custom template namer

See [TemplatedCustomNamer](/doc/Namers.md#templatedcustomnamer)

### Options.withNamer()

[Options](/doc/Options.md#top) now has the ability to specify a custom namer.

### Path

See [Path.h](/ApprovalTests/utilities/Path.h) and [Path.cpp](/ApprovalTests/utilities/Path.cpp)

## v.10.8.0

### Ninja builds work when inside source tree

The entire [Misconfigured Builds](/doc/TroubleshootingMisconfiguredBuild.md#top) page of workarounds is no needed, but is retained for those using older releases.

## v.10.7.0

### CombinationApprovals header

Optional header argument added to [CombinationApprovals](/doc/TestingCombinations.md#top).

## v.10.6.0

### FrameworkIntegrations class

We now have a centralised portal, `FrameworkIntegrations`, to all the places that you need to use, in order
to [add support for a new test framework](/doc/SupportingNewTestFramework.md#top).

### Approvals::verify() counts as an assertion in test frameworks

Previously, Approvals wouldn't register as an assertion, giving misleading messages and reporting, and sometimes causing
a test framework to complain that there were no assertions.

## v.10.5.0

### Support for selecting Reporter at run-time

See [How to Select a Reporter with an Environment Variable](/doc/how_tos/SelectReporterWithEnvironmentVariable.md#top).

## v.10.4.0

### Support for CppUTest framework

See [Using Approval Tests With CppUTest](/doc/UsingCppUTest.md#top).

## v.10.3.0

### Approvals::verifyAll and std::initializer_list

Added `std::initializer_list` support to `Approvals::verifyAll()`.

For example:

<!-- snippet: initializer_list -->
<a id='snippet-initializer_list'></a>
```cpp
ApprovalTests::Approvals::verifyAll({10, 20, 30});
```
<sup><a href='/tests/DocTest_Tests/VectorTests.cpp#L57-L59' title='Snippet source file'>snippet source</a> | <a href='#snippet-initializer_list' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## v.10.2.0

### DateUtils

See [DateUtils](/doc/Utilities.md#dateutils)

## v.10.1.1

### Improved Compilation Speeds

![Compilation Times: v.10.1.0: 2.7 secs vs v.10.1.1: 1.2 secs](/doc/images/ApprovalTests_v.10.1.1_compilation_times.png?raw=true)

## v.10.0.0

### Removed Deprecated Code

See [Why We Are Converting To Options](/doc/explanations/WhyWeAreConvertingToOptions.md#top) for easy ways to update your code.

Specifically, the following have been removed:

* Methods
    * `Approvals::verify(..., Reporter)`
    * `Approvals::verifyAll(..., Reporter)`
    * `Approvals::verifyExistingFile(..., Reporter)`
    * `Approvals::verifyExceptionMessage(..., Reporter)`
    * `Approvals::verifyWithExtension(...)`
    * `CombinationApprovals::verifyAllCombinations(Reporter, ...)`
* Macros
    * `APPROVAL_TESTS_HIDE_DEPRECATED_CODE`
    * `APPROVALTESTS_VERSION`
    * `APPROVALTESTS_VERSION_MAJOR`
    * `APPROVALTESTS_VERSION_MINOR`
    * `APPROVALTESTS_VERSION_PATCH`
    * `APPROVALTESTS_VERSION_STR`
    * `APPROVALS_CATCH_DISABLE_FILE_MACRO_CHECK`

## v.8.9.0

### Regex-based Scrubbing 

See [Scrubbing using Regular Expressions (regex)](/doc/how_tos/ScrubNonDeterministicOutput.md#regular-expressions-regex).

## v.8.8.0

### FmtApprovals

See [How to Use the Fmt Library To Print Objects](/doc/how_tos/UseTheFmtLibraryToPrintObjects.md#top).

## v.8.7.0

### Options

See [Options](/doc/Options.md#top).

### Scrubbers

See [How to Scrub Non-Deterministic Output](/doc/how_tos/ScrubNonDeterministicOutput.md#top).

### StringMaker and TApprovals

This is in internal change, which will provide future flexibility, and does not change any existing code.

In this release, we:

* templatized the Approvals class, renaming it to TApprovals
* changed the CombinationApprovals namespace to a template class called TCombinationApprovals
* introduced the StringMaker class as an additional customization point for the above two classes 

To learn about the extra string-formatting options for your objects, see [To String](/doc/ToString.md#top). 

### Consistent macro names

All our Macros now start with `APPROVAL_TESTS_`.

We have kept the old macros, redirecting to the new ones, for backwards compatibility.

| Old                                        | New                                       |
| ------------------------------------------ | ----------------------------------------- |
| `APPROVALTESTS_VERSION`                    | `APPROVAL_TESTS_VERSION`                  |
| `APPROVALTESTS_VERSION_MAJOR`              | `APPROVAL_TESTS_VERSION_MAJOR`            |
| `APPROVALTESTS_VERSION_MINOR`              | `APPROVAL_TESTS_VERSION_MINOR`            |
| `APPROVALTESTS_VERSION_PATCH`              | `APPROVAL_TESTS_VERSION_PATCH`            |
| `APPROVALTESTS_VERSION_STR`                | `APPROVAL_TESTS_VERSION_STR`              |
| `APPROVALS_CATCH_DISABLE_FILE_MACRO_CHECK` | `APPROVAL_TESTS_DISABLE_FILE_MACRO_CHECK` |

## v.8.6.0

### Support for Boost.Test framework

See [Using Approval Tests With Boost.Test](/doc/UsingBoostTest.md#top)

## v.8.5.0

### Support for Sublime Merge

Added support for [Sublime Merge](https://www.sublimemerge.com/) on Linux, macOS, and Windows (See [#103](https://github.com/approvals/ApprovalTests.cpp/pull/103#issue-377938792))

### Support for Beyond Compare on Linux

Added support for [Beyond Compare](https://www.scootersoftware.com) on Linux (See [#114](https://github.com/approvals/ApprovalTests.cpp/issues/114)).

## v.8.3.0

### Flexibility for adding custom merge tools

`CustomReporter::create()` adds flexibility for adding custom merge tools: see [How to Use A Custom Reporter](/doc/how_tos/UseACustomReporter.md#top).

### Supporting new merge tools.

See [How to Submit a New Reporter to ApprovalTests](/doc/how_tos/SubmitANewReporterToApprovalTests.md#top).

## v.8.2.0

### Conan Integration documented

See [Conan Integration](/doc/ConanIntegration.md#top).

## v.8.1.0

### Version detection

ApprovalTests provides the following macros to detect the release version, with a set of example values shown in italics:

* `APPROVAL_TESTS_VERSION_MAJOR`: *8*
* `APPROVAL_TESTS_VERSION_MINOR`: *1*
* `APPROVAL_TESTS_VERSION_PATCH`: *2*
* `APPROVAL_TESTS_VERSION_STR`: *8.1.2*
* `APPROVAL_TESTS_VERSION`: *80102*

## v.8.0.0

### CMake Integration documented

See [CMake Integration](/doc/CMakeIntegration.md#top).

### Use with Ninja generator documented

See [Troubleshooting Misconfigured Build](/doc/TroubleshootingMisconfiguredBuild.md#top), for explanations, fixes and workarounds.

## v.7.0.0

See the [v.7.0.0 milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/2?closed=1) for the full list of changes.

### Support for \[Boost\].UT test framework

See [Using Approval Tests With \[Boost\].UT](/doc/UsingUT.md#top).

## v.6.0.0

### Existing Catch Project - with your main()

See [Existing Project - with your main()](/doc/UsingCatch.md#existing-project---with-your-main).

## v.5.1.0

### Continuous Integration Builds

Approval tests will now [never launch any reporters on supported Continuous Integration machines](/doc/BuildMachinesAndCI.md#top).

### Approving multiple files in one test

See [Approving multiple files in one test](/doc/MultipleOutputFilesPerTest.md#approving-multiple-files-in-one-test)

### ExceptionCollector

See [ExceptionCollector](/doc/Utilities.md#exceptioncollector)

### Using custom writers

See [Using custom writers](/doc/Writers.md#using-custom-writers)

### Using custom filename extensions

See [Using custom filename extensions](/doc/Writers.md#using-custom-filename-extensions)

## v.5.0.0

### Multiple output files per test

See [Multiple output files per test](/doc/MultipleOutputFilesPerTest.md#top).

### SeparateApprovedAndReceivedDirectoriesNamer

See [SeparateApprovedAndReceivedDirectoriesNamer](/doc/Namers.md#separateapprovedandreceiveddirectoriesnamer)

### Registering a Custom Namer

See [Registering a Custom Namer](/doc/Namers.md#registering-a-custom-namer)

## Before v.5.0.0

### Customizing Google Tests Approval File Names

See [Using Approval Tests With Google Tests](/doc/UsingGoogleTests.md#customizing-google-tests-approval-file-names)

### Blocking Reporter

See [Blocking Reporters](/doc/Reporters.md#blocking-reporters)

### Machine Blockers

Sometimes you will want tests to only run on certain machines. Machine blockers are a great way to do this.

<!-- snippet: machine_specific_test_runner -->
<a id='snippet-machine_specific_test_runner'></a>
```cpp
TEST_CASE("Only run this test on John's machine")
{
    auto blocker = ApprovalTests::MachineBlocker::onMachinesNotNamed("JOHNS_MACHINE");
    if (blocker.isBlockingOnThisMachine())
    {
        return;
    }
    // Write tests here that depend on John's environment.
    REQUIRE(ApprovalTests::SystemUtils::getMachineName() == "JOHNS_MACHINE");
}
```
<sup><a href='/tests/DocTest_Tests/utilities/MachineBlockerTests.cpp#L20-L31' title='Snippet source file'>snippet source</a> | <a href='#snippet-machine_specific_test_runner' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

### Front Loaded Reporters

See [Front Loaded Reporters](/doc/Reporters.md#front-loaded-reporters)

### Using sub-directories for approved files

See [Using sub-directories for approved files](/doc/Configuration.md#using-sub-directories-for-approved-files)

---

[Back to User Guide](/doc/README.md#top)
