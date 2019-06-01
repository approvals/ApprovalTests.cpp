#include "gtest/gtest.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"

#define APPROVALS_GOOGLETEST_EXISTING_MAIN
#include "ApprovalTests/GoogleTestApprovals.h"

TEST(GoogleNamerCustomizations, EliminatesDuplicatedClassName)
{
    ApprovalTestNamer namer;
    EXPECT_EQ(namer.getOutputFileBaseName(), "testGoogleNamerCustomizations.EliminatesDuplicatedClassName");
}

class GoogleNamerCustomizationsFixture : public ::testing::Test{};

TEST_F(GoogleNamerCustomizationsFixture, EliminatesDuplicatedClassName)
{
//    auto expire = GoogleTestListener::addNameEquivalency(
//            [](std::string testFileNameWithoutExtension, std::string testCaseName)
//            {
//                return StringUtils::contains(testFileNameWithoutExtension+"Fixture",testCaseName);
//            });
    ApprovalTestNamer namer;
   // EXPECT_EQ(namer.getOutputFileBaseName(), "testGoogleNamerCustomizations.EliminatesDuplicatedClassName");
}