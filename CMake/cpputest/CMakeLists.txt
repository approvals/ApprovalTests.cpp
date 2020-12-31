if (NOT APPROVAL_TESTS_ENABLE_CPPUTEST_INTEGRATION)
    return()
endif ()

if (NOT TARGET cpputest)
    cmake_minimum_required(VERSION 3.8)

    # Download and unpack cpputest at configure time
    configure_file(CMakeLists.txt.in cpputest-download/CMakeLists.txt)

    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/cpputest-download)

    if (result)
        message(FATAL_ERROR "CMake step for cpputest failed: ${result}")
    endif ()

    execute_process(COMMAND ${CMAKE_COMMAND} --build .
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/cpputest-download)

    if (result)
        message(FATAL_ERROR "Build step for cpputest failed: ${result}")
    endif ()

    # Prevent CppUTest creating cluttering up CLion with nearly 30 CTest targets
    # (Continuous, ContinuousBuild etc) when it does:
    #   include(CTest)
    # This hack taken from https://stackoverflow.com/a/57240389/104370
    set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1) # hack to prevent CTest added targets

    # Prevent CppUTest's own tests from being built
    set(TESTS OFF CACHE BOOL "")

    # Prevent build of CppUTest from generating thousands of lines of
    # -Wc++98-compat and -Wc++98-compat-pedantic warnings:
    set(C++11 ON CACHE BOOL "Compile with C++11 support")

    # Add cpputest directly to our build. This defines the cpputest target.
    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/cpputest-src
            ${CMAKE_CURRENT_BINARY_DIR}/cpputest-build
            EXCLUDE_FROM_ALL
            )
endif ()
