add_executable(cmake_fetch_content_approvaltests_tests
        main.cpp
        tests.cpp
)
target_link_libraries(cmake_fetch_content_approvaltests_tests ApprovalTests::ApprovalTests Catch2::Catch2)

set_target_properties(cmake_fetch_content_approvaltests_tests PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

add_test(
        NAME cmake_fetch_content_approvaltests_tests
        COMMAND cmake_fetch_content_approvaltests_tests)