#include "doctest/doctest.h"
#include "ApprovalTests.hpp"

using namespace ApprovalTests;

TEST_CASE("out_of_source sample")
{
    Approvals::verify(42);
}
