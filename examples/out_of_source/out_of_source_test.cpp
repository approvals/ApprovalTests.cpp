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

// Questions
// TODO How to set up a namer so that this passes both in CMake build AND when exes copied
// TODO Add a second test
// TODO TextDiffReporter is useless due to #106
// TODO Work out how to avoid TroubleshootingMisconfiguredBuild error if source code is not in original absolute path - see TestName::checkBuildConfiguration and TestName::getFileName()

// Commands used to test this:
/*
    cd /Users/clare/Documents/develop/ApprovalTests/ApprovalTests.cpp/cmake-build-spaces/cmake-build-debug-clang-mp-90
    mkdir -p clare_install
    DESTDIR=clare_install make install
    cd ./clare_install/usr/local/out_of_source
    APPROVAL_TESTS_USE_REPORTER=TextDiffReporter ./out_of_source
*/
