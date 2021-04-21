#include "doctest/doctest.h"
#include "ApprovalTests.hpp"

#include <iostream>

using namespace ApprovalTests;

TEST_CASE("out_of_source sample")
{
    std::string approved = Approvals::getDefaultNamer()->getApprovedFile(".txt");
    std::cout << "Approved filename = " << approved << std::endl;
    Approvals::verify(42);
}

// Commands used to test this:
/*
    cd /Users/clare/Documents/develop/ApprovalTests/ApprovalTests.cpp/cmake-build-spaces/cmake-build-debug-clang-mp-90
    mkdir -p clare_install
    DESTDIR=clare_install make install
    cd ./clare_install/usr/local/out_of_source
    APPROVAL_TESTS_USE_REPORTER=TextDiffReporter ./out_of_source
*/
