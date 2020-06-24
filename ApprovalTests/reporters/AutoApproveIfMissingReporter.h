#pragma once

#include "ApprovalTests/core/Reporter.h"
#include "AutoApproveReporter.h"
#include "ApprovalTests/utilities/FileUtils.h"

namespace ApprovalTests
{
    class AutoApproveIfMissingReporter : public Reporter
    {
    public:
        bool report(std::string received, std::string approved) const override;
    };
}
