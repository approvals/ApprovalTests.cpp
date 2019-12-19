project(UT_Tests)
set(CMAKE_CXX_STANDARD 20)
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    MESSAGE("The [Boost].UT integration with Approval Tests requires source_location support by the compiler, therefore it's disabled")
else()
    add_executable(${PROJECT_NAME}
        ApprovalTestTests.cpp
        )
    target_link_libraries(${PROJECT_NAME} ApprovalTests ut)
    add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

    if(APPROVAL_TESTS_ENABLE_CODE_COVERAGE)
        setup_target_for_coverage_lcov(
                NAME ${PROJECT_NAME}_coverage
                EXECUTABLE ${PROJECT_NAME}
                DEPENDENCIES ${PROJECT_NAME})
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND CMAKE_CXX_SIMULATE_ID MATCHES "MSVC")
        target_compile_options(${PROJECT_NAME} PRIVATE
            /W4
            /WX
            )
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Werror
            )
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        target_compile_options(${PROJECT_NAME} PRIVATE
            /W4
            /WX
            )
    endif()
endif()