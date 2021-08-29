// begin-snippet: show_deprecation_warnings
#define APPROVAL_TESTS_SHOW_DEPRECATION_WARNINGS 1
// end-snippet

// begin-snippet: hide_deprecated_code
#define APPROVAL_TESTS_HIDE_DEPRECATED_CODE 1
// end-snippet

#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"

TEST_CASE("TestStreamableObject")
{
    ApprovalTests::Approvals::verify(42);
}
