<a id="top"></a>

# CMake Integration

toc

## Introduction

Because we use CMake to build Catch2, we also provide integration points for our users.

## CMake target

Approval Tests' CMake build exports an interface target `ApprovalTests::ApprovalTests`. Linking
against it will add the proper include path and all necessary capabilities
to the resulting binary.

This target is provided when ApprovalTests.cpp is used as a subdirectory.
Assuming that ApprovalTests.cpp has been cloned to `lib/ApprovalTests.cpp`:

```cmake
add_subdirectory(lib/ApprovalTests.cpp)
target_link_libraries(tests ApprovalTests::ApprovalTests)
```

## CMake project options

ApprovalTests.cpp's CMake project also provides some options for other projects
that consume it. These are:

* `APPROVAL_TESTS_ENABLE_CODE_COVERAGE` -- When `ON`, Approval Test's own tests are run with code coverage enabled. This uses [Lars Bilke's CodeCoverage.cmake](https://github.com/bilke/cmake-modules/blob/master/CodeCoverage.cmake).  Defaults to `OFF`.

Options that only affect the main project, and have no effect if `add_subdirectory()` or similar is used:

* `APPROVAL_TESTS_BUILD_CMAKE_INTEGRATION_TESTING` -- When `ON`, the tests in [tests/CMake_Tests](https://github.com/approvals/ApprovalTests.cpp/blob/master/tests/CMake_Tests) are run. Their job is to check that our CMake integrations still work. Note that these tests always run if this is the top-level project. Otherwise, they are only run if this is on and `APPROVAL_TESTS_BUILD_TESTING` is also on. Defaults to `OFF`.

Currently, these are all the supported options:

snippet: ApprovalTestsOptions.cmake

## Scenarios when using ApprovalTests.cpp 

### Context

**Example Project**

Suppose you are writing some tests that use ApprovalTests.cpp with the Catch2 test framework.

Your top-level `CMakeLists.txt` file might look something like this:

include: inc_fetch_content_approvaltests_cmakelists

Here is [this example project](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/master/fetch_content_approvaltests).

**Example Tests**

Your `tests/CMakeLists.txt` file might look something like this:

include: inc_fetch_content_approvaltests_tests_cmakelists

This says that the libraries `ApprovalTests::ApprovalTests` and `Catch2::Catch2` are required.

Here is [this example project's test directory](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/master/fetch_content_approvaltests/tests).

**Dependencies**

How might you enable CMake to provide those libraries? In other words, what are the options for the contents of `dependencies/CMakeLists.txt`?

The next few sections describe some options.

### Make CMake clone ApprovalTests.cpp

**Note:** The files in this section can be viewed and downloaded from [fetch_content_approvaltests](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/master/fetch_content_approvaltests).

The following is for when you just want ApprovalTests.cpp to be downloaded as part of your project's build. You don't particularly want to see its source code, although you're happy if your debugger steps in to its source code.

It also needs CMake 3.14 or above.

The important thing to note is the `add_subdirectory(dependencies)` line.

It will use the file: `dependencies/CMakeLists.txt`:

include: inc_fetch_content_approvaltests_dependencies_cmakelists

There are also options to enable use of ApprovalTests.cpp's copies of all other supported test frameworks except GoogleTest, including:

* `APPROVAL_TESTS_BUILD_THIRD_PARTY_DOCTEST`
* `APPROVAL_TESTS_BUILD_THIRD_PARTY_UT`

Note the `GIT_TAG` value: CMake needs to know which revision to use.

Note also that here we are using the copy of Catch2 that is included in the ApprovalTests.cpp repository.

### Make CMake clone ApprovalTests.cpp and Catch2

**Note:** The files in this section can be viewed and downloaded from [fetch_content_approvaltests_catch2](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/master/fetch_content_approvaltests_catch2).

The only difference between the previous example and this one is that we get CMake to also download and use the Catch2 repository. 

We use this file: `dependencies/CMakeLists.txt`:

include: inc_fetch_content_approvaltests_catch2_dependencies_cmakelists

### Use own ApprovalTests.cpp and Catch2 clones

**Note:** The files in this section can be viewed and downloaded from [add_subdirectory_approvaltests_catch2](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/master/add_subdirectory_approvaltests_catch2).

Here, instead of getting CMake to download ApprovalTests.cpp and Catch2, we have got our own clones or forks of them, which we want to use with our own tests.

This works with older versions of CMake, unlike the `FetchContent` examples above. The following `dependencies/CMakeLists.txt` file was tested with CMake 3.8.

include: inc_add_subdirectory_approvaltests_catch2_dependencies_cmakelists

### Using other supported test frameworks

To save space and repetition, the examples above only show the Catch2 framework.

The same principles apply when using all the other test frameworks supported by ApprovalTests.cpp.

## Scenarios when developing ApprovalTests.cpp 

### Developing ApprovalTests.cpp with test framework sources

**Note:** The files in this section can be viewed and downloaded from [develop_approvaltests](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/master/develop_approvaltests).

It is useful to be able to edit and debug both this project and the test frameworks that it depends upon. It helps to be able to see the source code of these frameworks, rather than just the single-header releases that are copied in to the third_party directory here.

This also allows us to checkout different commits of any of these projects.

Here we want to enable and run all the ApprovalTests.cpp tests, unlike the cases above, where we only want to run the tests of the project that is being developed by using this library.

Imagine this directory structure, where the repositories for all these projects are checked out side-by-side, and there is an extra directory `develop_approvaltests/`:

```
ApprovalTests.cpp/
  .git/
Catch2/
  .git/
doctest/
  .git/
googletest/
  .git/
ut/
  .git/
develop_approvaltests/
  CMakeLists.txt
```

The file `develop_approvaltests/CMakeLists.txt` creates a "super build": one project for developing ApprovalTests.cpp and all the projects it depends on:

include: inc_develop_approvaltests_cmakelists

---

[Back to User Guide](/doc/README.md#top)
