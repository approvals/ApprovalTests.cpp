// begin-snippet: show_deprecation_warnings
#define APPROVALS_SHOW_DEPRECATION_WARNINGS
// end-snippet

#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"

using namespace ApprovalTests;

TEST_CASE("TestStreamableObject")
{
    Approvals::verify(42);
}
