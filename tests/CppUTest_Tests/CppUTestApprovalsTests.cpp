#include "ApprovalTests/Approvals.h"

#include "CppUTest/TestHarness.h"

using namespace ApprovalTests;

TEST_GROUP(ApprovalTestsGroup){};

using namespace ApprovalTests;

TEST(ApprovalTestsGroup, YouCanVerifyText)
{
    //std::cout << __FILE__ << std::endl;
    Approvals::verify("My objects!");
}

TEST(ApprovalTestsGroup, TestStreamableObject)
{
    Approvals::verify(42);
}
