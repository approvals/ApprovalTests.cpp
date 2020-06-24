#include "ApprovalTests/reporters/DefaultFrontLoadedReporter.h"
#include "ApprovalTests/reporters/CIBuildOnlyReporter.h"

namespace ApprovalTests
{
    DefaultFrontLoadedReporter::DefaultFrontLoadedReporter()
        : FirstWorkingReporter({new CIBuildOnlyReporter()})
    {
    }
}
