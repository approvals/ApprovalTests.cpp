if (APPROVAL_TESTS_BUILD_THIRD_PARTY_CATCH2)
    if (APPROVAL_TESTS_USE_CATCH2V3)
        message(STATUS "Add CPM.cmake")
        # download CPM.cmake
        file(
                DOWNLOAD
                https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.6/CPM.cmake
                ${CMAKE_BINARY_DIR}/cmake/CPM.cmake
                EXPECTED_HASH SHA256=11c3fa5f1ba14f15d31c2fb63dbc8628ee133d81c8d764caad9a8db9e0bacb07
        )
        include(${CMAKE_BINARY_DIR}/cmake/CPM.cmake)

        message(STATUS "Fetching external libraries started")

        message(STATUS "Fetching catch2")
        CPMAddPackage(
                NAME catch2
                GITHUB_REPOSITORY catchorg/Catch2
                GIT_TAG v3.5.0
        )
    else ()
        add_subdirectory(catch2v2)
    endif ()

endif ()

if (APPROVAL_TESTS_BUILD_THIRD_PARTY_DOCTEST)
    add_subdirectory(doctest)
endif ()

if (APPROVAL_TESTS_BUILD_THIRD_PARTY_UT)
    add_subdirectory(ut)
endif ()
