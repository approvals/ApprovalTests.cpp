#include "gtest/gtest.h"
#include "ApprovalTests/Approvals.h"

TEST(GoogleTestApprovalsTests, TestStreamableObject)
{
    Approvals::verify(42);
}

TEST(GoogleTestApprovalsTests, SpecificReporter)
{
    // startcode basic_approval_with_reporter
    Approvals::verify("text to be verified", Windows::AraxisMergeReporter());
    // endcode
}
