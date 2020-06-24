#include "ApprovalTests/reporters/DefaultFrontLoadedReporter.h"

namespace ApprovalTests
{
    DefaultFrontLoadedReporter::DefaultFrontLoadedReporter()
        : FirstWorkingReporter({new CIBuildOnlyReporter()})
    {
    }
}
