cmake_minimum_required(VERSION 3.13)
project(doctest_multiple_shared_libraries LANGUAGES CXX)

option(APPROVAL_TESTS_ENABLE_DOCTEST_INTEGRATION "Enable doctest integration" ON)
if (NOT APPROVAL_TESTS_ENABLE_DOCTEST_INTEGRATION)
    return()
endif ()

get_filename_component(APPROVAL_TESTS_SOURCE_DIR "../.." ABSOLUTE)
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    enable_testing()
    add_subdirectory("${APPROVAL_TESTS_SOURCE_DIR}/third_party/doctest" doctest)
endif ()

find_package(Python3 REQUIRED COMPONENTS Interpreter)
file(GLOB_RECURSE approval_sources CONFIGURE_DEPENDS
        "${APPROVAL_TESTS_SOURCE_DIR}/ApprovalTests/*.h"
        "${APPROVAL_TESTS_SOURCE_DIR}/ApprovalTests/*.hpp"
        "${APPROVAL_TESTS_SOURCE_DIR}/ApprovalTests/*.cpp"
        "${APPROVAL_TESTS_SOURCE_DIR}/build/scripts/*.py")
set(generated_header "${CMAKE_CURRENT_BINARY_DIR}/generated/ApprovalTests.hpp")
add_custom_command(OUTPUT "${generated_header}"
        COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/generate_header.py"
                "${APPROVAL_TESTS_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/generated"
        DEPENDS ${approval_sources} generate_header.py
        VERBATIM)
add_custom_target(doctest_shared_header DEPENDS "${generated_header}")

add_executable(doctest_shared_runner main.cpp)
set_target_properties(doctest_shared_runner PROPERTIES ENABLE_EXPORTS ON)
if (WIN32)
    set(module_type SHARED)
else ()
    set(module_type MODULE)
endif ()
foreach(module IN ITEMS One Two)
    add_library(doctest_shared_${module} ${module_type} Module${module}.cpp)
    set_target_properties(doctest_shared_${module} PROPERTIES PREFIX "")
    if (APPLE)
        set_target_properties(doctest_shared_${module} PROPERTIES SUFFIX ".dylib")
        target_link_options(doctest_shared_${module} PRIVATE -undefined dynamic_lookup)
    elseif (WIN32)
        target_link_libraries(doctest_shared_${module} PRIVATE doctest_shared_runner)
    endif ()
    add_dependencies(doctest_shared_runner doctest_shared_${module})
endforeach()

foreach(target IN ITEMS doctest_shared_runner doctest_shared_One doctest_shared_Two)
    target_compile_features(${target} PRIVATE cxx_std_17)
    target_compile_definitions(${target} PRIVATE DOCTEST_CONFIG_IMPLEMENTATION_IN_DLL)
    target_include_directories(${target} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/generated")
    target_link_libraries(${target} PRIVATE doctest::doctest)
    add_dependencies(${target} doctest_shared_header)
endforeach()
target_link_libraries(doctest_shared_runner PRIVATE ${CMAKE_DL_LIBS})
add_test(NAME doctest_multiple_shared_libraries COMMAND doctest_shared_runner
        "$<TARGET_FILE:doctest_shared_One>" "$<TARGET_FILE:doctest_shared_Two>")
