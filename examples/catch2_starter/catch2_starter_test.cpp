#include "catch2/catch.hpp"
#include "ApprovalTests.hpp"

using namespace ApprovalTests;

TEST_CASE("catch2_starter sample")
{
    Approvals::verify(42);
}
