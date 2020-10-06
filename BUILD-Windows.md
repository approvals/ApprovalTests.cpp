<a id="top"></a>

# Developing ApprovalTests.cpp on Windows

<!-- toc -->
## Contents

  * [Prerequisites](#prerequisites)
  * [Dependencies](#dependencies)
  * [Visual Studio 2017 Community Edition](#visual-studio-2017-community-edition)
    * [Use CMake to generate Visual Studio 2017 configuration](#use-cmake-to-generate-visual-studio-2017-configuration)
  * [CLion](#clion)
    * [Use CLion with Visual Studio installed](#use-clion-with-visual-studio-installed)
    * [Run CLion with cygwin as toolset](#run-clion-with-cygwin-as-toolset)<!-- endToc -->

## Prerequisites

* CMake 3.8 or higher
* A C++11 or above compiler to use the library
* A C++17 or above compiler to run the project's own tests

## Dependencies

* See [third_party/](/third_party/) for the test frameworks that are included in this project.
* Source code for the **Google Test framework** - version 1.8.1 - is downloaded automatically when CMake is run - see [/CMake/googletest/CMakeLists.txt.in](/CMake/googletest/CMakeLists.txt.in), and is then built when the project is built.
* Similarly, the **{fmt}** library is downloaded automatically when CMake is run - see [/CMake/fmt/CMakeLists.txt.in](/CMake/fmt/CMakeLists.txt.in), and is then built when the project is built.
* **Boost** needs to be found by CMake's `find_package()` - see [/tests/Boost_Tests/CMakeLists.txt](/tests/Boost_Tests/CMakeLists.txt).

## Visual Studio 2017 Community Edition

### Use CMake to generate Visual Studio 2017 configuration

Decide where to put the build files that CMake will generate.
In the following, we're putting the output in `cmake-build-vs` - that location is already ignored by git.

1. Open a Command window
2. Then run:

		cd ApprovalTests.cpp
		mkdir cmake-build-vs
		cd    cmake-build-vs
		cmake -G "Visual Studio 15 2017" ..

## CLion

### Use CLion with Visual Studio installed

* Follow the instructions for experimental support of [Microsoft Visual C++ compiler](https://www.jetbrains.com/help/clion/quick-tutorial-on-configuring-clion-on-windows.html)
* Output is put in `cmake-build-debug`
* Tested with Visual Studio 2017
* **Major limitation**: Debugging is not yet supported by CLion, when compiling with Visual Studio, as of CLion 2017.3.3

### Run CLion with cygwin as toolset

* Code builds fine
* Tests run fine
* Reporters run fine
