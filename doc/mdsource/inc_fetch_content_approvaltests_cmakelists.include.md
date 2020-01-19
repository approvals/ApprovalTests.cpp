

```cmake
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
# This version is needed for FetchContent_Declare & FetchContent_MakeAvailable

project(fetch_content_approvaltests)

enable_testing()

add_subdirectory(dependencies)
add_subdirectory(tests)
```

