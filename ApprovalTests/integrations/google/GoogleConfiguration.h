#ifndef APPROVALTESTS_CPP_GOOGLECONFIGURATION_H
#define APPROVALTESTS_CPP_GOOGLECONFIGURATION_H

#include "GoogleCustomizationsFactory.h"

class GoogleConfiguration
{
public:
    // This result is not used, it is only there to allow the method to execute, when this is used outside a function.
    APPROVAL_TESTS_NO_DISCARD static bool addTestCaseNameRedundancyCheck(GoogleCustomizationsFactory::Comparator comparator)
    {
        return GoogleCustomizationsFactory::addTestCaseNameRedundancyCheck(comparator);
    }

    // This result is not used, it is only there to allow the method to execute, when this is used outside a function.
    APPROVAL_TESTS_NO_DISCARD static bool addIgnorableTestCaseNameSuffix(std::string suffix)
    {
        return addTestCaseNameRedundancyCheck( createIgnorableTestCaseNameSuffixCheck(suffix) );
    }

    static GoogleCustomizationsFactory::Comparator createIgnorableTestCaseNameSuffixCheck( const std::string& suffix )
    {
        return [suffix](std::string testFileNameWithExtension, std::string testCaseName)
        {
            if (testCaseName.length() <= suffix.length() || !StringUtils::endsWith(testCaseName, suffix))
            {
                return false;
            }

            auto withoutSuffix = testCaseName.substr(0, testCaseName.length() - suffix.length());
            auto withFileExtension = withoutSuffix + ".";
            return StringUtils::contains(testFileNameWithExtension, withFileExtension);
        };
    }
};

#endif //APPROVALTESTS_CPP_GOOGLECONFIGURATION_H
