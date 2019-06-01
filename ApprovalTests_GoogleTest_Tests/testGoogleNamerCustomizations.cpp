#include "gtest/gtest.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"

#include "ApprovalTests/integrations/google/GoogleCustomizationsFactory.h"


auto expired = GoogleCustomizationsFactory::addEquivalencyCheck(
    [](std::string testFileNameWithExtension, std::string testCaseName)
    {
        // The dot is used to make sure that we only match when Fixture appears at the end of the file name
        auto modifiedTestCaseName = StringUtils::replaceAll(testCaseName, "Fixture", ".");
        return StringUtils::contains(testFileNameWithExtension, modifiedTestCaseName);
    });


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
