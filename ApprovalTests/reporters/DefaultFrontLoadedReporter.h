#ifndef APPROVALTESTS_CPP_DEFAULTFRONTLOADEDREPORTER_H
#define APPROVALTESTS_CPP_DEFAULTFRONTLOADEDREPORTER_H

#include "ApprovalTests/reporters/CIBuildOnlyReporter.h"
#include "ApprovalTests/reporters/FirstWorkingReporter.h"

namespace ApprovalTests
{
    class DefaultFrontLoadedReporter : public FirstWorkingReporter
    {
    public:
        DefaultFrontLoadedReporter()
            : FirstWorkingReporter({new CIBuildOnlyReporter()})
        {
        }
    };
}

#endif //APPROVALTESTS_CPP_DEFAULTFRONTLOADEDREPORTER_H
