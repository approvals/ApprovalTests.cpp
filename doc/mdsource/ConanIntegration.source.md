<a id="top"></a>

# Conan Integration

toc

## Using Conan to obtain ApprovalTests.cpp

Some examples of using the [Conan package manager](https://conan.io/):

* Daniel Heater's [ApprovalTests-ConanDemo repo](https://github.com/dheater/ApprovalTests-ConanDemo)
    * This demonstrates using ApprovalTests.cpp with Conan's `cmake` generator in a `conanfile.txt` file.
* p-podsiadly's 
[ImageApprovals](https://github.com/p-podsiadly/ImageApprovals)
    * This shows a different approach, using Conan's `cmake_find_package` generator from purely CMake code.
    * It's also a nice example of extending ApprovalTests.cpp to compare images.

## Links

* For users: [conan.io/center/approvaltests.cpp](https://conan.io/center/approvaltests.cpp/8.2.0/?user=_&channel=_)
* For maintainers: [the Conan recipe: approvaltests.cpp](https://github.com/conan-io/conan-center-index/tree/master/recipes/approvaltests.cpp)

---

[Back to User Guide](/doc/README.md#top)
