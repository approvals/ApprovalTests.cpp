if (NOT APPROVAL_TESTS_ENABLE_DOCTEST_INTEGRATION)
    return()
endif ()

if (NOT TARGET doctest)
    project(doctest CXX)
    set(CMAKE_CXX_STANDARD 11)
    add_library(${PROJECT_NAME} INTERFACE)
    target_include_directories(${PROJECT_NAME}
            INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

    # Mimic the library names in doctest's own CMake files:
    add_library(doctest::doctest ALIAS doctest)
endif ()
