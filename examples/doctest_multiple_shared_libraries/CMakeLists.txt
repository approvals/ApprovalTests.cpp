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

# A static ApprovalTests library is also linked into the Unix loadable modules.
set_target_properties(ApprovalTests PROPERTIES POSITION_INDEPENDENT_CODE ON)

function(add_shared_doctest_example variant)
    set(runner doctest_shared_${variant}_runner)
    add_executable(${runner} main.cpp)
    set_target_properties(${runner} PROPERTIES ENABLE_EXPORTS ON)
    if (WIN32)
        set(module_type SHARED)
    else ()
        set(module_type MODULE)
    endif ()
    foreach(module IN ITEMS One Two)
        set(target doctest_shared_${variant}_${module})
        add_library(${target} ${module_type} Module${module}.cpp)
        set_target_properties(${target} PROPERTIES PREFIX "")
        if (APPLE)
            set_target_properties(${target} PROPERTIES SUFFIX ".dylib")
            target_link_options(${target} PRIVATE -undefined dynamic_lookup)
        elseif (WIN32)
            target_link_libraries(${target} PRIVATE ${runner})
        endif ()
        add_dependencies(${runner} ${target})
    endforeach()

    target_sources(doctest_shared_${variant}_One PRIVATE ModuleOneExtra.cpp)
    # Keep implementation and declaration-only includes in separate translation units.
    set_target_properties(doctest_shared_${variant}_One PROPERTIES UNITY_BUILD OFF)

    foreach(target IN ITEMS ${runner} doctest_shared_${variant}_One doctest_shared_${variant}_Two)
        target_compile_features(${target} PRIVATE cxx_std_17)
        target_compile_definitions(${target} PRIVATE DOCTEST_CONFIG_IMPLEMENTATION_IN_DLL)
        target_link_libraries(${target} PRIVATE doctest::doctest)
        if (variant STREQUAL "header")
            target_include_directories(${target} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/generated")
            add_dependencies(${target} doctest_shared_header)
        else ()
            target_link_libraries(${target} PRIVATE ApprovalTests::ApprovalTests)
        endif ()
    endforeach()
    target_link_libraries(${runner} PRIVATE ${CMAKE_DL_LIBS})
    add_test(NAME doctest_shared_${variant} COMMAND ${runner}
            "$<TARGET_FILE:doctest_shared_${variant}_One>"
            "$<TARGET_FILE:doctest_shared_${variant}_Two>")
    add_test(NAME doctest_shared_${variant}_listeners
            COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/check_listeners.py"
                    "$<TARGET_FILE:${runner}>"
                    "$<TARGET_FILE:doctest_shared_${variant}_One>"
                    "$<TARGET_FILE:doctest_shared_${variant}_Two>")
    # Both variants write received files beside the same approved files.
    set_tests_properties(doctest_shared_${variant} PROPERTIES
            RESOURCE_LOCK doctest_shared_approval_files)
endfunction()

add_shared_doctest_example(header)
add_shared_doctest_example(source)
