#pragma once

#include "ApprovalTests/reporters/CIBuildOnlyReporter.h"
#include "ApprovalTests/reporters/FirstWorkingReporter.h"

namespace ApprovalTests
{
    class DefaultFrontLoadedReporter : public FirstWorkingReporter
    {
    public:
        DefaultFrontLoadedReporter();
    };
}
