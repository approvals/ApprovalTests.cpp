#ifndef APPROVALTESTS_CPP_GOOGLECUSTOMIZATIONSFACTORY_H
#define APPROVALTESTS_CPP_GOOGLECUSTOMIZATIONSFACTORY_H

#include "ApprovalTests/utilities/Macros.h"
#include "ApprovalTests/utilities/StringUtils.h"

#include <vector>
#include <functional>
#include <string>

namespace ApprovalTests {
class GoogleCustomizationsFactory
{
public:
    using Comparator = std::function<bool(const std::string&, const std::string&)>;
private:
    using ComparatorContainer = std::vector< Comparator >;
    APPROVAL_TESTS_MACROS_STATIC(ComparatorContainer, comparatorContainer, GoogleCustomizationsFactory::createContainer())

    static ComparatorContainer* createContainer()
    {
        auto container = new ComparatorContainer;

        auto exactNameMatching = [](const std::string& testFileNameWithExtension, const std::string& testCaseName)
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

    APPROVAL_TESTS_NO_DISCARD static bool addTestCaseNameRedundancyCheck(const Comparator& comparator)
    {
        comparatorContainer().push_back(comparator);
        return true;
    }
    

};
}

#endif //APPROVALTESTS_CPP_GOOGLECUSTOMIZATIONSFACTORY_H
