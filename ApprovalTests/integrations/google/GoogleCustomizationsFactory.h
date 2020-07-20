#pragma once

#include "ApprovalTests/utilities/StringUtils.h"
#include "ApprovalTests/utilities/Macros.h"

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
        static ComparatorContainer& comparatorContainer();

    public:
        static ComparatorContainer getEquivalencyChecks();

        APPROVAL_TESTS_NO_DISCARD static bool
        addTestCaseNameRedundancyCheck(const Comparator& comparator);
    };
}
