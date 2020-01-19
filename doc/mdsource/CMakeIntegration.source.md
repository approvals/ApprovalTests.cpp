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

## Scenarios

### Developing ApprovalTests.cpp

It is useful to be able to edit and debug both this project and the test frameworks that it depends upon. It helps to be able to see the source code of these frameworks, rather than just the single-header releases that are copied in to the third_party directory here.

This also allows us to update to different commits of any of these projects.

If the repositories for all these projects are checked out in the the same directory, then this `CMakeLists.txt` file can be put in to a parallel directory.

include: inc_develop_approvaltests_cmakelists

---

[Back to User Guide](/doc/README.md#top)
