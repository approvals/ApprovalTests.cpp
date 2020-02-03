<a id="top"></a>

# Features



toc

## v.x.y.z

### Conan Integration documented

See [Conan Integration](/doc/ConanIntegration.md#top).

## v.8.1.0

### Version detection

ApprovalTests provides the following macros to detect the release version, with a set of example values shown in italics:

* `APPROVALTESTS_VERSION_MAJOR`: *8*
* `APPROVALTESTS_VERSION_MINOR`: *1*
* `APPROVALTESTS_VERSION_PATCH`: *2*
* `APPROVALTESTS_VERSION_STR`: *8.1.2*
* `APPROVALTESTS_VERSION`: *80102*

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

snippet: machine_specific_test_runner

### Front Loaded Reporters

See [Front Loaded Reporters](/doc/Reporters.md#front-loaded-reporters)

### Using sub-directories for approved files

See [Using sub-directories for approved files](/doc/Configuration.md#using-sub-directories-for-approved-files)


---

[Back to User Guide](/doc/README.md#top)
