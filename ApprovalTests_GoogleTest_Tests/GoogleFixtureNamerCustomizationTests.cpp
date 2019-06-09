#include "gtest/gtest.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"

#include "ApprovalTests/integrations/google/GoogleConfiguration.h"

// startcode googletest_customize_suffix
// main.cpp
auto customization = GoogleConfiguration::addIgnorableTestCaseNameSuffix("Fixture");
// endcode

// startcode googletest_name_parts
TEST(TestCaseName, TestName)
// endcode
{
    ApprovalTestNamer namer;
    EXPECT_EQ(namer.getOutputFileBaseName(), "GoogleFixtureNamerCustomizationTests.TestCaseName.TestName");
}

TEST(GoogleFixtureNamerCustomizationTests, EliminatesDuplicatedClassName)
{
    ApprovalTestNamer namer;
    EXPECT_EQ(namer.getOutputFileBaseName(), "GoogleFixtureNamerCustomizationTests.EliminatesDuplicatedClassName");
}

class GoogleFixtureNamerCustomizationTestsFixture : public ::testing::Test{};

TEST_F(GoogleFixtureNamerCustomizationTestsFixture, OnlyMatchesFixtureAtEnd)
{
    ApprovalTestNamer namer;
    EXPECT_EQ(namer.getOutputFileBaseName(), "GoogleFixtureNamerCustomizationTests.OnlyMatchesFixtureAtEnd");
}

// startcode googletest_customize_function
// main.cpp
bool dropTestCaseNamesWithIgnoreThis(const std::string& /*testFileNameWithExtension*/, const std::string& testCaseName)
{
    return StringUtils::contains(testCaseName, "IgnoreThis");
}

auto ignoreNames = GoogleConfiguration::addTestCaseNameRedundancyCheck(dropTestCaseNamesWithIgnoreThis);
// endcode

// startcode googletest_customize_lambda
// main.cpp
auto ignoreNamesLambda = GoogleConfiguration::addTestCaseNameRedundancyCheck(
    [](const std::string& /*testFileNameWithExtension*/, const std::string& testCaseName)
    {
        return StringUtils::contains(testCaseName, "IgnoreThis");
    });
// endcode

// startcode googletest_customize_test
TEST(TestCaseName_IgnoreThis, TestName )
// endcode
{
    ApprovalTestNamer namer;

    // startcode googletest_customize_test_name
    auto outputFileBaseName = "GoogleFixtureNamerCustomizationTests.TestName";
    // endcode

    EXPECT_EQ(namer.getOutputFileBaseName(), outputFileBaseName);
}

