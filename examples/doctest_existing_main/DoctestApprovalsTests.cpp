#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"

using namespace ApprovalTests;

TEST_CASE("TestStreamableObject")
{
    Approvals::verify(42);
}
