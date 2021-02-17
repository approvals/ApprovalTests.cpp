if (NOT APPROVAL_TESTS_ENABLE_UT_INTEGRATION)
    return()
endif ()

if ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION GREATER_EQUAL 9.2) OR (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION GREATER_EQUAL 9.0))
    # TODO Work out how to negate this condition
ELSE()
    MESSAGE("The [Boost].UT integration with Approval Tests requires source_location support by the compiler, therefore it's disabled")
    return()
endif ()

# begin-snippet: ut_starter_cmake
set(EXE_NAME ut_starter)

set(CMAKE_CXX_STANDARD 20)
add_executable(${EXE_NAME}
        ut_starter_test.cpp
        )
target_link_libraries(${EXE_NAME} ApprovalTests::ApprovalTests boost.ut)

add_test(NAME ${EXE_NAME} COMMAND ${EXE_NAME})
# end-snippet
