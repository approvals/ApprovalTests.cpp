#include "gtest/gtest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/reporters/WindowsReporters.h"
#include "ApprovalTests/reporters/MacReporters.h"

TEST(GoogleTestApprovalsTests, TestStreamableObject)
{
    ApprovalTests::Approvals::verify(42);
}

TEST(GoogleTestApprovalsTests, SpecificReporter)
{
    // begin-snippet: basic_approval_with_reporter
    using namespace ApprovalTests;
    Approvals::verify("text to be verified", Options(Windows::AraxisMergeReporter()));
    // end-snippet
}

TEST(GoogleTestApprovalsTests, SpecificReporter2)
{
    // begin-snippet: basic_approval_with_reporter_2
    using namespace ApprovalTests;
    Approvals::verify("text to be verified",
                      Options().withReporter(Mac::AraxisMergeReporter()));
    // end-snippet
}
