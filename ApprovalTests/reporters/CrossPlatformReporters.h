#pragma once

#include "ApprovalTests/reporters/GenericDiffReporter.h"
#include "ApprovalTests/reporters/FirstWorkingReporter.h"

namespace ApprovalTests
{
    namespace CrossPlatform
    {
        class VisualStudioCodeReporter : public GenericDiffReporter
        {
        public:
            VisualStudioCodeReporter();
        };

        class CrossPlatformDiffReporter : public FirstWorkingReporter
        {
        public:
            CrossPlatformDiffReporter();
        };
    }
}
