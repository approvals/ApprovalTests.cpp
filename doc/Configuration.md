<a id="top"></a>

# Configuring Approval Tests

<!-- toc -->
## Contents

  * [Using sub-directories for approved files](#using-sub-directories-for-approved-files)<!-- endToc -->

## Using sub-directories for approved files

If you have a lot of approval files, you might want to put them in a subdirectory, to prevent them cluttering up your source files. You can do this at a global or per-test level, by adding the line:

<!-- snippet: use_subdirectory_in_main -->
<a id='snippet-use_subdirectory_in_main'></a>
```cpp
auto directoryDisposer =
    ApprovalTests::Approvals::useApprovalsSubdirectory("approval_tests");
```
<sup><a href='/tests/Catch2_Tests/main.cpp#L12-L15' title='Snippet source file'>snippet source</a> | <a href='#snippet-use_subdirectory_in_main' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Note that the sub-directory is created automatically, and that it will be inside the directory containing the source code of the test, not the current working directory of the test process.

The return value will restore the original directory when the object destructs. Because of this, if you do not store the result in a variable, it will immediately undo itself by the end of the line.

This mechanism allows you to select a different sub-directory in individual tests.

---

[Back to User Guide](/doc/README.md#top)
