#pragma once

#include <map>
#include <memory>
#include <utility>
#include "ApprovalTests/core/ApprovalComparator.h"
#include "ApprovalTests/utilities/Macros.h"

namespace ApprovalTests
{

    using ComparatorContainer =
        std::map<std::string, std::shared_ptr<ApprovalComparator>>;

    class APPROVAL_TESTS_NO_DISCARD ComparatorDisposer
    {
    public:
        ComparatorDisposer(
            ComparatorContainer& comparators_,
            const std::string& extensionWithDot,
            std::shared_ptr<ApprovalTests::ApprovalComparator> previousComparator_,
            std::shared_ptr<ApprovalTests::ApprovalComparator> newComparator);

        ComparatorDisposer(const ComparatorDisposer&) = delete;

        ComparatorDisposer(ComparatorDisposer&& other) noexcept;

        ~ComparatorDisposer();

    private:
        // A disposer becomes inactive when it is moved from.
        // This is done to prevent a comparator from being disposed twice.
        bool isActive = true;
        ComparatorContainer& comparators;
        std::string ext_;
        std::shared_ptr<ApprovalTests::ApprovalComparator> previousComparator;
    };
}
