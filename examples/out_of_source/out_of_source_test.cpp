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
