#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"

TEST_CASE("VerifyingNoException")
{
    // begin-snippet: verify_exception_message_example
    ApprovalTests::Approvals::verifyExceptionMessage([]() { /* your code goes here */ });
    // end-snippet
}
