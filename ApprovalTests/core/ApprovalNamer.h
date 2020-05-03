#pragma once

#include <string>

namespace ApprovalTests
{
    /*! \brief Interface class for controlling how output files are named.

     \see For more information, see
     \userguide{Namers,Namers}
     */
    class ApprovalNamer
    {
    public:
        virtual ~ApprovalNamer() = default;
        virtual std::string getApprovedFile(std::string extensionWithDot) const = 0;
        virtual std::string getReceivedFile(std::string extensionWithDot) const = 0;
    };
}
