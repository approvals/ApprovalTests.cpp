#pragma once

#include "ApprovalTests/reporters/QuietReporter.h"
#include "ApprovalTests/reporters/FrontLoadedReporterDisposer.h"
#include "ApprovalTests/Approvals.h"

namespace ApprovalTests
{
    namespace CIBuildOnlyReporterUtils
    {
        inline FrontLoadedReporterDisposer
        useAsFrontLoadedReporter(const std::shared_ptr<Reporter>& reporter)
        {
            return Approvals::useAsFrontLoadedReporter(
                std::make_shared<ApprovalTests::CIBuildOnlyReporter>(reporter));
        }
    }
} // namespace ApprovalTests
