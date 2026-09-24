find_package(Python3 REQUIRED COMPONENTS Interpreter)

# Where TestTracking.h lives, and where the generated single header is written.
set(DOCTEST_SHARED_COMMON_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE INTERNAL "")
set(DOCTEST_SHARED_GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated" CACHE INTERNAL "")
set(Python3_EXECUTABLE "${Python3_EXECUTABLE}" CACHE INTERNAL "")

# Build the single header from the checked-in sources, without editing them.
file(GLOB_RECURSE approval_sources CONFIGURE_DEPENDS
        "${APPROVAL_TESTS_SOURCE_DIR}/ApprovalTests/*.h"
        "${APPROVAL_TESTS_SOURCE_DIR}/ApprovalTests/*.hpp"
        "${APPROVAL_TESTS_SOURCE_DIR}/ApprovalTests/*.cpp"
        "${APPROVAL_TESTS_SOURCE_DIR}/build/scripts/*.py")
set(generated_header "${DOCTEST_SHARED_GENERATED_DIR}/ApprovalTests.hpp")
add_custom_command(OUTPUT "${generated_header}"
        COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/generate_header.py"
                "${APPROVAL_TESTS_SOURCE_DIR}" "${DOCTEST_SHARED_GENERATED_DIR}"
        DEPENDS ${approval_sources} generate_header.py
        VERBATIM)
add_custom_target(doctest_shared_generate_single_header DEPENDS "${generated_header}")

# The static library is also linked into the Unix loadable modules.
set_target_properties(ApprovalTests PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Settings shared by the runner and every module. The provider decides how
# ApprovalTests reaches the target: single_header or static_library.
function(configure_doctest_target target provider)
    target_compile_features(${target} PRIVATE cxx_std_17)
    target_compile_definitions(${target} PRIVATE DOCTEST_CONFIG_IMPLEMENTATION_IN_DLL)
    target_include_directories(${target} PRIVATE "${DOCTEST_SHARED_COMMON_DIR}")
    target_link_libraries(${target} PRIVATE doctest::doctest)
    if (provider STREQUAL "single_header")
        target_include_directories(${target} PRIVATE "${DOCTEST_SHARED_GENERATED_DIR}")
        add_dependencies(${target} doctest_shared_generate_single_header)
    elseif (provider STREQUAL "static_library")
        target_link_libraries(${target} PRIVATE ApprovalTests::ApprovalTests)
    else ()
        message(FATAL_ERROR "Unknown ApprovalTests provider: ${provider}")
    endif ()
endfunction()

# A dynamically loaded library of tests that the runner opens with dlopen/LoadLibrary.
function(add_test_module target runner provider)
    if (WIN32)
        set(module_type SHARED)
    else ()
        set(module_type MODULE)
    endif ()
    add_library(${target} ${module_type} ${ARGN})
    set_target_properties(${target} PROPERTIES PREFIX "")
    if (APPLE)
        set_target_properties(${target} PROPERTIES SUFFIX ".dylib")
        target_link_options(${target} PRIVATE -undefined dynamic_lookup)
    elseif (WIN32)
        target_link_libraries(${target} PRIVATE ${runner})
    endif ()
    configure_doctest_target(${target} ${provider})
endfunction()
