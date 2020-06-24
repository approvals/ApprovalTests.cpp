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
        DiffReporter();
    };
}
