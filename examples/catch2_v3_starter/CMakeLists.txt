if (NOT APPROVAL_TESTS_ENABLE_CATCH2V3_INTEGRATION)
    return()
endif ()

# begin-snippet: catch2_v3_starter_cmake
set(EXE_NAME catch2_v3_starter)
set(CMAKE_CXX_STANDARD 14)
add_executable(${EXE_NAME}
        catch2_v3_starter_main.cpp
        catch2_v3_starter_test.cpp
        )
target_link_libraries(${EXE_NAME} ApprovalTests::ApprovalTests Catch2::Catch2WithMain)

add_test(NAME ${EXE_NAME} COMMAND ${EXE_NAME})
# end-snippet
