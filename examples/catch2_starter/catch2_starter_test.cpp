#include "catch2/catch.hpp"
#include "ApprovalTests/Approvals.h"

using namespace ApprovalTests;

TEST_CASE("catch2_starter sample")
{
    Approvals::verify(42);
}
