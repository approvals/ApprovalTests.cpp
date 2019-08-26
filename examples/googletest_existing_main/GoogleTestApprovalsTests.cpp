#include "gtest/gtest.h"
#include "ApprovalTests/Approvals.h"
#include "Approvals.h"

TEST(GoogleTestApprovalsTests, TestStreamableObject)
{
    ApprovalTests::Approvals::verify(42);
}

TEST(GoogleTestApprovalsTests, SpecificReporter)
{
    // begin-snippet: basic_approval_with_reporter
    ApprovalTests::Approvals::verify("text to be verified", Windows::AraxisMergeReporter());
    // end-snippet
}
