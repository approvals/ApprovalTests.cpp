#include "ApprovalTests/reporters/DiffReporter.h"

#include "EnvironmentVariableReporter.h"
#include "WindowsReporters.h"
#include "MacReporters.h"
#include "LinuxReporters.h"

namespace ApprovalTests
{
    DiffReporter::DiffReporter()
        : FirstWorkingReporter({new EnvironmentVariableReporter(),
                                new Mac::MacDiffReporter(),
                                new Linux::LinuxDiffReporter(),
                                new Windows::WindowsDiffReporter()})
    {
    }
}
