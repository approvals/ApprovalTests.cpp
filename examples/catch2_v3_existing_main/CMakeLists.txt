if (NOT APPROVAL_TESTS_ENABLE_CATCH2V3_INTEGRATION)
    return()
endif ()

project(catch2_v3_existing_main)
set(CMAKE_CXX_STANDARD 14)
add_executable(${PROJECT_NAME}
        main.cpp
        Catch2ApprovalsTests.cpp
        )
target_link_libraries(${PROJECT_NAME} ApprovalTests::ApprovalTests Catch2::Catch2)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
