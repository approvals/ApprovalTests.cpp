<a id="top"></a>

# Conan Integration

toc

## Using Conan to obtain ApprovalTests.cpp

The [Conan C++ package manager](https://conan.io) knows how to download released versions of ApprovalTests.cpp, and integrate the downloaded single-header file in to various C++ build systems.

This page assumes basic familiarity with Conan. For more information, see [Conan's extensive documentation](https://docs.conan.io/en/latest/index.html).

## Example Conan CMake Setups

These examples demonstrate a few different ways of using Conan with ApprovalTests.cpp. They differ in which [Conan generator](https://docs.conan.io/en/latest/integrations/build_system/cmake.html#cmake) they use.

They all specify their dependencies in a [`conanfile.txt`](https://docs.conan.io/en/latest/reference/conanfile_txt.html) file, but they could just as easily use a [`conanfile.py`](https://docs.conan.io/en/latest/reference/conanfile.html) instead.

### Using Conan's cmake_find_package and cmake_paths generators

**Note:** The files in this section can be viewed and downloaded from [conan_cmake_find_package](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/main/conan_cmake_find_package).

This example use Conan's [cmake_find_package](https://docs.conan.io/en/latest/integrations/build_system/cmake/cmake_find_package_generator.html) generator, and optionally also the [cmake_paths](https://docs.conan.io/en/latest/integrations/build_system/cmake/cmake_paths_generator.html) generator.

The benefit of these generators is consistency: the target names for dependencies (for example, `ApprovalTests::ApprovalTests`) are generally the same as you would get if building against the library's own CMake files.

This gives more flexibility, as it opens up the possibility of some users obtaining dependencies via Conan, and other users building the dependencies themselves, with CMake)

The `conanfile.txt` file lists the required libraries, and which generator to use (here, `cmake_find_package` and optionally `cmake_paths`):

include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/conan_cmake_find_package/mdsource/inc_conan_cmake_find_package_conanfile.include.md

There are two choices for the CMake instructions used in the top-level CMakeLists.txt file with these generators, as explained in the comments here:

include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/conan_cmake_find_package/mdsource/inc_conan_cmake_find_package_cmakelists.include.md

And the CMakeLists.txt that builds the tests is as follows (note the standard library target names):

include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/conan_cmake_find_package/mdsource/inc_conan_cmake_find_package_tests_cmakelists.include.md

Example set of build commands to download dependencies, make the test program and run the tests:

include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/conan_cmake_find_package/mdsource/inc_conan_cmake_find_package_build.include.md

### Using Conan's cmake generator

**Note:** The files in this section can be viewed and downloaded from [conan_cmake](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/main/conan_cmake).

This example use Conan's [cmake](https://docs.conan.io/en/latest/integrations/build_system/cmake/cmake_generator.html) Generator.

The `conanfile.txt` file lists the required libraries, and which generator to use (here, `conan`):

include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/conan_cmake/mdsource/inc_conan_cmake_conanfile.include.md

The `conan` generator generates a `conanbuildinfo.cmake` file, which needs to used in the top-level CMakeLists.txt file like this:

include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/conan_cmake/mdsource/inc_conan_cmake_cmakelists.include.md

And the CMakeLists.txt that builds the tests is as follows (note the Conan-specific library target names):

include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/conan_cmake/mdsource/inc_conan_cmake_tests_cmakelists.include.md

Example set of build commands to download dependencies, make the test program and run the tests:

include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/conan_cmake/mdsource/inc_conan_cmake_build.include.md

### Making CMake invoke Conan

**Note:** The files in this section can be viewed and downloaded from [cmake_invoking_conan](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/main/cmake_invoking_conan).

This example use Conan's [cmake-conan](https://github.com/conan-io/cmake-conan) CMake module.

An advantage of this approach is that a project can use Conan to download dependencies, without people building that needing to know to run `conan install`. Anyone who is used to using CMake to generate builds will be able to build projects that use this mechanism. There will still need to be an installation of Conan on the build machine, however.

The `conanfile.txt` file lists the required libraries but does not say which generator to use:

include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/cmake_invoking_conan/mdsource/inc_cmake_invoking_conan_conanfile.include.md

There is a CMake file called `CMake/Conan.cmake` which contains instructions for downloading a specific version of the cmake-conan CMake module:

include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/cmake_invoking_conan/mdsource/inc_cmake_invoking_conan_CMake_conan.include.md

The top-level CMakeLists.txt file includes the above `CMake/Conan.cmake` file, and runs the macro that it contained:

include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/cmake_invoking_conan/mdsource/inc_cmake_invoking_conan_cmakelists.include.md

And the CMakeLists.txt that builds the tests is as follows (note the Conan-specific library target names):

include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/cmake_invoking_conan/mdsource/inc_cmake_invoking_conan_tests_cmakelists.include.md

Example set of build commands to download dependencies, make the test program and run the tests - note that there isno line to run conan:

include: https://raw.githubusercontent.com/claremacrae/ApprovalTests.cpp.CMakeSamples/main/cmake_invoking_conan/mdsource/inc_cmake_invoking_conan_build.include.md

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
