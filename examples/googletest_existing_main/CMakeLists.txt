project(googletest_existing_main)
set(CMAKE_CXX_STANDARD 11)
add_executable(${PROJECT_NAME}
        main.cpp
        GoogleTestApprovalsTests.cpp
        )
target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../ApprovalTests_GoogleTest_Tests)
target_link_libraries(${PROJECT_NAME} ApprovalTests gtest gtest_main)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
