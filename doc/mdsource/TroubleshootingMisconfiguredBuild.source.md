<a id="top"></a>

# Troubleshooting Misconfigured Build

toc

## Feedback Requested

This is living documentation. If you discover extra scenarios or better solutions, please contribute back via bug reports or pull requests. Thank you. 

## Symptoms

### Compilation Error

Compiling tests in Ninja-generated builds gives a compilation failure, with this message:

snippet: compiler_error_for_misconfigured_build

### Test Failure

Running tests gives output such as the following:

snippet: ForgottenToConfigure.HelpMessageForIncorrectBuildConfig.approved.txt

## The problem

### Ninja generator

Approval Tests depends on the test framework to provide access to the full path of the source file of the test being run.

In many cases, this is implemented using `__FILE__`.

With some build configurations, we have found that the path contained in `__FILE__` contains either just the file name, or contains an incorrect relative path to a non-existent directory, relative to the current working directory of the test program.

This is what we have established:

* Some compilers only put a relative path in to `__FILE__`, if the filename they are given on the command line was relative
* On all platforms, the Ninja generator:
  * gives the compiler **relative paths**, if the build tree is inside the source tree
  * gives the compiler **absolute paths** if build tree is outside the source tree
* Visual Studio recently changed its default generator to Ninja, making the problem much more common.

This means that **if Ninja is used to create a build-space that is inside the source tree, Approval Tests-based tests will fail**.

Visual C++ has a way to over-ride this and force absolute paths, if given `/FC`


## Solutions

### Situation: Visual Studio with Visual C++ compiler (cl.exe)

Use `/FC` to make Visual Studio emit the full path in diagnostics, and `__FILE__` ([documentation](https://docs.microsoft.com/en-us/cpp/build/reference/fc-full-path-of-source-code-file-in-diagnostics?view=vs-2019)).

You need to add a line like the following to your `CMakeLists.txt` file:

```cmake
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(my_program_name PUBLIC /FC)
endif()
```

Or this:

```cmake
target_compile_options(my_program_name PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/FC>)
```

### Situation: Visual Studio with Clang compiler (clang-cl.exe)

We have not been able to find a compiler flag that makes clang-cl put full paths in `__FILE__`.

The only solution we have found is to put your build outputs in a directory outside the source tree, so that the build will use absolute paths.

One way to do this is to edit your `CMakeSettings.json` file, and change all pairs of lines like this:

```json
      "buildRoot": "${projectDir}\\out\\build\\${name}",
      "installRoot": "${projectDir}\\out\\install\\${name}",
```

To something like this (where you change `MyProjectName` to the actual name of your project):

```json
      "buildRoot": "${env.USERPROFILE}\\CMakeBuilds\\MyProjectName\\build\\${name}",
      "installRoot": "${env.USERPROFILE}\\CMakeBuilds\\MyProjectName\\install\\${name}",
```

This would put the build outputs in to:

`C:\Users\YourUserName\CMakeBuilds\MyProjectName\build`

---

[Back to User Guide](/doc/README.md#top)
