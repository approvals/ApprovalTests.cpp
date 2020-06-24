#include "ApprovalTests/integrations/google/GoogleCustomizationsFactory.h"

namespace ApprovalTests
{
    GoogleCustomizationsFactory::ComparatorContainer&
    GoogleCustomizationsFactory::comparatorContainer()
    {
        static ComparatorContainer container;
        if (container.empty())
        {
            auto exactNameMatching = [](const std::string& testFileNameWithExtension,
                                        const std::string& testCaseName) {
                return StringUtils::contains(testFileNameWithExtension,
                                             testCaseName + ".");
            };
            container.push_back(exactNameMatching);
        }
        return container;
    }

    GoogleCustomizationsFactory::ComparatorContainer
    GoogleCustomizationsFactory::getEquivalencyChecks()
    {
        return comparatorContainer();
    }

    bool GoogleCustomizationsFactory::addTestCaseNameRedundancyCheck(
        const GoogleCustomizationsFactory::Comparator& comparator)
    {
        comparatorContainer().push_back(comparator);
        return true;
    }
}
