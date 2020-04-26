project(doctest_existing_main)
set(CMAKE_CXX_STANDARD 14)
add_executable(${PROJECT_NAME}
        main.cpp
        DeprecatedApprovalsTests.cpp
        DeprecatedCombinationApprovalsTests.cpp
        DoctestApprovalsTests.cpp
        )
target_link_libraries(${PROJECT_NAME} ApprovalTests::ApprovalTests doctest::doctest)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
