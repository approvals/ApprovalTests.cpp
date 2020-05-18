cmake_minimum_required(VERSION 3.8)

# Download and unpack fmt at configure time
configure_file(CMakeLists.txt.in fmt-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/fmt-download)

if (result)
    message(FATAL_ERROR "CMake step for fmt failed: ${result}")
endif ()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/fmt-download)

if (result)
    message(FATAL_ERROR "Build step for fmt failed: ${result}")
endif ()

# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add fmt directly to our build. This defines the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/fmt-src
        ${CMAKE_CURRENT_BINARY_DIR}/fmt-build
        EXCLUDE_FROM_ALL
        )