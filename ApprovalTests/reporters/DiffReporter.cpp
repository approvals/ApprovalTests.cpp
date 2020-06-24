#include "ApprovalTests/reporters/DiffReporter.h"

namespace ApprovalTests
{
    DiffReporter::DiffReporter()
        : FirstWorkingReporter({new Mac::MacDiffReporter(),
                                new Linux::LinuxDiffReporter(),
                                new Windows::WindowsDiffReporter()})
    {
    }
}
