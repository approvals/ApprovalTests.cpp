<a id="top"></a>

# How to Install ApprovalTests Using CMake

<!-- toc -->
## Contents

  * [Audience](#audience)
  * [Why](#why)
  * [Example](#example)<!-- endToc -->

## Audience

This page is aimed at developers who understand CMake's feature to build against libraries that were installed in a standard location.

## Why

If you wish to create a pre-built copy of Approval Tests, for example installed as a system library on your machine, or in a user-owned directory, you can use CMake's Install mechanism.

This copies a statically-compiled library and all the ApprovalTests headers to a central location, or to your chosen location, if you use `-DCMAKE_INSTALL_PREFIX`.

## Example

Here is an example of building and installing the ApprovalTests library and include files.

```bash
cd ApprovalTests.cpp
mkdir -p build && cd build
cmake \
    -DAPPROVAL_TESTS_BUILD_TESTING=OFF \
    -DAPPROVAL_TESTS_BUILD_EXAMPLES=OFF \
    -DAPPROVAL_TESTS_BUILD_DOCS=OFF \
    -DAPPROVAL_TESTS_BUILD_THIRD_PARTY_CATCH2=OFF \
    -DAPPROVAL_TESTS_BUILD_THIRD_PARTY_DOCTEST=OFF \
    -DAPPROVAL_TESTS_BUILD_THIRD_PARTY_UT=OFF \
    -DAPPROVAL_TESTS_ENABLE_BOOST_TEST_INTEGRATION=OFF \
    -DAPPROVAL_TESTS_ENABLE_CATCH2_INTEGRATION=OFF \
    -DAPPROVAL_TESTS_ENABLE_CPPUTEST_INTEGRATION=OFF \
    -DAPPROVAL_TESTS_ENABLE_DOCTEST_INTEGRATION=OFF \
    -DAPPROVAL_TESTS_ENABLE_GOOGLETEST_INTEGRATION=OFF \
    -DAPPROVAL_TESTS_ENABLE_UT_INTEGRATION=OFF \
    ..
cmake --build   . --parallel 8
cmake --install .
```

---

[Back to User Guide](/doc/README.md#top)
