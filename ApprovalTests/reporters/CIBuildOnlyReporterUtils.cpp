#include "ApprovalTests/reporters/CIBuildOnlyReporterUtils.h"
#include "ApprovalTests/reporters/CIBuildOnlyReporter.h"
#include "ApprovalTests/Approvals.h"

namespace ApprovalTests
{
    FrontLoadedReporterDisposer CIBuildOnlyReporterUtils::useAsFrontLoadedReporter(
        const std::shared_ptr<Reporter>& reporter)
    {
        return Approvals::useAsFrontLoadedReporter(
            std::make_shared<ApprovalTests::CIBuildOnlyReporter>(reporter));
    }
}
