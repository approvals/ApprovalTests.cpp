#include "gtest/gtest.h"
#include "../ApprovalTests/namers/ApprovalTestNamer.h"

TEST(GoogleNamerTest, ItDropsFirstNameWhenItEqualsTheFilename)
{
    ApprovalTestNamer namer;
    EXPECT_EQ(namer.getTestName(), "ItDropsFirstNameWhenItEqualsTheFilename");
}

TEST(TestCaseNameDifferentNameThanFile, TestName)
{
    ApprovalTestNamer namer;
    EXPECT_EQ(namer.getTestName(), "TestCaseNameDifferentNameThanFile.TestName");
}
