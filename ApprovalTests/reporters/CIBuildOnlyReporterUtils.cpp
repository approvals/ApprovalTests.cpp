#include "ApprovalTests/reporters/CIBuildOnlyReporterUtils.h"

namespace ApprovalTests
{
    FrontLoadedReporterDisposer CIBuildOnlyReporterUtils::useAsFrontLoadedReporter(
        const std::shared_ptr<Reporter>& reporter)
    {
        return Approvals::useAsFrontLoadedReporter(
            std::make_shared<ApprovalTests::CIBuildOnlyReporter>(reporter));
    }
}
