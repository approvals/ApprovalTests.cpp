#include "gtest/gtest.h"
#include "ApprovalTests/Approvals.h"

using namespace ApprovalTests;

TEST(GoogleTestApprovalsTests, YouCanVerifyText)
{
    //std::cout << __FILE__ << std::endl;
    Approvals::verify("My objects!");
}

TEST(GoogleTestApprovalsTests, TestStreamableObject)
{
    Approvals::verify(42);
}
