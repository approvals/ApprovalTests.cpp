// begin-snippet: show_deprecation_warnings
#define APPROVAL_TESTS_SHOW_DEPRECATION_WARNINGS
// end-snippet

// begin-snippet: hide_deprecated_code
#define APPROVAL_TESTS_HIDE_DEPRECATED_CODE
// end-snippet

#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"

using namespace ApprovalTests;

TEST_CASE("TestStreamableObject")
{
    Approvals::verify(42);
}
