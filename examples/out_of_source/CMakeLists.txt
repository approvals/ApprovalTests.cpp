if (NOT APPROVAL_TESTS_ENABLE_DOCTEST_INTEGRATION)
    return()
endif ()

# begin-snippet: out_of_source_cmake
set(EXE_NAME out_of_source)
add_executable(${EXE_NAME}
        out_of_source_main.cpp
        out_of_source_test.cpp
        DocTestReporter.cpp
        DocTestReporter.h
        )
target_link_libraries(${EXE_NAME} ApprovalTests::ApprovalTests doctest::doctest ghc_filesystem)
set_target_properties(${EXE_NAME} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON)

add_test(NAME ${EXE_NAME} COMMAND ${EXE_NAME})
# end-snippet

install(TARGETS ${EXE_NAME} DESTINATION ${EXE_NAME})
# Copy all approved files
# TODO Remove the manual list
install(FILES out_of_source_test.out_of_source_sample.approved.txt
        DESTINATION ${EXE_NAME}
        )
install(FILES approval_tests/out_of_source_test.out_of_source_approvals_sub-directory_sample.approved.txt
        DESTINATION ${EXE_NAME}/approval_tests/
        )
