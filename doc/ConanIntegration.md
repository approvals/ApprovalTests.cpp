<a id="top"></a>

# Conan Integration

<!-- toc -->
## Contents

  * [Using Conan to obtain ApprovalTests.cpp](#using-conan-to-obtain-approvaltestscpp)
  * [Example Conan CMake Setups](#example-conan-cmake-setups)
    * [Example 1. Using Conan's cmake_find_package and cmake_paths generators](#example-1-using-conans-cmake_find_package-and-cmake_paths-generators)
    * [Example 2. Using Conan's cmake generator](#example-2-using-conans-cmake-generator)
    * [Example 3. Making CMake invoke Conan](#example-3-making-cmake-invoke-conan)
  * [Other people's examples](#other-peoples-examples)
  * [Links](#links)<!-- endToc -->

## Using Conan to obtain ApprovalTests.cpp

The [Conan C++ package manager](https://conan.io) knows how to download released versions of ApprovalTests.cpp, and integrate the downloaded single-header file in to various C++ build systems.

This page assumes basic familiarity with Conan. For more information, see [Conan's extensive documentation](https://docs.conan.io/en/latest/index.html).

## Example Conan CMake Setups

These examples demonstrate a few different ways of using Conan with ApprovalTests.cpp. They differ in which [Conan generator](https://docs.conan.io/en/latest/integrations/build_system/cmake.html#cmake) they use.

They all specify their dependencies in a [`conanfile.txt`](https://docs.conan.io/en/latest/reference/conanfile_txt.html) file, but they could just as easily use a [`conanfile.py`](https://docs.conan.io/en/latest/reference/conanfile.html) instead.

### Example 1. Using Conan's cmake_find_package and cmake_paths generators

> **Scenario:** I want to use CMake's `find_package()` and have Conan obtain the packages for me. I only want the Conan references to appear at the top of my project.

**Note:** The files in this section can be viewed and downloaded from [conan_cmake_find_package](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/main/conan_cmake_find_package).

This example use Conan's [cmake_find_package](https://docs.conan.io/en/latest/integrations/build_system/cmake/cmake_find_package_generator.html) generator, and optionally also the [cmake_paths](https://docs.conan.io/en/latest/integrations/build_system/cmake/cmake_paths_generator.html) generator.

The benefit of these generators is consistency: the target names for dependencies (for example, `ApprovalTests::ApprovalTests`) are generally the same as you would get if building against the library's own CMake files.

This gives more flexibility, as it opens up the possibility of some users obtaining dependencies via Conan, and other users building the dependencies themselves, with CMake)

The `conanfile.txt` file lists the required libraries, and which generator to use (here, `cmake_find_package` and optionally `cmake_paths`):

<!-- include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/conan_cmake_find_package/mdsource/inc_conan_cmake_find_package_conanfile.include.md -->

```
[requires]
catch2/2.13.4
approvaltests.cpp/10.7.0

[generators]
cmake_find_package
cmake_paths
```
<sup><a href='https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/main/./conan_cmake_find_package/conanfile.txt' title='File snippet was copied from'>snippet source</a></sup>
<!-- endInclude -->

There are two choices for the CMake instructions used in the top-level CMakeLists.txt file with these generators, as explained in the comments here:

<!-- include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/conan_cmake_find_package/mdsource/inc_conan_cmake_find_package_cmakelists.include.md -->

```cmake
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(conan_cmake_find_package)

# EITHER Using the "cmake_find_package" generator
#set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
#set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR} ${CMAKE_PREFIX_PATH})

# OR Using the "cmake_find_package" and "cmake_paths" generators
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

find_package(Catch2 REQUIRED)
find_package(ApprovalTests REQUIRED)

enable_testing()

add_subdirectory(tests)
```
<sup><a href='https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/main/./conan_cmake_find_package/CMakeLists.txt' title='File snippet was copied from'>snippet source</a></sup>
<!-- endInclude -->

And the CMakeLists.txt that builds the tests is as follows (note the standard library target names):

<!-- include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/conan_cmake_find_package/mdsource/inc_conan_cmake_find_package_tests_cmakelists.include.md -->

```cmake
add_executable(tests
        main.cpp
        tests.cpp
)
target_link_libraries(
        tests
        ApprovalTests::ApprovalTests
        Catch2::Catch2)

target_compile_features(tests PUBLIC cxx_std_11)
set_target_properties(tests PROPERTIES CXX_EXTENSIONS OFF)

add_test(
        NAME tests
        COMMAND tests)
```
<sup><a href='https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/main/./conan_cmake_find_package/tests/CMakeLists.txt' title='File snippet was copied from'>snippet source</a></sup>
<!-- endInclude -->

Example set of build commands to download dependencies, make the test program and run the tests:

<!-- include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/conan_cmake_find_package/mdsource/inc_conan_cmake_find_package_build.include.md -->

```bash
#!/bin/bash

# Force execution to halt if there are any errors in this script:
set -e
set -o pipefail

mkdir -p build
cd       build
conan install ..
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
ctest --output-on-failure . -C Debug
```
<sup><a href='https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/main/./conan_cmake_find_package/build.sh' title='File snippet was copied from'>snippet source</a></sup>
<!-- endInclude -->

### Example 2. Using Conan's cmake generator

> **Scenario:** I'm only going to be building with Conan, so I don't mind Conan-specific libraries appearing in `target_link_libraries()` in CMake: I just want my top-level CMake files to be simple - not cluttered with find_packages().

**Note:** The files in this section can be viewed and downloaded from [conan_cmake](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/main/conan_cmake).

This example use Conan's [cmake](https://docs.conan.io/en/latest/integrations/build_system/cmake/cmake_generator.html) Generator.

The `conanfile.txt` file lists the required libraries, and which generator to use (here, `conan`):

<!-- include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/conan_cmake/mdsource/inc_conan_cmake_conanfile.include.md -->

```
[requires]
catch2/2.13.4
approvaltests.cpp/10.7.0

[generators]
cmake
```
<sup><a href='https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/main/./conan_cmake/conanfile.txt' title='File snippet was copied from'>snippet source</a></sup>
<!-- endInclude -->

The `conan` generator generates a `conanbuildinfo.cmake` file, which needs to used in the top-level CMakeLists.txt file like this:

<!-- include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/conan_cmake/mdsource/inc_conan_cmake_cmakelists.include.md -->

```cmake
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(conan_cmake)

# Conan's cmake generator creates a conanbuildinfo.cmake file, which we
# need to include, and then use:
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

enable_testing()

add_subdirectory(tests)
```
<sup><a href='https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/main/./conan_cmake/CMakeLists.txt' title='File snippet was copied from'>snippet source</a></sup>
<!-- endInclude -->

And the CMakeLists.txt that builds the tests is as follows (note the Conan-specific library target names):

<!-- include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/conan_cmake/mdsource/inc_conan_cmake_tests_cmakelists.include.md -->

```cmake
add_executable(tests
        main.cpp
        tests.cpp
)

# Note the Conan-specific library namees, beginning with CONAN_PKG.
# Conan sets up these names when its cmake generator is used.
# This ties your project to using Conan.
target_link_libraries(
        tests
        CONAN_PKG::approvaltests.cpp
        CONAN_PKG::catch2)

target_compile_features(tests PUBLIC cxx_std_11)
set_target_properties(tests PROPERTIES CXX_EXTENSIONS OFF)

add_test(
        NAME tests
        COMMAND tests)
```
<sup><a href='https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/main/./conan_cmake/tests/CMakeLists.txt' title='File snippet was copied from'>snippet source</a></sup>
<!-- endInclude -->

Example set of build commands to download dependencies, make the test program and run the tests:

<!-- include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/conan_cmake/mdsource/inc_conan_cmake_build.include.md -->

```bash
#!/bin/bash

# Force execution to halt if there are any errors in this script:
set -e
set -o pipefail

mkdir -p build
cd       build
conan install ..
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
ctest --output-on-failure . -C Debug
```
<sup><a href='https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/main/./conan_cmake/build.sh' title='File snippet was copied from'>snippet source</a></sup>
<!-- endInclude -->

### Example 3. Making CMake invoke Conan

> **Scenario:** I want to use CMake without having to remember to run a Conan command to make it download my dependencies.
>
> This will mean your dependencies are always uptodate (at the cost of a slightly slower build)

**Note:** The files in this section can be viewed and downloaded from [cmake_invoking_conan](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/main/cmake_invoking_conan).

This example use Conan's [cmake-conan](https://github.com/conan-io/cmake-conan) CMake module.

An advantage of this approach is that a project can use Conan to download dependencies, without people building that needing to know to run `conan install`. Anyone who is used to using CMake to generate builds will be able to build projects that use this mechanism. There will still need to be an installation of Conan on the build machine, however.

The `conanfile.txt` file lists the required libraries but does not say which generator to use:

<!-- include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/cmake_invoking_conan/mdsource/inc_cmake_invoking_conan_conanfile.include.md -->

```
# See CMake/Conan.cmake for how 'conan install' is launched from cmake

[requires]
catch2/2.13.4
approvaltests.cpp/10.7.0

# Note that we don't say what generator we want.
# CMake code will take care of that for us.
```
<sup><a href='https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/main/./cmake_invoking_conan/conanfile.txt' title='File snippet was copied from'>snippet source</a></sup>
<!-- endInclude -->

There is a CMake file called `CMake/Conan.cmake` which contains instructions for downloading a specific version of the cmake-conan CMake module:

<!-- include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/cmake_invoking_conan/mdsource/inc_cmake_invoking_conan_CMake_conan.include.md -->

```cmake
macro(run_conan)
# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(
    STATUS
      "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
       "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_add_remote(NAME bincrafters URL
                 https://api.bintray.com/conan/bincrafters/public-conan)

conan_cmake_run(
  CONANFILE conanfile.txt
  BASIC_SETUP
  CMAKE_TARGETS # individual targets to link to
  BUILD
    missing
)
endmacro()
```
<sup><a href='https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/main/./cmake_invoking_conan/CMake/Conan.cmake' title='File snippet was copied from'>snippet source</a></sup>
<!-- endInclude -->

The top-level CMakeLists.txt file includes the above `CMake/Conan.cmake` file, and runs the macro that it contained:

<!-- include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/cmake_invoking_conan/mdsource/inc_cmake_invoking_conan_cmakelists.include.md -->

```cmake
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(conan_cmake)

# Load CMake/Conan.cmake, which sets up a 'run_conan()' macro to download dependencies.
include(CMake/Conan.cmake)
run_conan()

enable_testing()

add_subdirectory(tests)
```
<sup><a href='https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/main/./cmake_invoking_conan/CMakeLists.txt' title='File snippet was copied from'>snippet source</a></sup>
<!-- endInclude -->

And the CMakeLists.txt that builds the tests is as follows (note the Conan-specific library target names):

<!-- include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/cmake_invoking_conan/mdsource/inc_cmake_invoking_conan_tests_cmakelists.include.md -->

```cmake
add_executable(tests
        main.cpp
        tests.cpp
)

# Note the Conan-specific library namees, beginning with CONAN_PKG.
# Conan sets up these names when its cmake generator is used.
# This ties your project to using Conan.
target_link_libraries(
        tests
        CONAN_PKG::approvaltests.cpp
        CONAN_PKG::catch2)

target_compile_features(tests PUBLIC cxx_std_11)
set_target_properties(tests PROPERTIES CXX_EXTENSIONS OFF)

add_test(
        NAME tests
        COMMAND tests)
```
<sup><a href='https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/main/./cmake_invoking_conan/tests/CMakeLists.txt' title='File snippet was copied from'>snippet source</a></sup>
<!-- endInclude -->

Example set of build commands to download dependencies, make the test program and run the tests - note that there isno line to run conan:

<!-- include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/cmake_invoking_conan/mdsource/inc_cmake_invoking_conan_build.include.md -->

```bash
#!/bin/bash

# Force execution to halt if there are any errors in this script:
set -e
set -o pipefail

mkdir -p build
cd       build
# Note that we do not need to invoke conan.
# However, we do need to say what build configuration we want.
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
ctest --output-on-failure . -C Debug
```
<sup><a href='https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/main/./cmake_invoking_conan/build.sh' title='File snippet was copied from'>snippet source</a></sup>
<!-- endInclude -->

## Other people's examples

Some examples of using the [Conan package manager](https://conan.io/):

* Daniel Heater's [ApprovalTests-ConanDemo repo](https://github.com/dheater/ApprovalTests-ConanDemo)
    * This demonstrates using ApprovalTests.cpp with Conan's `cmake` generator in a `conanfile.txt` file.
* p-podsiadly's 
    [ImageApprovals](https://github.com/p-podsiadly/ImageApprovals)
    * This shows a different approach, using Conan's `cmake_find_package` generator from purely CMake code.
    * It's also a nice example of extending ApprovalTests.cpp to compare images.

## Links

* For users: [conan.io/center/approvaltests.cpp](https://conan.io/center/approvaltests.cpp)
* For maintainers: [the Conan recipe: approvaltests.cpp](https://github.com/conan-io/conan-center-index/tree/master/recipes/approvaltests.cpp)

---

[Back to User Guide](/doc/README.md#top)
