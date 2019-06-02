#ifndef APPROVALTESTS_CPP_GOOGLECONFIGURATION_H
#define APPROVALTESTS_CPP_GOOGLECONFIGURATION_H

#include "GoogleCustomizationsFactory.h"
#include <regex>

class GoogleConfiguration
{
public:
    static bool addTestCaseNameRedundancyCheck(GoogleCustomizationsFactory::Comparator comparator)
    {
        return GoogleCustomizationsFactory::addTestCaseNameRedundancyCheck(comparator);
    }

    static bool addIgnorableTestCaseNameSuffix(std::string suffix)
    {
        auto customization = addTestCaseNameRedundancyCheck(
            [suffix](std::string testFileNameWithExtension, std::string testCaseName)
            {
                std::regex endOfStringRegex(suffix + "$");
                // The dot is used to make sure that we only match when Fixture appears at the end of the file name
                auto modifiedTestCaseName = std::regex_replace(testCaseName, endOfStringRegex, ".");
                return StringUtils::contains(testFileNameWithExtension, modifiedTestCaseName);
            });
        return customization;
    }
};

#endif //APPROVALTESTS_CPP_GOOGLECONFIGURATION_H
