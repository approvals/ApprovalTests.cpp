

```cmake
# -------------------------------------------------------------------
# ApprovalTests.cpp
add_subdirectory(
        ../../ApprovalTests.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/approvaltests.cpp_build
)

# -------------------------------------------------------------------
# Catch2
set(CATCH_BUILD_TESTING OFF CACHE BOOL "")
add_subdirectory(
        ../../Catch2
        ${CMAKE_CURRENT_BINARY_DIR}/catch2_build
)
```

