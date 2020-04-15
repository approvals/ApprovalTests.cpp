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
            std::shared_ptr<ApprovalTests::ApprovalComparator> newComparator)
            : comparators(comparators_)
            , ext_(extensionWithDot)
            , previousComparator(std::move(previousComparator_))
        {
            comparators_[extensionWithDot] = std::move(newComparator);
        }

        ComparatorDisposer(const ComparatorDisposer&) = delete;

        ComparatorDisposer(ComparatorDisposer&& other) noexcept
            : comparators(other.comparators)
            , ext_(std::move(other.ext_))
            , previousComparator(std::move(other.previousComparator))
        {
            other.isActive = false;
        }

        ~ComparatorDisposer()
        {
            if (isActive)
            {
                comparators[ext_] = previousComparator;
            }
        }

    private:
        // A disposer becomes inactive when it is moved from.
        // This is done to prevent a comparator from being disposed twice.
        bool isActive = true;
        ComparatorContainer& comparators;
        std::string ext_;
        std::shared_ptr<ApprovalTests::ApprovalComparator> previousComparator;
    };
}
