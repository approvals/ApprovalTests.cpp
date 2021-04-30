#include "doctest/doctest.h"
#include "ApprovalTests.hpp"

#include <iostream>

using namespace ApprovalTests;

TEST_CASE("source_sub_dir_tests sample")
{
    std::string approved = Approvals::getDefaultNamer()->getApprovedFile(".txt");
    std::cout << "Approved filename = " << approved << std::endl;
    Approvals::verify(42);
}
