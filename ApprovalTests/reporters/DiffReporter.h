#pragma once

#include "ApprovalTests/reporters/FirstWorkingReporter.h"

namespace ApprovalTests
{
    class DiffReporter : public FirstWorkingReporter
    {
    public:
        DiffReporter();
    };
}
