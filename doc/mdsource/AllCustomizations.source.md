<a id="top"></a>

# All Customizations of Approval Tests

toc

## Introduction

This page provides a starting point to see all the ways of controlling the behaviour of Approval Tests.

## Disposable Objects

See [Disposable Objects](/doc/DisposableObjects.md#top) for a general overview of how most customisation of Approval Tests works.

## Namers - how Approved Files are named

### Output Directories

See [Using sub-directories for approved files](/doc/Configuration.md#using-sub-directories-for-approved-files) for putting Approval files in a sub-directory, to keep your tests directory tidy.

See [SeparateApprovedAndReceivedDirectoriesNamer](/doc/Namers.md#separateapprovedandreceiveddirectoriesnamer) to put the Approved and Received files in adjacent directories, in order to allow a folder-diffing tool to compare the two directories. 

### Output File Names

See [Namers](/doc/Namers.md#top) for controlling how Approval files are named. 

See [Multiple output files per test](/doc/MultipleOutputFilesPerTest.md#top)
for multiple ways to control file names when verifying more than one output file in a test.

See [Using Approval Tests With Google Tests](/doc/UsingGoogleTests.md#top) for how to control the names of Approval files if using that framework. 

### Filename Extensions

See [Writers](/doc/Writers.md#top) for how to control the file extension used to save Approval files.

## Writers - how things being verified are written to file

See [Writers](/doc/Writers.md#top) for how to customize the serialization of objects.

## Comparators - how files are compared

See [Custom Comparators](/doc/CustomComparators.md#top) for controlling how Approval Tests determines if the [Received File](/doc/Glossary.md#received-file) and [Approved File](/doc/Glossary.md#approved-file) are equivalent.

## Reporters - how test failures are shown

See [Reporters](/doc/Reporters.md#top) to control how test failures are shown. This is typically done by showing a diff tool.

---

[Back to User Guide](/doc/README.md#top)
