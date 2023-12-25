if (NOT APPROVAL_TESTS_ENABLE_CATCH2_INTEGRATION)
    return()
endif ()

if(NOT APPROVAL_TESTS_USE_CATCH2V3)
    return()
endif()

# begin-snippet: catch2_starter_cmake
set(EXE_NAME catch2_v3_starter)
set(CMAKE_CXX_STANDARD 11)
add_executable(${EXE_NAME}
        catch2_starter_main.cpp
        catch2_starter_test.cpp
        )
target_link_libraries(${EXE_NAME} ApprovalTests::ApprovalTests Catch2::Catch2WithMain)

add_test(NAME ${EXE_NAME} COMMAND ${EXE_NAME})
# end-snippet
