#pragma once

#include <string>

namespace ApprovalTests
{
    class Reporter
    {
    public:
        virtual ~Reporter() = default;
        virtual bool report(std::string received, std::string approved) const = 0;
    };
}
