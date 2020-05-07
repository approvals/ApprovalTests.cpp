#include "gtest/gtest.h"
#include "ApprovalTests/Approvals.h"

using namespace ApprovalTests;

TEST(GoogleTestApprovalsTests, TestStreamableObject)
{
    Approvals::verify(42);
}

TEST(GoogleTestApprovalsTests, SpecificReporter)
{
    // begin-snippet: basic_approval_with_reporter
    Approvals::verify("text to be verified", Options(Windows::AraxisMergeReporter()));
    // end-snippet
}

TEST(GoogleTestApprovalsTests, SpecificReporter2)
{
    // begin-snippet: basic_approval_with_reporter_2
    Approvals::verify("text to be verified",
                      Options().withReporter(Mac::AraxisMergeReporter()));
    // end-snippet
}
