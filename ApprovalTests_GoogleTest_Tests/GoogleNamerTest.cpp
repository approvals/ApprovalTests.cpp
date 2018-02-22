#include "gtest/gtest.h"
#include "../ApprovalTests/Namers/ApprovalNamer.h"

TEST(GoogleNamerTest, ItDropsFirstNameWhenItEqualsTheFilename)
{
    ApprovalNamer namer;
    EXPECT_EQ(namer.getTestName(), "ItDropsFirstNameWhenItEqualsTheFilename");
}

TEST(TestCaseNameDifferentNameThanFile, TestName)
{
    ApprovalNamer namer;
    EXPECT_EQ(namer.getTestName(), "TestCaseNameDifferentNameThanFile.TestName");
}

// Adding support for invalid but possible code (missing 2nd macro parameter)
TEST(TestCaseNameDifferentNameThanFile)
{
    ApprovalNamer namer;
    EXPECT_EQ(namer.getTestName(), "TestCaseNameDifferentNameThanFile");
}

// Adding support for invalid but possible code (missing 2nd macro parameter)
TEST(GoogleNamerTest)
{
    ApprovalNamer namer;
    EXPECT_EQ(namer.getTestName(), "");
}
