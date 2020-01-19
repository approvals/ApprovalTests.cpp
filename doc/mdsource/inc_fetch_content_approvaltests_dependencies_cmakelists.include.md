

```cmake
include(FetchContent)

# -------------------------------------------------------------------
# ApprovalTests.cpp
FetchContent_Declare(ApprovalTests
        GIT_REPOSITORY https://github.com/approvals/ApprovalTests.cpp.git
        GIT_TAG cmake_docs) # TODO Merge cmake_docs to default - then change this to master

# Tell the ApprovalTests CMake files that we want to use its copy of Catch2:
set(APPROVAL_TESTS_BUILD_THIRD_PARTY_CATCH2 ON CACHE BOOL "")

# These are also available:
#    set(APPROVAL_TESTS_BUILD_THIRD_PARTY_DOCTEST ON CACHE BOOL "")
#    set(APPROVAL_TESTS_BUILD_THIRD_PARTY_UT ON CACHE BOOL "")

FetchContent_MakeAvailable(ApprovalTests)
```

