add_executable(cmake_fetch_content_approvaltests_tests
        main.cpp
        tests.cpp
)
target_link_libraries(cmake_fetch_content_approvaltests_tests ApprovalTests::ApprovalTests Catch2::Catch2)
