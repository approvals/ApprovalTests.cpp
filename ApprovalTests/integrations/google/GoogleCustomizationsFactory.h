#pragma once

#include "ApprovalTests/utilities/StringUtils.h"

#include <vector>
#include <functional>
#include <string>

namespace ApprovalTests
{
    class GoogleCustomizationsFactory
    {
    public:
        using Comparator = std::function<bool(const std::string&, const std::string&)>;

    private:
        using ComparatorContainer = std::vector<Comparator>;
        static ComparatorContainer& comparatorContainer()
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

    public:
        static ComparatorContainer getEquivalencyChecks()
        {
            return comparatorContainer();
        }

        APPROVAL_TESTS_NO_DISCARD static bool
        addTestCaseNameRedundancyCheck(const Comparator& comparator)
        {
            comparatorContainer().push_back(comparator);
            return true;
        }
    };
}
