#include "gtest/gtest.h"
#include "ApprovalTests/Approvals.h"

TEST(GoogleTestApprovalsTests, TestStreamableObject)
{
    Approvals::verify(42);
}

TEST(GoogleTestApprovalsTests, SpecificReporter)
{
    // begin-snippet: basic_approval_with_reporter
    Approvals::verify("text to be verified", Windows::AraxisMergeReporter());
    // end-snippet
}
