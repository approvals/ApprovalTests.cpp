<a id="top"></a>

# Test cases

<!-- toc -->
## Contents

  * [anchor called top is removed](#anchor-called-top-is-removed)
  * [other anchors are retained](#other-anchors-are-retained)
  * [anchor with unusal characters in is updated correctly](#anchor-with-unusal-characters-in-is-updated-correctly)
  * [link to markdown file outside doc/ is unchanged](#link-to-markdown-file-outside-doc-is-unchanged)
    * [links to docs in various relative paths are correct](#links-to-docs-in-various-relative-paths-are-correct)
  * [Multiple links on one line](#multiple-links-on-one-line)
    * [Links to directories](#links-to-directories)
  * [Links to source files](#links-to-source-files)
  * [Links to .include.md files](#links-to-includemd-files)
  * [Links to images](#links-to-images)
  * [Link to README.md should go to GitHub](#link-to-readmemd-should-go-to-github)
  * [Non-HTML links - should be unchanged](#non-html-links---should-be-unchanged)
  * [Do not change specific links that are in code blocks](#do-not-change-specific-links-that-are-in-code-blocks)
  * [Test code snippet - linking to lines in a file](#test-code-snippet---linking-to-lines-in-a-file)
  * [Test code snippet - linking to a whole file](#test-code-snippet---linking-to-a-whole-file)
  * [Test changes made to satisfy Pygments](#test-changes-made-to-satisfy-pygments)
    * [Convert h to cpp](#convert-h-to-cpp)
    * [Remove txt](#remove-txt)
  * [A wide table](#a-wide-table)
  * [A table with wide words](#a-table-with-wide-words)
  * [Included file](#included-file)
  * [Snippet pulled in from external CMake file](#snippet-pulled-in-from-external-cmake-file)
  * [Hyperlink and URL](#hyperlink-and-url)
    * [Does not render correctly on Read the Docs](#does-not-render-correctly-on-read-the-docs)
    * [Does render correctly on Read the Docs](#does-render-correctly-on-read-the-docs)<!-- endToc -->

## anchor called top is removed

["Target 1"](/doc/DisposableObjects.md#top)

## other anchors are retained

[requirements for using Approval Tests With \[Boost\].UT](/doc/UsingUT.md#requirements).

## anchor with unusal characters in is updated correctly

[TCR](/doc/Glossary.md#test--commit--revert-tcr).

[Existing Project - with your main()](/doc/UsingCatch.md#existing-project---with-your-main).

## link to markdown file outside doc/ is unchanged

[How To Release](/build/HowToRelease.md#top)

### links to docs in various relative paths are correct

See [Target 1](/doc/subdir1/Doc1.md#target1).

See [Target 1](/doc/subdir/Doc1.md#target1).

See [Target 1](/doc/Doc1.md#target1).

## Multiple links on one line

See [Target 1](/doc/Doc1.md#target1) join1 [Target 2](/doc/Doc2.md#target3) join2 [Target 3](/doc/Doc3.md#target3).

### Links to directories

[the build directory](/build/)

[doc](/doc/).

[/ApprovalTests/integrations/](/ApprovalTests/integrations/)

## Links to source files

[tests/GoogleTest_Tests/main.cpp](/tests/GoogleTest_Tests/main.cpp)

## Links to .include.md files

[include_using_test_frameworks_list.include.md](/doc/include_using_test_frameworks_list.include.md#top)

## Links to images

Tutorial ![Intro Graphic](/doc/images/ApprovalTests.cpp.IntroGraphic.gif?raw=true)

Tutorial ![New Failure](/doc/images/tutorial/01_new_failure.png?raw=true)

## Link to README.md should go to GitHub

Link to README.md should go to GitHub, because README.md is not intended to be displayed on Read the Docs.

Each new documentation page needs to be added to [doc/README.md](/doc/README.md#top).

## Non-HTML links - should be unchanged

[Llewellyn](mailto:llewellyn.falco@gmail.com)

## Do not change specific links that are in code blocks

```md
* [this link will work everywhere](/doc/Reporters.md#top)
```

Not this:

```md
* [this link is wrong](doc/Reporters.md#top)
```

And not this:

```md
* [this link is wrong](Reporters.md#top)
```

# Links whose hyperlinked text is in fixed-width font

From Namers.md:

The interface for this is [`ApprovalNamer`](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/core/ApprovalNamer.h).

From CMakeIntegration.md:

[`ExternalProject` module](https://cmake.org/cmake/help/latest/module/ExternalProject.html)

[`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html).

From UsingUT.md

[`std::source_location`](https://en.cppreference.com/w/cpp/utility/source_location)

From Setup.md

[`tests/NewTest.cpp`](https://github.com/approvals/ApprovalTests.cpp.StarterProject/blob/master/tests/NewTest.cpp)

Multiple on one line

[`ExternalProject` module](https://cmake.org/cmake/help/latest/module/ExternalProject.html) and `this should still be fixed width` and [`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html).

## Test code snippet - linking to lines in a file

<!-- snippet: verify_exception_message_example -->
<a id='snippet-verify_exception_message_example'></a>
```cpp
ApprovalTests::Approvals::verifyExceptionMessage([]() { /* your code goes here */ });
```
<sup><a href='/tests/DocTest_Tests/ApprovalsExamples.cpp#L6-L8' title='Snippet source file'>snippet source</a> | <a href='#snippet-verify_exception_message_example' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Test code snippet - linking to a whole file

<!-- snippet: VectorTests.VerifyAllStartingPoint.approved.txt -->
<a id='snippet-VectorTests.VerifyAllStartingPoint.approved.txt'></a>
```txt
TITLE


input.value1 => placeholder
input.value2 => placeholder
```
<sup><a href='/tests/DocTest_Tests/approval_tests/VectorTests.VerifyAllStartingPoint.approved.txt#L1-L6' title='Snippet source file'>snippet source</a> | <a href='#snippet-VectorTests.VerifyAllStartingPoint.approved.txt' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Test changes made to satisfy Pygments

### Convert h to cpp

```h
class Wibble
{
};
```

### Remove txt

```txt
I am some text
```

## A wide table

| Framework    |  Min C++  | Ease of setup      | IDE Support           | Build time  |
| ------------ | :-------: | ------------------ | --------------------- | ----------- |
| Catch2       |   C++11   | Very easy [1], [2] | Widely supported      | Not bad [3] |
| doctest      |   C++11   | Very easy [1]      | Unknown               | Fast        |
| Google Test  |   C++11   | Difficult          | Very widely supported | Fast        |
| Boost.Test   |   C++11   | Difficult          | Unknown               | Fast        |
| \[Boost\].UT | C++20 [4] | Very easy [1]      | Unknown               | Fast        |

1. Released as a single header file
2. See the [Starter Project](https://github.com/approvals/ApprovalTests.Cpp.StarterProject)
3. Catch2 has [options to speed up its builds](https://github.com/catchorg/Catch2/blob/master/docs/slow-compiles.md#top)
4. \[Boost\].UT works with C++17, but the ApprovalTests interface to that library depends on [std::source_location](https://en.cppreference.com/w/cpp/utility/source_location), which is a C++ 20 feature. 

## A table with wide words

Some of these words end up with spaces in, wrongly.

| Old                                        | New                                       |
| ------------------------------------------ | ----------------------------------------- |
| `APPROVALTESTS_VERSION`                    | `APPROVAL_TESTS_VERSION`                  |
| `APPROVALTESTS_VERSION_MAJOR`              | `APPROVAL_TESTS_VERSION_MAJOR`            |
| `APPROVALTESTS_VERSION_MINOR`              | `APPROVAL_TESTS_VERSION_MINOR`            |
| `APPROVALTESTS_VERSION_PATCH`              | `APPROVAL_TESTS_VERSION_PATCH`            |
| `APPROVALTESTS_VERSION_STR`                | `APPROVAL_TESTS_VERSION_STR`              |
| `APPROVALS_CATCH_DISABLE_FILE_MACRO_CHECK` | `APPROVAL_TESTS_DISABLE_FILE_MACRO_CHECK` |

## Included file

* [Using Approval Tests With Catch](/doc/UsingCatch.md#top)<!-- include: include_using_test_frameworks_list.include.md -->
* [Using Approval Tests With CppUTest](/doc/UsingCppUTest.md#top)
* [Using Approval Tests With Google Tests](/doc/UsingGoogleTests.md#top)
* [Using Approval Tests With Doctest](/doc/UsingDoctest.md#top)
* [Using Approval Tests With Boost.Test](/doc/UsingBoostTest.md#top)
* [Using Approval Tests With \[Boost\].UT](/doc/UsingUT.md#top)<!-- endInclude -->

## Snippet pulled in from external CMake file

Sample take from CMakeIntegration.md:

We use this `dependencies/CMakeLists.txt` file:

<!-- include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/fetch_content_approvaltests_catch2/mdsource/inc_fetch_content_approvaltests_catch2_dependencies_cmakelists.include.md -->

```cmake
# Needs CMake 3.14 or above
include(FetchContent)

# -------------------------------------------------------------------
# ApprovalTests.cpp
FetchContent_Declare(ApprovalTests
        GIT_REPOSITORY https://github.com/approvals/ApprovalTests.cpp.git
        GIT_TAG master)

FetchContent_MakeAvailable(ApprovalTests)

# -------------------------------------------------------------------
# Catch2
FetchContent_Declare(Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.11.1)

FetchContent_MakeAvailable(Catch2)
```
<sup><a href='https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/main/./fetch_content_approvaltests_catch2/dependencies/CMakeLists.txt' title='File snippet was copied from'>snippet source</a></sup>
<!-- endInclude -->

## Hyperlink and URL

### Does not render correctly on Read the Docs

Where a run of formatted text (here, italic) contains a hyperlink. I have not been able to get it to display correctly in Read the Docs.

Example Markdown input, where the whole line is italic:

*If you would like us to add any more questions here, please contact us via [the Contributing page](/doc/Contributing.md#top).*

On the production site, it displays like this (after our conversion process here):

```
If you would like us to add any more questions here, please contact us via `the Contributing page <Contributing.html>`__.
```

*If you would like us to add any more questions here, please contact us via [the Contributing page](/doc/Contributing.md#top).*

### Does render correctly on Read the Docs

The fix is to end the italic formatting before the hyperlink. It looks a bit worse on GitHub but a lot better in Read the Docs:

*If you would like us to add any more questions here, please contact us via* [the Contributing page](/doc/Contributing.md#top).

---

[Back to User Guide](/doc/README.md#top)
