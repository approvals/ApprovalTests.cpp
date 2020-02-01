#ifndef APPROVALTESTS_CPP_COMPARATORDISPOSER_H
#define APPROVALTESTS_CPP_COMPARATORDISPOSER_H

#include <map>
#include <memory>
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
            ComparatorContainer& comparators,
            std::string extensionWithDot,
            std::shared_ptr<ApprovalTests::ApprovalComparator>
                previousComparator,
            std::shared_ptr<ApprovalTests::ApprovalComparator> newComparator)
            : comparators(comparators)
            , ext_(extensionWithDot)
            , previousComparator(previousComparator)
        {
            comparators[extensionWithDot] = newComparator;
        }

        ComparatorDisposer(const ComparatorDisposer&) = delete;

        ComparatorDisposer(ComparatorDisposer&& other)
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

#endif //APPROVALTESTS_CPP_COMPARATORDISPOSER_H
