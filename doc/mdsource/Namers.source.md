<a id="top"></a>

# Namers

toc

## The Purpose of Namers

`Approvals::verify(text);`

could be written as:

`REQUIRE(text == (loadContentsFromFile("FileName.TestName.approved.txt"));`

Part of Approval Tests' "Convention over Configuration" is to remove this by automatically creating meaningful file names, and therefore it could be written as:

`REQUIRE(text == (loadContentsFromFile(namer.getApprovedFile()));`

"If you **always** have to do something, you should **never** have to do something."

Since all of your `REQUIRE`s would look like this, we can simplify it with the above `Approvals::verify(text);` - and this is enabled by the ApprovalNamers.

## The Parts of Namers

The conventional layout for files saved with `Approvals::verify()` and related functions is:

* `path_to_test_file/FileName.TestName.approved.txt`
* `path_to_test_file/FileName.TestName.received.txt`

The Approval Namer is responsible for creating these two names.

The interface for this is [`ApprovalNamer`](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/namers/ApprovalNamer.h).


## Registering a Custom Namer

If you ever want to create a custom namer, Approval Tests has a mechanism to change which namer it uses by default. Please note that you need to create a function that creates new namers.


snippet: register_default_namer

## Alternative Namers

### SeparateApprovedAndReceivedDirectoriesNamer

The pattern used by this class for file names is:
- `./approved/[test file name].[test name].[extension]`
- `./received/[test file name].[test name].[extension]`

This layout enables Beyond Compare 4 (or any other directory comparison tool) to compare the `approved/` and `received/` directories, and approve one or more files by copying them (without renaming) from `received/` to `approved/`.

The `approved/` and `received/` directories are created automatically.

To register this as your default namer, use:

snippet: register_separate_directories_namer

## Approving multiple files from one test 

ApprovalTests uses the name of the current test to determine the names of output files that it writes. This means that **by default, there is only one approval file per test case**.

However, sometimes it is useful to be able to verify multiple files in one test case, or have a file per OS or other environment configuration.

### Scenarios

Here are some examples of files you might want.

&nbsp;

**Multiple data inputs:**

In this scenario, your test creates 3 files, all of which are being checked when you run the test.

```
TestProteinGeneration.createImage.protein1.approved.png
TestProteinGeneration.createImage.protein2.approved.png
TestProteinGeneration.createImage.protein3.approved.png
```

&nbsp;

**Multiple outputs:**

In this scenario, the code under test creates three different types of files, all of which are being checked.

```
TestProtein.processInput.logOutput.approved.txt
TestProtein.processInput.calculationResults.approved.txt
TestProtein.processInput.renderedResult.approved.png
```

&nbsp;

**Multiple environments:**

In this scenario, your test only creates one file, and which one it is checked against is dependent on which OS the test is running on.

```
TestQtDialog.loginScreen.onMacOSX.approved.png
TestQtDialog.loginScreen.onWindows.approved.png
TestQtDialog.loginScreen.onLinux.approved.png
```

&nbsp;

Here are a few ways to do that.

### Catch2

You can have a file-per-subsection.

You can either do these dynamically, e.g. in a for-loop:

snippet: catch2_multiple_output_files_dynamic

Or hard-coded, with multiple sections:

snippet: catch2_multiple_output_files_hard_coded

### doctest

Note: unlike Catch, doctest sub-cases must have static strings for names, so if you want to name things dynamically, you will have to use the native Approval Tests mechanism - see below.

You can have hard-coded, with multiple sections:

snippet: doctest_multiple_output_files_hard_coded

### Approval Tests

This can be done with Catch2's `SECTION` and doctest's `SUBCASE`. However, there is no supported way to do this with Google Tests, and it may be desirable to use an approach that Approval Tests can use with all test frameworks it supports.

The function `addAdditionalApprovalTestInformation()` adds an extra piece of text to be added to the filename used for output files.

Example of use:

---

[Back to User Guide](/doc/README.md#top)
