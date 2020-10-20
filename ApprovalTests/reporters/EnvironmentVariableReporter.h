#pragma once

#include "ApprovalTests/core/Reporter.h"
#include <memory>

namespace ApprovalTests
{
    class EnvironmentVariableReporter : public Reporter
    {
    public:
        bool report(std::string received, std::string approved) const override;
    };
}
