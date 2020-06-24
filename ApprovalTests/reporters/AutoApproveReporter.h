#pragma once

#include "ApprovalTests/core/Reporter.h"

namespace ApprovalTests
{
    class AutoApproveReporter : public Reporter
    {
    public:
        bool report(std::string received, std::string approved) const override;
    };
}
