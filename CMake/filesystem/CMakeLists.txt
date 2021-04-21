# TODO Add option
#if (NOT APPROVAL_TESTS_ENABLE_GHC_FILESYSTEM_INTEGRATION)
#    return()
#endif ()

if (TARGET ghc_filesystem)
    return()
endif ()

# Needs CMake 3.14 or above
include(FetchContent)

FetchContent_Declare(filesystem
        GIT_REPOSITORY https://github.com/gulrak/filesystem.git
        GIT_TAG v1.5.4)
FetchContent_MakeAvailable(filesystem)
