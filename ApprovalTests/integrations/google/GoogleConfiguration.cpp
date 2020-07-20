#include "ApprovalTests/integrations/google/GoogleConfiguration.h"

namespace ApprovalTests
{
    bool GoogleConfiguration::addTestCaseNameRedundancyCheck(
        GoogleCustomizationsFactory::Comparator comparator)
    {
        return GoogleCustomizationsFactory::addTestCaseNameRedundancyCheck(comparator);
    }

    bool GoogleConfiguration::addIgnorableTestCaseNameSuffix(std::string suffix)
    {
        return addTestCaseNameRedundancyCheck(
            createIgnorableTestCaseNameSuffixCheck(suffix));
    }

    GoogleCustomizationsFactory::Comparator
    GoogleConfiguration::createIgnorableTestCaseNameSuffixCheck(const std::string& suffix)
    {
        return [suffix](std::string testFileNameWithExtension, std::string testCaseName) {
            if (testCaseName.length() <= suffix.length() ||
                !StringUtils::endsWith(testCaseName, suffix))
            {
                return false;
            }

            auto withoutSuffix =
                testCaseName.substr(0, testCaseName.length() - suffix.length());
            auto withFileExtension = withoutSuffix + ".";
            return StringUtils::contains(testFileNameWithExtension, withFileExtension);
        };
    }
}
