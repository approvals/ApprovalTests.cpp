

```cmake
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
# This version is needed for FetchContent_Declare & FetchContent_MakeAvailable

project(fetch_content_approvaltests_catch2)

enable_testing()

add_subdirectory(dependencies)
add_subdirectory(tests)
```
<sup><a href='https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/master/./fetch_content_approvaltests_catch2/CMakeLists.txt' title='File snippet was copied from'>snippet source</a></sup>

