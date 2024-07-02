if (NOT APPROVAL_TESTS_ENABLE_CATCH2V3_INTEGRATION)
    return()
endif ()

# begin-snippet: catch2_v3_amalgamated_starter_cmake
set(EXE_NAME catch2_v3_amalgamated_starter)
set(CMAKE_CXX_STANDARD 17)
add_executable(${EXE_NAME}
        catch2_v3_amalgamated_starter_main.cpp
        catch2_v3_amalgamated_starter_test.cpp
        )
target_link_libraries(${EXE_NAME} ApprovalTests::ApprovalTests Catch2v2_Amalgamated)

add_test(NAME ${EXE_NAME} COMMAND ${EXE_NAME})
# end-snippet
