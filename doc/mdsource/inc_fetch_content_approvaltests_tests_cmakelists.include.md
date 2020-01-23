

```cmake
add_executable(tests
        main.cpp
        tests.cpp
)
target_link_libraries(tests ApprovalTests::ApprovalTests Catch2::Catch2)

target_compile_features(tests PUBLIC cxx_std_11)
set_target_properties(tests PROPERTIES CXX_EXTENSIONS OFF)

add_test(
        NAME tests
        COMMAND tests)
```
<sup><a href='https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/master/./fetch_content_approvaltests/tests/CMakeLists.txt' title='File snippet was copied from'>snippet source</a></sup>

