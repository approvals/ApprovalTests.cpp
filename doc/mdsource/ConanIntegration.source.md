<a id="top"></a>

# Conan Integration

toc

## Using Conan to obtain ApprovalTests.cpp

The [Conan C++ package manager](https://conan.io) knows how to download released versions of ApprovalTests.cpp, and integrate the downloaded single-header file in to various C++ build systems.

This page assumes basic familiarity with Conan. For more information, see [Conan's extensive documentation](https://docs.conan.io/en/latest/index.html).

## Example Conan CMake Setups

These examples demonstrate a few applications of Conan with ApprovalTests.cpp.

### Using Conan's cmake generator

**Note:** The files in this section can be viewed and downloaded from [conan_cmake](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/main/conan_cmake).

This example use Conan's [cmake Generator](https://docs.conan.io/en/latest/reference/generators/cmake.html).

The `conanfile.txt` file lists the required libraries, and which generator to use (here, `conan`):

include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/conan_cmake/mdsource/inc_conan_cmake_conanfile.include.md

The `conan` generator generates a `conanbuildinfo.cmake` file, which needs to used in the top-level CMakeLists.txt file like this:

include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/conan_cmake/mdsource/inc_conan_cmake_cmakelists.include.md

And the CMakeLists.txt that builds the tests is as follows (note the Conan-specific library target names):

include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/conan_cmake/mdsource/inc_conan_cmake_tests_cmakelists.include.md

Example set of build commands to download dependencies, make the test program and run the tests:

include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/conan_cmake/mdsource/inc_conan_cmake_build.include.md

## Other people's examples

Some examples of using the [Conan package manager](https://conan.io/):

* Daniel Heater's [ApprovalTests-ConanDemo repo](https://github.com/dheater/ApprovalTests-ConanDemo)
    * This demonstrates using ApprovalTests.cpp with Conan's `cmake` generator in a `conanfile.txt` file.
* p-podsiadly's 
[ImageApprovals](https://github.com/p-podsiadly/ImageApprovals)
    * This shows a different approach, using Conan's `cmake_find_package` generator from purely CMake code.
    * It's also a nice example of extending ApprovalTests.cpp to compare images.

## Links

* For users: [conan.io/center/approvaltests.cpp](https://conan.io/center/approvaltests.cpp/10.1.1/?user=_&channel=_)
    * Note: There may well be newer versions available than this link points to.
* For maintainers: [the Conan recipe: approvaltests.cpp](https://github.com/conan-io/conan-center-index/tree/master/recipes/approvaltests.cpp)

---

[Back to User Guide](/doc/README.md#top)
