#ifndef APPROVALTESTS_CPP_APPROVALCOMPARATOR_H
#define APPROVALTESTS_CPP_APPROVALCOMPARATOR_H

#include <string>

namespace ApprovalTests
{
    class ApprovalComparator
    {
    public:
        virtual ~ApprovalComparator() = default;

        virtual bool contentsAreEquivalent(std::string receivedPath,
                                           std::string approvedPath) const = 0;
    };
}

#endif //APPROVALTESTS_CPP_APPROVALCOMPARATOR_H
