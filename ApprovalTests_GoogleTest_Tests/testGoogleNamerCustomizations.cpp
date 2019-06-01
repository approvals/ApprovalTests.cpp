#include "gtest/gtest.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"

#include "ApprovalTests/integrations/google/GoogleCustomizationsFactory.h"

// startcode googletest_customize_suffix
// main.cpp
auto customization = GoogleCustomizationsFactory::addTestCaseNameSuffix("Fixture");
// endcode

// startcode googletest_name_parts
TEST(test_case_name, test_name)
// endcode
{
    ApprovalTestNamer namer;
    EXPECT_EQ(namer.getOutputFileBaseName(), "testGoogleNamerCustomizations.test_case_name.test_name");
}

TEST(GoogleNamerCustomizations, EliminatesDuplicatedClassName)
{
    ApprovalTestNamer namer;
    EXPECT_EQ(namer.getOutputFileBaseName(), "testGoogleNamerCustomizations.EliminatesDuplicatedClassName");
}

class GoogleNamerCustomizationsFixture : public ::testing::Test{};

TEST_F(GoogleNamerCustomizationsFixture, EliminatesDuplicatedClassName)
{
    ApprovalTestNamer namer;
    EXPECT_EQ(namer.getOutputFileBaseName(), "testGoogleNamerCustomizations.EliminatesDuplicatedClassName");
}
