#pragma once
#include "ApprovalTests/core/Reporter.h"

namespace ApprovalTests
{
    class DocTestReporter : public Reporter
    {
    public:
        bool report(std::string received, std::string approved) const override;
    };
}
