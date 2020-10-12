#include "ApprovalTests/Approvals.h"

#include "CppUTest/TestHarness.h"

using namespace ApprovalTests;

TEST_GROUP(ApprovalTestsGroup){};

using namespace ApprovalTests;

TEST(ApprovalTestsGroup, YouCanVerifyText)
{
    Approvals::verify("My objects!");
}
