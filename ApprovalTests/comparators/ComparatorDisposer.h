#ifndef APPROVALTESTS_CPP_COMPARATORDISPOSER_H
#define APPROVALTESTS_CPP_COMPARATORDISPOSER_H

#include <map>
#include <memory>
#include "ApprovalTests/core/ApprovalComparator.h"
#include "ApprovalTests/utilities/Macros.h"

namespace ApprovalTests
{

using ComparatorContainer = std::map<std::string, std::shared_ptr<ApprovalComparator> >;

class APPROVAL_TESTS_NO_DISCARD ComparatorDisposer
{
public:
    ComparatorDisposer(
            ComparatorContainer &comparators,
            std::string extensionWithDot,
            std::shared_ptr<ApprovalTests::ApprovalComparator> previousComparator,
            std::shared_ptr<ApprovalTests::ApprovalComparator> newComparator)
            :
            comparators(comparators),
            ext_(extensionWithDot),
            previousComparator(previousComparator)
    {
        comparators[extensionWithDot] = newComparator;
    }

    ~ComparatorDisposer()
    {
        comparators[ext_] = previousComparator;
    }

private:
    ComparatorContainer &comparators;
    std::string ext_;
    std::shared_ptr<ApprovalTests::ApprovalComparator> previousComparator;
};

}

#endif //APPROVALTESTS_CPP_COMPARATORDISPOSER_H
