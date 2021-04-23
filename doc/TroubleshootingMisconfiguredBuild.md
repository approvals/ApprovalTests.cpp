<a id="top"></a>

# Troubleshooting Misconfigured Build

<!-- toc -->
## Contents

  * [Version v.10.8.0](#version-v1080)
  * [Before v.10.8.0](#before-v1080)
    * [Feedback Requested](#feedback-requested)
    * [Symptoms](#symptoms)
      * [Compilation Error](#compilation-error)
      * [Test Failure](#test-failure)
    * [The problem](#the-problem)
      * [Ninja generator](#ninja-generator)
    * [Solutions](#solutions)
      * [Use a Ninja Unity build, if you can](#use-a-ninja-unity-build-if-you-can)
      * [Move your build outside the source tree](#move-your-build-outside-the-source-tree)
      * [Force the compiler to use full-paths in `__FILE__`](#force-the-compiler-to-use-full-paths-in-__file__)
      * [With \[Boost\].UT, check compiler and build options](#with-boostut-check-compiler-and-build-options)
      * [Use a non-Ninja generator](#use-a-non-ninja-generator)
    * [Specific Situations](#specific-situations)
      * [Situation: Visual Studio with Visual C++ compiler (cl.exe)](#situation-visual-studio-with-visual-c-compiler-clexe)
      * [Situation: Visual Studio with Clang compiler (clang-cl.exe)](#situation-visual-studio-with-clang-compiler-clang-clexe)
      * [Situation: CMake's Ninja Generator](#situation-cmakes-ninja-generator)<!-- endToc -->

## Version v.10.8.0

Significant improvements regarding the Ninja build system were made in Approval Tests v.10.8.0. Our suggestion is that
if you are using an older version, start by upgrading.

## Before v.10.8.0

### Feedback Requested

This is living documentation. If you discover extra scenarios or better solutions, please contribute back via bug
reports or pull requests. Thank you.

### Symptoms

#### Compilation Error

Prior to v.10.8.0, compiling tests in Ninja-generated builds gives a compilation failure, with this message:

```h
"There seems to be a problem with your build configuration, probably with Ninja. "
"Please visit https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredBuild.md "
"The filename is: "
__FILE__
```

#### Test Failure

Prior to v.10.8.0, running tests gives output such as the following:

<!-- snippet: ForgottenToConfigure.HelpMessageForIncorrectBuildConfig.approved.txt -->
<a id='snippet-ForgottenToConfigure.HelpMessageForIncorrectBuildConfig.approved.txt'></a>
```txt
*****************************************************************************
*                                                                           *
* Welcome to Approval Tests.
*
* There seems to be a problem with your build configuration.
* We cannot find the test source file at:
*   ../../../tests/Catch2_Tests/ApprovalsTests.cpp
*
* For details on how to fix this, please visit:
* https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredBuild.md
*
* For advanced users only:
* If you believe you have reached this message in error, you can bypass
* the check by calling ApprovalTestNamer::setCheckBuildConfig(false);
*                                                                           *
*****************************************************************************
```
<sup><a href='/tests/DocTest_Tests/docs/approval_tests/ForgottenToConfigure.HelpMessageForIncorrectBuildConfig.approved.txt#L1-L16' title='Snippet source file'>snippet source</a> | <a href='#snippet-ForgottenToConfigure.HelpMessageForIncorrectBuildConfig.approved.txt' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

### The problem

#### Ninja generator

Approval Tests depends on the test framework to provide access to the full path of the source file of the test being run.

In many cases, this is implemented using `__FILE__`.

With some build configurations, we have found that the path contained in `__FILE__` contains either just the file name, or contains an incorrect relative path to a non-existent directory, relative to the current working directory of the test program.

This is what we have established:

* Some compilers only put a relative path in to `__FILE__`, if the filename they are given on the command line was relative
* On all platforms, the [Ninja build generator](https://ninja-build.org):
  * gives the compiler **relative paths**, if the build tree is inside the source tree
  * gives the compiler **absolute paths** if build tree is outside the source tree
* Visual Studio recently changed its default generator to Ninja, making the problem much more common.

This means that **if Ninja is used to create a build-space that is inside the source tree, Approval Tests-based tests will fail**.

Note that Visual C++ has a way to over-ride this and force absolute paths, if given `/FC`. This is described below, in [Situation: Visual Studio with Visual C++ compiler (cl.exe)](/doc/TroubleshootingMisconfiguredBuild.md#situation-visual-studio-with-visual-c-compiler-clexe).

### Solutions

This section lists the known types of workaround for the above problems.

#### Use a Ninja Unity build, if you can

When used to generate Unity builds, the Ninja build generator creates executables that run correctly with Approval Tests, finding the source file location correctly. 

For more information about Unity builds in CMake, see this article: [CMake 3.16 added support for precompiled headers & unity builds - what you need to know](https://onqtam.com/programming/2019-12-20-pch-unity-cmake-3-16/). It also describes the initial problems you may encounter when trying to compile a project as Unity, and how to fix them.

If you are using **CMake 3.16 or above**, it is easy to turn on Unity builds, and the following examples show you how.

**Using the ApprovalTests.cpp repo**

Here is an example CMake command-line for creating Unity builds with the Ninja generator:

```bash
# CMake 3.16 or above:
cmake -G "Ninja" -DCMAKE_UNITY_BUILD=yes <source_location>
```

In the following situations, the above is all you need to do, for all the supported test frameworks to work correctly:

* You are building the ApprovalTests.cpp project with CMake.
* You have added the ApprovalTests.cpp project to your own CMake build, via `add_subdirectory()`. For more information on the options for this, see [CMake Integration](/doc/CMakeIntegration.md#top).

**Using the ApprovalTests.cpp single-header download**

If you are using the single-header download of Approval Tests with a Ninja Unity build, you may find that you get a compilation failure, pointing to this page, when in fact the tests would run correctly.

In this case, you will need to disable the compilation check of `__FILE__`, which can be done by defining the `APPROVAL_TESTS_DISABLE_FILE_MACRO_CHECK` macro. This can be done line this:

```bash
# CMake 3.16 or above - with other frameworks, including Catch2, doctest, Google Test:
cmake -G "Ninja" -DCMAKE_UNITY_BUILD=yes \
    -DCMAKE_CXX_FLAGS_INIT=-DAPPROVAL_TESTS_DISABLE_FILE_MACRO_CHECK \
    <source_location>
```

#### Move your build outside the source tree

The problem with Ninja builds generating relative paths to source files only occurs if the build is inside the source tree.

If you are able to move your build outside the source tree, Ninja will generate absolute paths to source files, and Approval Tests will work fine.

If you need help to do this, see the various sections in [Specific Situations](/doc/TroubleshootingMisconfiguredBuild.md#specific-situations) below.

#### Force the compiler to use full-paths in `__FILE__`

This can be done with Visual C++: see below.

#### With \[Boost\].UT, check compiler and build options

The \[Boost\].UT framework uses very recent features of C++, and is changing somewhat rapidly.

If the ApprovalTests.cpp integration with \[Boost\].UT is not working in your build, you will see probably the following output at run-time, where the filename is `unknown`:

<!-- snippet: ForgottenToConfigure.HelpMessageForIncorrectBoostUTConfig.approved.txt -->
<a id='snippet-ForgottenToConfigure.HelpMessageForIncorrectBoostUTConfig.approved.txt'></a>
```txt
*****************************************************************************
*                                                                           *
* Welcome to Approval Tests.
*
* There seems to be a problem with your build configuration.
* We cannot find the test source file at:
*   unknown
*
* For details on how to fix this, please visit:
* https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredBuild.md
*
* For advanced users only:
* If you believe you have reached this message in error, you can bypass
* the check by calling ApprovalTestNamer::setCheckBuildConfig(false);
*                                                                           *
*****************************************************************************
```
<sup><a href='/tests/DocTest_Tests/docs/approval_tests/ForgottenToConfigure.HelpMessageForIncorrectBoostUTConfig.approved.txt#L1-L16' title='Snippet source file'>snippet source</a> | <a href='#snippet-ForgottenToConfigure.HelpMessageForIncorrectBoostUTConfig.approved.txt' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

These are possible causes:

* Check that your compiler and build options satisfy the [requirements for using Approval Tests With \[Boost\].UT](/doc/UsingUT.md#requirements).
* If you have downloaded your own copy of the \[Boost\].UT framework, it's possible that it is not compatible with the ApprovalTests.cpp version you are using. It will be worth comparing your version of the \[Boost\].UT header with the one in this project: [third_party/ut/include/boost/ut.hpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/third_party/ut/include/boost/ut.hpp).

#### Use a non-Ninja generator

If you can't use any of the above, your only option to work around this Ninja limitation is probably to switch to a [different CMake generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) than Ninja.

### Specific Situations

#### Situation: Visual Studio with Visual C++ compiler (cl.exe)

Use `/FC` to make Visual Studio emit the full path in diagnostics, and `__FILE__` ([documentation](https://docs.microsoft.com/en-us/cpp/build/reference/fc-full-path-of-source-code-file-in-diagnostics?view=vs-2019)).

If you are using this project by cloning or forking its repository, and then using CMake's `add_subdirectory()`, this will be done for you automatically, for all targets that use the provided [CMake target](/doc/CMakeIntegration.md#cmake-target).

Otherwise (such as if you are using the downloaded single-header file, or you have set up your own CMake builds), you need to add a line like the following to your `CMakeLists.txt` file:

```cmake
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(my_program_name PUBLIC /FC)
endif()
```

Or this:

```cmake
target_compile_options(my_program_name PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/FC>)
```

#### Situation: Visual Studio with Clang compiler (clang-cl.exe)

We have not been able to find a compiler flag that makes clang-cl put full paths in `__FILE__`.

The only solution we have found is to put your build outputs in a directory outside the source tree, so that the build will use absolute paths.

One way to do this is to edit your `CMakeSettings.json` file, and change all pairs of lines like this:

```
      "buildRoot": "${projectDir}\\out\\build\\${name}",
      "installRoot": "${projectDir}\\out\\install\\${name}",
```

To something like this (where you change `MyProjectName` to the actual name of your project):

```
      "buildRoot": "${env.USERPROFILE}\\CMakeBuilds\\MyProjectName\\build\\${name}",
      "installRoot": "${env.USERPROFILE}\\CMakeBuilds\\MyProjectName\\install\\${name}",
```

This would put the build outputs in to:

`C:\Users\YourUserName\CMakeBuilds\MyProjectName\build`

#### Situation: CMake's Ninja Generator

The easiest solution is probably to use a [different CMake generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) instead of Ninja.

However, if you wish to continue using Ninja, you will need to create and use a build directory outside of your source directory. 

For example, with CMake, you might do this:

```bash
cd ApprovalTests.cpp
mkdir ../build_approval_tests_ninja
cd    ../build_approval_tests_ninja
cmake -G Ninja ../ApprovalTests.cpp
cmake --build .
ctest
``` 

---

[Back to User Guide](/doc/README.md#top)
