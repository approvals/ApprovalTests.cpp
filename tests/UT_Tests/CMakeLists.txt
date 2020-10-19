if (NOT APPROVAL_TESTS_ENABLE_UT_INTEGRATION)
    return()
endif ()

project(UT_Tests)
if ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION GREATER_EQUAL 9.2) OR (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION GREATER_EQUAL 9.0))
    set(CMAKE_CXX_STANDARD 20)
    add_executable(${PROJECT_NAME}
            UTApprovalTestTests.cpp
            )
    target_link_libraries(${PROJECT_NAME} ApprovalTests::ApprovalTests boost.ut)
    add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

    if (APPROVAL_TESTS_ENABLE_CODE_COVERAGE)
        setup_target_for_coverage_lcov(
                NAME ${PROJECT_NAME}_coverage
                EXECUTABLE ${PROJECT_NAME}
                DEPENDENCIES ${PROJECT_NAME})
    endif ()

    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND CMAKE_CXX_SIMULATE_ID MATCHES "MSVC")
        target_compile_options(${PROJECT_NAME} PRIVATE
                /W4
                /WX
                )
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE
                -Wall
                -Wextra
                -Wpedantic
                -Werror
                )
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        target_compile_options(${PROJECT_NAME} PRIVATE
                /W4
                /WX
                )
    endif ()
else ()
    MESSAGE("The [Boost].UT integration with Approval Tests requires source_location support by the compiler, therefore it's disabled")
endif ()