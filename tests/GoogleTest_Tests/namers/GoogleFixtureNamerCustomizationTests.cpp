#include "gtest/gtest.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"

#include "ApprovalTests/integrations/google/GoogleConfiguration.h"

// begin-snippet: googletest_customize_suffix
// main.cpp
auto customization =
    ApprovalTests::GoogleConfiguration::addIgnorableTestCaseNameSuffix("Fixture");
// end-snippet

// begin-snippet: googletest_name_parts
TEST(TestCaseName, TestName)
// end-snippet
{
    ApprovalTests::ApprovalTestNamer namer;
    EXPECT_EQ(namer.getOutputFileBaseName(),
              "GoogleFixtureNamerCustomizationTests.TestCaseName.TestName");
}

TEST(GoogleFixtureNamerCustomizationTests, EliminatesDuplicatedClassName)
{
    ApprovalTests::ApprovalTestNamer namer;
    EXPECT_EQ(namer.getOutputFileBaseName(),
              "GoogleFixtureNamerCustomizationTests.EliminatesDuplicatedClassName");
}

class GoogleFixtureNamerCustomizationTestsFixture : public ::testing::Test
{
};

TEST_F(GoogleFixtureNamerCustomizationTestsFixture, OnlyMatchesFixtureAtEnd)
{
    ApprovalTests::ApprovalTestNamer namer;
    EXPECT_EQ(namer.getOutputFileBaseName(),
              "GoogleFixtureNamerCustomizationTests.OnlyMatchesFixtureAtEnd");
}

// begin-snippet: googletest_customize_function
// main.cpp
bool dropTestCaseNamesWithIgnoreThis(const std::string& /*testFileNameWithExtension*/,
                                     const std::string& testCaseName)
{
    return ApprovalTests::StringUtils::contains(testCaseName, "IgnoreThis");
}

auto ignoreNames = ApprovalTests::GoogleConfiguration::addTestCaseNameRedundancyCheck(
    dropTestCaseNamesWithIgnoreThis);
// end-snippet

// begin-snippet: googletest_customize_lambda
// main.cpp
auto ignoreNamesLambda =
    ApprovalTests::GoogleConfiguration::addTestCaseNameRedundancyCheck(
        [](const std::string& /*testFileNameWithExtension*/,
           const std::string& testCaseName) {
            return ApprovalTests::StringUtils::contains(testCaseName, "IgnoreThis");
        });
// end-snippet

// begin-snippet: googletest_customize_test
TEST(TestCaseName_IgnoreThis, TestName)
// end-snippet
{
    ApprovalTests::ApprovalTestNamer namer;

    // begin-snippet: googletest_customize_test_name
    auto outputFileBaseName = "GoogleFixtureNamerCustomizationTests.TestName";
    // end-snippet

    EXPECT_EQ(namer.getOutputFileBaseName(), outputFileBaseName);
}
