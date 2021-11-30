#pragma once

#include "ApprovalTests/integrations/google/GoogleCustomizationsFactory.h"

namespace ApprovalTests
{
    class GoogleConfiguration
    {
    public:
        // This result is not used, it is only there to allow the method to execute, when this is used outside a function.
        APPROVAL_TESTS_NO_DISCARD static bool addTestCaseNameRedundancyCheck(
            GoogleCustomizationsFactory::Comparator comparator);

        // This result is not used, it is only there to allow the method to execute, when this is used outside a function.
        APPROVAL_TESTS_NO_DISCARD static bool
        addIgnorableTestCaseNameSuffix(std::string suffix);

        static GoogleCustomizationsFactory::Comparator
        createIgnorableTestCaseNameSuffixCheck(const std::string& suffix);
    };
}
