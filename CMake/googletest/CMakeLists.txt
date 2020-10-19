if (NOT APPROVAL_TESTS_ENABLE_GOOGLETEST_INTEGRATION)
    return()
endif ()

if (NOT TARGET gtest_main)
    # Download and unpack googletest at configure time
    configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

    execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
            RESULT_VARIABLE result
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/googletest-download")

    if (result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif ()

    execute_process(COMMAND "${CMAKE_COMMAND}" --build .
            RESULT_VARIABLE result
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/googletest-download")

    if (result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif ()

    # Prevent GoogleTest from overriding our compiler/linker options
    # when building with Visual Studio
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This adds
    # the following targets: gtest, gtest_main, gmock
    # and gmock_main
    add_subdirectory("${CMAKE_CURRENT_BINARY_DIR}/googletest-src"
            "${CMAKE_CURRENT_BINARY_DIR}/googletest-build"
            EXCLUDE_FROM_ALL
            )
endif ()
