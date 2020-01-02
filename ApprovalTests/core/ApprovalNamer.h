#ifndef APPROVALTESTS_CPP_APPROVALNAMER_H
#define APPROVALTESTS_CPP_APPROVALNAMER_H

#include <string>

namespace ApprovalTests
{
    class ApprovalNamer
    {
    public:
        virtual ~ApprovalNamer() = default;
        virtual std::string
        getApprovedFile(std::string extensionWithDot) const = 0;
        virtual std::string
        getReceivedFile(std::string extensionWithDot) const = 0;
    };
}

#endif
