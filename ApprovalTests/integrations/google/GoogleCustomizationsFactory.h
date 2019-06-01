#ifndef APPROVALTESTS_CPP_GOOGLECUSTOMIZATIONSFACTORY_H
#define APPROVALTESTS_CPP_GOOGLECUSTOMIZATIONSFACTORY_H

#include "../../Macros.h"
#include "../../StringUtils.h"

#include <vector>
#include <functional>
#include <string>

class GoogleCustomizationsFactory
{
    using Comparator = std::function<bool(const std::string&, const std::string&)>;
    using ComparatorContainer = std::vector< Comparator >;
    APPROVAL_TESTS_MACROS_STATIC(ComparatorContainer, comparatorContainer, GoogleCustomizationsFactory::createContainer())

    static ComparatorContainer* createContainer()
    {
        auto container = new ComparatorContainer;

        auto exactNameMatching = [](std::string testFileNameWithExtension, std::string testCaseName)
        {
            return StringUtils::contains(testFileNameWithExtension, testCaseName + ".");
        };
        container->push_back( exactNameMatching );
        return container;
    }

public:
    static ComparatorContainer getEquivalencyChecks()
    {
        return comparatorContainer();
    }

    // Return if added (always true)
    static bool addEquivalencyCheck(Comparator comparator)
    {
        comparatorContainer().push_back(comparator);
        return true;
    }
    
    static bool addTestCaseNameSuffix(std::string suffix)
    {
        // startcode googletest_customize_lambda
        // main.cpp
        auto customization =  GoogleCustomizationsFactory::addEquivalencyCheck(
            [suffix](std::string testFileNameWithExtension, std::string testCaseName)
            {
                // The dot is used to make sure that we only match when Fixture appears at the end of the file name
                auto modifiedTestCaseName = StringUtils::replaceAll(testCaseName, suffix, ".");
                return StringUtils::contains(testFileNameWithExtension, modifiedTestCaseName);
            });
        // endcode
        return customization;
    }
};

#endif //APPROVALTESTS_CPP_GOOGLECUSTOMIZATIONSFACTORY_H
