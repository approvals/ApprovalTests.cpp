#pragma once

#include "ApprovalTests/reporters/QuietReporter.h"
#include "ApprovalTests/reporters/FrontLoadedReporterDisposer.h"

namespace ApprovalTests
{
    namespace CIBuildOnlyReporterUtils
    {
        FrontLoadedReporterDisposer
        useAsFrontLoadedReporter(const std::shared_ptr<Reporter>& reporter);
    }
} // namespace ApprovalTests
