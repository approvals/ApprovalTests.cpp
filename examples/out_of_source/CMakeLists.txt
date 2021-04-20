if (NOT APPROVAL_TESTS_ENABLE_DOCTEST_INTEGRATION)
    return()
endif ()

# begin-snippet: out_of_source_cmake
set(EXE_NAME out_of_source)
set(CMAKE_CXX_STANDARD 11)
add_executable(${EXE_NAME}
        out_of_source_main.cpp
        out_of_source_test.cpp
        DocTestReporter.cpp
        DocTestReporter.h
        )
target_link_libraries(${EXE_NAME} ApprovalTests::ApprovalTests doctest::doctest)

add_test(NAME ${EXE_NAME} COMMAND ${EXE_NAME})
# end-snippet

install(TARGETS ${EXE_NAME} DESTINATION ${EXE_NAME})
# Copy all approved files
file(GLOB_RECURSE APPROVED_FILES_TO_INSTALL ${CMAKE_CURRENT_SOURCE_DIR} "*.approved.*")
install(FILES ${APPROVED_FILES_TO_INSTALL} DESTINATION ${EXE_NAME})
