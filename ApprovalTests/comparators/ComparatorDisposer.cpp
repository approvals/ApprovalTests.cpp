#include "ApprovalTests/comparators/ComparatorDisposer.h"

namespace ApprovalTests
{
    ComparatorDisposer::ComparatorDisposer(
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

    ComparatorDisposer::ComparatorDisposer(ComparatorDisposer&& other) noexcept
        : comparators(other.comparators)
        , ext_(std::move(other.ext_))
        , previousComparator(std::move(other.previousComparator))
    {
        other.isActive = false;
    }

    ComparatorDisposer::~ComparatorDisposer()
    {
        if (isActive)
        {
            comparators[ext_] = previousComparator;
        }
    }
}
