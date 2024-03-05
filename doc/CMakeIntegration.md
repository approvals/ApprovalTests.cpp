<a id="top"></a>

# CMake Integration

<!-- toc -->
## Contents

  * [Part 1: Reference](#part-1-reference)
    * [Integration Points](#integration-points)
      * [CMake target](#cmake-target)
      * [CMake project options](#cmake-project-options)
        * [Which targets are built](#which-targets-are-built)
        * [Which third_party libraries are made available](#which-third_party-libraries-are-made-available)
        * [Control the behaviour of our builds](#control-the-behaviour-of-our-builds)
      * [CMake commands support](#cmake-commands-support)
    * [Single header or CMake Integration?](#single-header-or-cmake-integration)
      * [CMake Integration Benefits](#cmake-integration-benefits)
  * [Part 2: Optional Explanatory Examples](#part-2-optional-explanatory-examples)
    * [Scenarios when using Approval Tests](#scenarios-when-using-approval-tests)
      * [Context](#context)
      * [Make CMake clone ApprovalTests.cpp and Catch2](#make-cmake-clone-approvaltestscpp-and-catch2)
      * [Make CMake clone ApprovalTests.cpp using CPM](#make-cmake-clone-approvaltestscpp-using-cpm)
      * [Make CMake clone ApprovalTests.cpp](#make-cmake-clone-approvaltestscpp)
      * [Use own ApprovalTests.cpp and Catch2 clones](#use-own-approvaltestscpp-and-catch2-clones)
      * [Using other supported test frameworks](#using-other-supported-test-frameworks)
    * [Scenarios when developing ApprovalTests.cpp](#scenarios-when-developing-approvaltestscpp)
      * [Developing ApprovalTests.cpp with test framework sources](#developing-approvaltestscpp-with-test-framework-sources)<!-- endToc -->

## Part 1: Reference

### Integration Points

Because we use CMake to build ApprovalTests.cpp, we also provide integration points for our users.

#### CMake target

Approval Tests' CMake build exports an interface target `ApprovalTests::ApprovalTests`. Linking
against it will add the proper include path and all necessary capabilities
to the resulting binary.

This target is provided when ApprovalTests.cpp is used as a subdirectory.
Assuming that ApprovalTests.cpp has been cloned to `lib/ApprovalTests.cpp`:

```cmake
add_subdirectory(lib/ApprovalTests.cpp)
target_link_libraries(tests ApprovalTests::ApprovalTests)
```

#### CMake project options

ApprovalTests.cpp's CMake project also provides some options for other projects
that consume it.

The file [CMake/ApprovalTestsOptions.cmake](https://github.com/approvals/ApprovalTests.cpp/blob/master/CMake/ApprovalTestsOptions.cmake) defines these options.

The options provided are:

##### Which targets are built

Note that these are always enabled if this is the top-level project.

* `APPROVAL_TESTS_BUILD_TESTING`
  * When `ON`, the self-tests are run.  Defaults to `OFF`.
* `APPROVAL_TESTS_BUILD_EXAMPLES`
  * When `ON`, the examples are run.  Defaults to `OFF`.
* `APPROVAL_TESTS_BUILD_DOCS`
  * When `ON`, documentation files are generated, if Doxygen, Sphinx and mdsnippets are installed.  Defaults to `OFF`.
  * These are not part of the `ALL` target.

##### Which third_party libraries are made available

Note that these are always included if this is the top-level project.

* `APPROVAL_TESTS_BUILD_THIRD_PARTY_CATCH2`
  * When `ON`, this project's copy of the Catch2v2 test framework is included.  Defaults to `OFF`.
* `APPROVAL_TESTS_BUILD_THIRD_PARTY_DOCTEST`
  * When `ON`, this project's copy of the doctest test framework is included.  Defaults to `OFF`.
* `APPROVAL_TESTS_BUILD_THIRD_PARTY_UT`
  * When `ON`, this project's copy of the Boost.UT test framework is included.  Defaults to `OFF`.

##### Control the behaviour of our builds

* `APPROVAL_TESTS_ENABLE_CODE_COVERAGE`
  * When `ON`, Approval Test's own tests are run with code coverage enabled. This uses [Lars Bilke's CodeCoverage.cmake](https://github.com/bilke/cmake-modules/blob/master/CodeCoverage.cmake).  Defaults to `OFF`.

#### CMake commands support

* `add_subdirectory()`
    * See [Use own ApprovalTests.cpp and Catch2 clones](/doc/CMakeIntegration.md#use-own-approvaltestscpp-and-catch2-clones) below, for an example using [`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html).
    * **Use case:** This is typically for you have your own copy of the Approval Tests project directory that you want to re-use.
* `FetchContent`
    * See [Make CMake clone ApprovalTests.cpp and Catch2](/doc/CMakeIntegration.md#make-cmake-clone-approvaltestscpp-and-catch2)
 below, for an example using the [`FetchContent` module](https://cmake.org/cmake/help/latest/module/FetchContent.html).
    * The examples below use `FetchContent_MakeAvailable()`, which requires CMake 3.14 or above.
    * If you only have CMake 3.11 or above, see [FetchContent (CMake 3.11+)](https://cliutils.gitlab.io/modern-cmake/chapters/projects/fetch.html) for how to use `FetchContent_Populate()`.
    * **Use case:** This is typically for when you want CMake to download a specific version of Approval Tests for you, behind the scenes.
* `ExternalProject`
    * With CMake before 3.11, see the [`ExternalProject` module](https://cmake.org/cmake/help/latest/module/ExternalProject.html). The `FetchContent` examples below should help get started with `ExternalProject`.
    * **Use case:** This is typically for when you want CMake to download a specific version of Approval Tests for you, behind the scenes, and you are using an older version of CMake.
* `find_package()` - not supported
    * There is not yet support for [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html).
* `CPM`
    * See [Make CMake clone ApprovalTests.cpp using CPM](/doc/CMakeIntegration.md#make-cmake-clone-approvaltestscpp-using-cpm)
    * [CPM](https://github.com/cpm-cmake/CPM.cmake) is CMake's missing package manager. It is a small script for setup-free, cross-platform, reproducible dependency management.
    * **Use case:** This is typically for when you want CMake to download a specific version of Approval Tests for you, behind the scenes, and you would like caching, offline builds and version checking.

### Single header or CMake Integration?

There are two main options for incorporating Approval Tests in to your project:

1. Download the single-header file from the [Releases page](https://github.com/approvals/ApprovalTests.cpp/releases) and, typically, add the header to your source code.
2. Obtain a copy of the entire ApprovalTests.cpp repository and incorporate it in to your CMake build scripts.

Options for obtaining the repository typically include:

* cloning it
* forking it
* including it as a sub-repository
* having a build tool, such as CMake, download it for you automatically as part of your builds

#### CMake Integration Benefits

We recommend using the CMake integration route, which has several user benefits over the single header:

* Automatic prevention of most of the scenarios listed in [Troubleshooting Misconfigured Build](/doc/TroubleshootingMisconfiguredBuild.md#top).
* Source-code compatibility with the single header download:
    * For convenience, we provide a wrapper header file [ApprovalTests.hpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/ApprovalTests.hpp), which can be used to access all the features of this library, without having to know which features are provided by which header files.
* Flexibility in how many of the Approval Tests include files you include:
    * There is also the option to include just the headers in [ApprovalTests/](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests) that you use.
    * This may slightly improve build speeds.
* It may occasionally [provide workarounds to bugs](https://github.com/approvals/ApprovalTests.cpp/issues/90).

## Part 2: Optional Explanatory Examples

### Scenarios when using Approval Tests 

#### Context

**Example Project**

Suppose you are writing some tests that use ApprovalTests.cpp with the Catch2 test framework.

Your top-level `CMakeLists.txt` file might look something like this:

<!-- include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/fetch_content_approvaltests/mdsource/inc_fetch_content_approvaltests_cmakelists.include.md -->

```cmake
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
# This version is needed for FetchContent_Declare & FetchContent_MakeAvailable

project(fetch_content_approvaltests)

enable_testing()

add_subdirectory(dependencies)
add_subdirectory(tests)
```
<sup><a href='https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/main/./fetch_content_approvaltests/CMakeLists.txt' title='File snippet was copied from'>snippet source</a></sup>
<!-- endInclude -->

The important thing to note, for following the examples below, is the `add_subdirectory(dependencies)` line. It makes CMake load a file `dependencies/CMakeLists.txt`.

Each example below shows a `dependencies/CMakeLists.txt`, for the corresponding scenario. All other code is identical between the example directories.

Here is [this example project](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/main/fetch_content_approvaltests).

**Example Tests**

Your `tests/CMakeLists.txt` file might look something like this:

<!-- include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/fetch_content_approvaltests/mdsource/inc_fetch_content_approvaltests_tests_cmakelists.include.md -->

```cmake
add_executable(tests
        main.cpp
        tests.cpp
)
target_link_libraries(tests ApprovalTests::ApprovalTests Catch2::Catch2)

target_compile_features(tests PUBLIC cxx_std_11)
set_target_properties(tests PROPERTIES CXX_EXTENSIONS OFF)

add_test(
        NAME tests
        COMMAND tests)
```
<sup><a href='https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/main/./fetch_content_approvaltests/tests/CMakeLists.txt' title='File snippet was copied from'>snippet source</a></sup>
<!-- endInclude -->

This says that the libraries `ApprovalTests::ApprovalTests` and `Catch2::Catch2` are required by the `tests` executable.

Here is [this example project's test directory](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/main/fetch_content_approvaltests/tests).

**Dependencies**

How might you enable CMake to provide those libraries? In other words, what are the options for the contents of `dependencies/CMakeLists.txt`?

The next few sections describe some options.

#### Make CMake clone ApprovalTests.cpp and Catch2

**Note:** The files in this section can be viewed and downloaded from [fetch_content_approvaltests_catch2](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/main/fetch_content_approvaltests_catch2).

The following is for when you just want ApprovalTests.cpp and Catch2 to be downloaded as part of your project's build. You don't particularly want to see their source code, although you're happy if your debugger steps in to them.

It also needs CMake 3.14 or above.

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

Note the `GIT_TAG` values: This tells CMake which revision of dependencies to use. The value can be a tag or a git commit ID. Here we use `master`, to always test our integrations with the latest Approval Tests code. However, it is generally recommended to pin your dependencies to specific versions, and test behaviour before updating to newer versions. 

After CMake has generated the build files, the directory structure would look something like this, where the `cmake-build-debug` directory is the build space, and the `cmake-build-debug/_deps` contains the downloaded and built ApprovalTests.cpp and Catch2 repositories:

```
fetch_content_approvaltests_catch2/
  .git/
  cmake-build-debug/
    _deps/
      approvaltests-build/
      approvaltests-src/
      approvaltests-subbuild/
      catch2-build
      catch2-src
      catch2-subbuild
    ...
  CMakeLists.txt
  dependencies/
    CMakeLists.txt
  tests/
    ...
```

#### Make CMake clone ApprovalTests.cpp using CPM

The following is for when you just want ApprovalTests.cpp to be downloaded as part of your project's build. You don't particularly want to see their source code, although you're happy if your debugger steps in to them.

It also needs CMake 3.14 or above.

We use this in our `CMakeLists.txt` file:

<!-- snippet: cpm_download -->
<a id='snippet-cpm_download'></a>
```txt
message(STATUS "Add CPM.cmake")
# download CPM.cmake
file(
        DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.6/CPM.cmake
        ${CMAKE_BINARY_DIR}/cmake/CPM.cmake
        EXPECTED_HASH SHA256=11c3fa5f1ba14f15d31c2fb63dbc8628ee133d81c8d764caad9a8db9e0bacb07
)
include(${CMAKE_BINARY_DIR}/cmake/CPM.cmake)
```
<sup><a href='#snippet-cpm_download' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

<!-- snippet: cpm_add_approvaltests -->
<a id='snippet-cpm_add_approvaltests'></a>
```txt
message(STATUS "Fetching approvaltests")
CPMAddPackage(
        NAME approvaltests
        GITHUB_REPOSITORY approvals/ApprovalTests.cpp
        GIT_TAG master
)
```
<sup><a href='#snippet-cpm_add_approvaltests' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Note the `GIT_TAG` values: This tells CMake which revision of dependencies to use. The value can be a tag or a git commit ID. Here we use `master`. However, it is generally recommended to pin your dependencies to specific versions, and test behaviour before updating to newer versions.

After CMake has generated the build files, the directory structure would look something like this, where the `cmake-build-debug` directory is the build space, and the `cmake-build-debug/_deps` contains the downloaded and built ApprovalTests.cpp repository:

```
your_project/
  .git/
  cmake-build-debug/
    _deps/
      approvaltests-build/
      approvaltests-src/
      approvaltests-subbuild/
    ...
  CMakeLists.txt
  tests/
    ...
```

#### Make CMake clone ApprovalTests.cpp

**Note:** The files in this section can be viewed and downloaded from [fetch_content_approvaltests](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/main/fetch_content_approvaltests).

The only difference between the previous example and this one is that here we use the Catch2v2 header that is in the ApprovalTests.cpp project.

We use this `dependencies/CMakeLists.txt` file:

<!-- include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/fetch_content_approvaltests/mdsource/inc_fetch_content_approvaltests_dependencies_cmakelists.include.md -->

```cmake
# Needs CMake 3.14 or above
include(FetchContent)

# -------------------------------------------------------------------
# ApprovalTests.cpp
FetchContent_Declare(ApprovalTests
        GIT_REPOSITORY https://github.com/approvals/ApprovalTests.cpp.git
        GIT_TAG master)

# Tell the ApprovalTests CMake files that we want to use its copy of Catch2:
set(APPROVAL_TESTS_BUILD_THIRD_PARTY_CATCH2 ON CACHE BOOL "")

FetchContent_MakeAvailable(ApprovalTests)
```
<sup><a href='https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/main/./fetch_content_approvaltests/dependencies/CMakeLists.txt' title='File snippet was copied from'>snippet source</a></sup>
<!-- endInclude -->

We have set `APPROVAL_TESTS_BUILD_THIRD_PARTY_CATCH2` to `ON`, so that CMake will use the copy of Catch2 that is included in the ApprovalTests.cpp repository.

There are also options to enable use of ApprovalTests.cpp's copies of all other supported test frameworks except GoogleTest, including:

* `APPROVAL_TESTS_BUILD_THIRD_PARTY_DOCTEST`
* `APPROVAL_TESTS_BUILD_THIRD_PARTY_UT`

#### Use own ApprovalTests.cpp and Catch2 clones

**Note:** The files in this section can be viewed and downloaded from [add_subdirectory_approvaltests_catch2](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/main/add_subdirectory_approvaltests_catch2).

Here, instead of getting CMake to download ApprovalTests.cpp and Catch2, we have got our own clones or forks of them, which we want to use with our own tests.

In this example, the directory structure looks like this:

```
ApprovalTests.cpp/
  .git/
  CMakeLists.txt
  ...
Catch2/
  .git/
  CMakeLists.txt
  ...

add_subdirectory_approvaltests_catch2/
  .git/
  CMakeLists.txt
  dependencies/
    CMakeLists.txt
  tests/
```

We use this `dependencies/CMakeLists.txt` file:

<!-- include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/add_subdirectory_approvaltests_catch2/mdsource/inc_add_subdirectory_approvaltests_catch2_dependencies_cmakelists.include.md -->

```cmake
# -------------------------------------------------------------------
# ApprovalTests.cpp
add_subdirectory(
        ../../ApprovalTests.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/approvaltests.cpp_build
)

# -------------------------------------------------------------------
# Catch2
set(CATCH_BUILD_TESTING OFF CACHE BOOL "")
add_subdirectory(
        ../../Catch2
        ${CMAKE_CURRENT_BINARY_DIR}/catch2_build
)
```
<sup><a href='https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/main/./add_subdirectory_approvaltests_catch2/dependencies/CMakeLists.txt' title='File snippet was copied from'>snippet source</a></sup>
<!-- endInclude -->

Here we use `add_subdirectory()`. This works with older versions of CMake, unlike the `FetchContent` examples above.

The above was tested with CMake 3.8.

If your directory layout differed from the above, you would change the relative paths in the `add_subdirectory()` lines.

#### Using other supported test frameworks

To save space and repetition, the examples above only show the Catch2 test framework.

The same principles apply when using all the other test frameworks supported by ApprovalTests.cpp.

### Scenarios when developing ApprovalTests.cpp 

#### Developing ApprovalTests.cpp with test framework sources

**Note:** The files in this section can be viewed and downloaded
from [dev_approvals](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/main/dev_approvals).

For Approval Tests project maintainers, it is useful to be able to edit and debug both this project and the test
frameworks that it depends upon. It helps to be able to see the source of these frameworks, rather than just the
single-header releases that are copied in to the third_party directory here.

This also allows us to checkout different commits of any of these projects.

Here we want to enable and run all the ApprovalTests.cpp tests, unlike the cases above, where we only want to run the
tests of the project that is being developed.

Consider this directory structure, where the repositories for all these projects are checked out side-by-side, and there
is an extra directory `dev_approvals/` that will contain just a `CMakeLists.txt` file, to set up a project containing
all the other directories:

```
ApprovalTests.cpp/
  .git/
  CMakeLists.txt
  ...
Catch2/
  .git/
  CMakeLists.txt
  ...
doctest/
  .git/
  CMakeLists.txt
  ...
googletest/
  .git/
  CMakeLists.txt
  ...
ut/
  .git/
  CMakeLists.txt
  ...

dev_approvals/
  CMakeLists.txt
```

The file `dev_approvals/CMakeLists.txt` creates a kind of "super build": one project for developing ApprovalTests.cpp
and all the projects it depends on:

<!-- include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/dev_approvals/mdsource/inc_dev_approvals_cmakelists.include.md -->

```cmake
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(dev_approvals)

enable_testing()

set(CMAKE_VERBOSE_MAKEFILE off)

# Prevent ctest creating cluttering up CLion with nearly 30 CTest targets
# (Continuous, ContinuousBuild etc) when it does:
#   include(CTest)
# This hack taken from https://stackoverflow.com/a/57240389/104370
set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1) # hack to prevent CTest added targets

# -------------------------------------------------------------------
# boost
# This will be used by find_package() in ApprovalTests.cpp/tests/Boost_Tests
# If there is a local boost directory, use tat.
# Otherwise, require the user to have installed boost (as is done in CI builds)
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../boost)
    set(BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../boost)
endif()

# -------------------------------------------------------------------
# Catch2
set(CATCH_BUILD_TESTING OFF CACHE BOOL "")
add_subdirectory(
        ../Catch2
        ${CMAKE_CURRENT_BINARY_DIR}/catch2_build
)

# -------------------------------------------------------------------
# CppUTest

# Prevent CppUTest's own tests from being built
set(TESTS OFF CACHE BOOL "")

# Prevent build of CppUTest from generating thousands of lines of
# -Wc++98-compat and -Wc++98-compat-pedantic warnings:
set(C++11 ON CACHE BOOL "Compile with C++11 support")

add_subdirectory(
        ../cpputest
        ${CMAKE_CURRENT_BINARY_DIR}/cpputest_build
)

# -------------------------------------------------------------------
# doctest
add_subdirectory(
        ../doctest
        ${CMAKE_CURRENT_BINARY_DIR}/doctest_build
)

# -------------------------------------------------------------------
# filesystem
set(CATCH_BUILD_TESTING OFF CACHE BOOL "")
add_subdirectory(
        ../filesystem
        ${CMAKE_CURRENT_BINARY_DIR}/filesystem_build
)

# -------------------------------------------------------------------
# fmt
set(CATCH_BUILD_TESTING OFF CACHE BOOL "")
add_subdirectory(
        ../fmt
        ${CMAKE_CURRENT_BINARY_DIR}/fmt_build
)

# -------------------------------------------------------------------
# GoogleTest
# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" )
add_subdirectory(
        ../googletest
        ${CMAKE_CURRENT_BINARY_DIR}/googletest_build
)

# -------------------------------------------------------------------
# Boost.ut
set(BUILD_BENCHMARKS OFF CACHE BOOL "")
set(BUILD_EXAMPLES OFF CACHE BOOL "")
set(BUILD_TESTS OFF CACHE BOOL "")

add_subdirectory(
        ../ut
        ${CMAKE_CURRENT_BINARY_DIR}/ut_build
)

if(TARGET Boost::ut)
    add_library(boost.ut ALIAS ut)
endif()

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    # Turn off some checks off for boost.ut
    target_compile_options(ut INTERFACE
            -Wno-c99-extensions # Needed for Boost.ut, at least in v1.1.6
            -Wno-documentation-unknown-command # unknown command tag name \userguide
            -Wno-weak-vtables
            -Wno-comma # See https://github.com/boost-ext/ut/issues/398
            )
endif()

# -------------------------------------------------------------------
# ApprovalTests.cpp

set(APPROVAL_TESTS_BUILD_TESTING ON CACHE BOOL "")
set(APPROVAL_TESTS_BUILD_EXAMPLES ON CACHE BOOL "")

add_subdirectory(
        ../ApprovalTests.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/approvaltests.cpp_build
)
```
<sup><a href='https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/main/./dev_approvals/CMakeLists.txt' title='File snippet was copied from'>snippet source</a></sup>
<!-- endInclude -->

---

[Back to User Guide](/doc/README.md#top)
