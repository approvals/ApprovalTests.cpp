#include "gtest/gtest.h"
#include <ApprovalTests/Approvals.h>

TEST(GoogleTestApprovalsTests, TestStreamableObject)
{
    Approvals::verify(42);
}
