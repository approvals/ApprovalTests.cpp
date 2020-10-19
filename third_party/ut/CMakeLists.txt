if (NOT APPROVAL_TESTS_ENABLE_UT_INTEGRATION)
    return()
endif ()

if (NOT TARGET boost.ut)
    project(boost.ut CXX)
    set(CMAKE_CXX_STANDARD 17)
    add_library(${PROJECT_NAME} INTERFACE)
    target_include_directories(${PROJECT_NAME}
            INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

    if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        target_compile_options(boost.ut INTERFACE
                -Wno-c99-extensions # Suppress "designated initializers are a C99 feature"
                )
    endif ()

    # Mimic the library names in BOOST.ut's own CMake files:
    add_library(ut ALIAS boost.ut)
endif ()
