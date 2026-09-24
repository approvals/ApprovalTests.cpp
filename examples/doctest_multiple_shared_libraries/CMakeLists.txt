cmake_minimum_required(VERSION 3.13)
project(doctest_multiple_shared_libraries LANGUAGES CXX)

option(APPROVAL_TESTS_ENABLE_DOCTEST_INTEGRATION "Enable doctest integration" ON)
if (NOT APPROVAL_TESTS_ENABLE_DOCTEST_INTEGRATION)
    return()
endif ()

get_filename_component(APPROVAL_TESTS_SOURCE_DIR "../.." ABSOLUTE)
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    enable_testing()
    list(APPEND CMAKE_MODULE_PATH "${APPROVAL_TESTS_SOURCE_DIR}/CMake")
    add_subdirectory("${APPROVAL_TESTS_SOURCE_DIR}/ApprovalTests" ApprovalTests)
    add_subdirectory("${APPROVAL_TESTS_SOURCE_DIR}/third_party/doctest" doctest)
endif ()

# Helpers used by runner/ and module_*/
add_subdirectory(common)

# The runner is an executable that loads module_one and module_two at runtime.
# Every module and the runner get ApprovalTests in one of two ways, and each way
# is built and tested separately:
#   single_header  - #include the generated single ApprovalTests.hpp
#   static_library - link the ApprovalTests::ApprovalTests static library
foreach (provider IN ITEMS single_header static_library)
    set(APPROVALS_PROVIDER ${provider})
    set(variant doctest_shared_${provider})

    add_subdirectory(runner ${provider}/runner)
    add_subdirectory(module_one ${provider}/module_one)
    add_subdirectory(module_two ${provider}/module_two)

    add_dependencies(${variant}_runner ${variant}_module_one ${variant}_module_two)

    add_test(NAME ${variant} COMMAND ${variant}_runner
            "$<TARGET_FILE:${variant}_module_one>"
            "$<TARGET_FILE:${variant}_module_two>")
    add_test(NAME ${variant}_listeners
            COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/common/check_listeners.py"
                    "$<TARGET_FILE:${variant}_runner>"
                    "$<TARGET_FILE:${variant}_module_one>"
                    "$<TARGET_FILE:${variant}_module_two>")
    # Both providers write received files beside the same approved files.
    set_tests_properties(${variant} PROPERTIES RESOURCE_LOCK doctest_shared_approval_files)
endforeach ()
