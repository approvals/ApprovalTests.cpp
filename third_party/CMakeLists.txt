if (APPROVAL_TESTS_BUILD_THIRD_PARTY_CATCH2)
    add_subdirectory(catch2)
    add_subdirectory(catch2v3_amalgamated)
endif ()

if (APPROVAL_TESTS_BUILD_THIRD_PARTY_DOCTEST)
    add_subdirectory(doctest)
endif ()

if (APPROVAL_TESTS_BUILD_THIRD_PARTY_UT)
    add_subdirectory(ut)
endif ()
