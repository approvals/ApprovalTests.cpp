#pragma once

#include <string>

namespace ApprovalTests
{
    /*! \brief Determine if received and approved files are equivalent

     \see For more information, see
     <a href="https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/CustomComparators.md#top">Custom Comparators</a>
     in the User Guide on GitHub.
     */
    class ApprovalComparator
    {
    public:
        virtual ~ApprovalComparator() = default;

        virtual bool contentsAreEquivalent(std::string receivedPath,
                                           std::string approvedPath) const = 0;
    };
}
