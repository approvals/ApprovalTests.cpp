#pragma once

#include "ApprovalTests/core/Reporter.h"
#include <memory>

namespace ApprovalTests
{
    class EnvironmentVariableReporter : public Reporter
    {
        std::shared_ptr<Reporter> defaultIfNotFound_;

    public:
        EnvironmentVariableReporter();
        EnvironmentVariableReporter(std::shared_ptr<Reporter> defaultIfNotFound);
        bool report(std::string received, std::string approved) const override;
    };
}
