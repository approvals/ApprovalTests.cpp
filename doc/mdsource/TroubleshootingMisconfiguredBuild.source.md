<a id="top"></a>

# Troubleshooting Misconfigured Build

toc

## Feedback Requested

This is living documentation. If you discover extra scenarios or better solutions, please contribute back via bug reports or pull requests. Thank you. 

## Symptoms

Running tests gives output such as the following:

snippet: ForgottenToConfigure.HelpMessageForIncorrectBuildConfig.approved.txt

## The problem

Approval Tests depends on the test framework to provide access to the source file of the test being run.

In many cases, this is implementing using `__FILE__`.

With some build configurations, we have found that the path contained in `__FILE__` contains either just the file name, or contains an incorrect relative path to a non-existent directory, relative to the current working directory of the test program. 

## Situation: Visual Studio with Visual C++ compiler (cl.exe)

Use `/FC` to make Visual Studio emit the full path in diagnostics, and `__FILE__` ([documentation](https://docs.microsoft.com/en-us/cpp/build/reference/fc-full-path-of-source-code-file-in-diagnostics?view=vs-2019)).

You need to add a line like the following to your `CMakeLists.txt` file:

```cmake
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /FC)
endif()
```

## Situation: Visual Studio with Clang compiler (clang-cl.exe)

We have not been able to find a compiler flag that makes clang-cl put full paths in `__FILE__`.

The only solution we have found is to put your build outputs in a directory outside the source tree.

---

[Back to User Guide](/doc/README.md#top)
