#ifndef APPROVALTESTS_CPP_GOOGLECONFIGURATION_H
#define APPROVALTESTS_CPP_GOOGLECONFIGURATION_H

#include "GoogleCustomizationsFactory.h" 

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
                // The dot is used to make sure that we only match when Fixture appears at the end of the file name
                auto modifiedTestCaseName = StringUtils::replaceAll(testCaseName, suffix, ".");
                return StringUtils::contains(testFileNameWithExtension, modifiedTestCaseName);
            });
        return customization;
    }
};

#endif //APPROVALTESTS_CPP_GOOGLECONFIGURATION_H
