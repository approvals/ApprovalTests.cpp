#pragma once

#include "FirstWorkingReporter.h"
#include "WindowsReporters.h"
#include "MacReporters.h"
#include "LinuxReporters.h"

namespace ApprovalTests
{
    class DiffReporter : public FirstWorkingReporter
    {
    public:
        DiffReporter()
            : FirstWorkingReporter({new Mac::MacDiffReporter(),
                                    new Linux::LinuxDiffReporter(),
                                    new Windows::WindowsDiffReporter()})
        {
        }
    };
}
