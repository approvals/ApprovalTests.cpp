#include "gtest/gtest.h"
#include "ApprovalTests/Approvals.h"
#include "Approvals.h"

TEST(GoogleTestApprovalsTests, YouCanVerifyText)
{
    //std::cout << __FILE__ << std::endl;
    ApprovalTests::Approvals::verify("My objects!");
}

TEST(GoogleTestApprovalsTests, TestStreamableObject)
{
    ApprovalTests::Approvals::verify(42);
}
