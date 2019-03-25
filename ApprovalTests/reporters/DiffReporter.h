#ifndef APPROVALTESTS_CPP_DIFFREPORTER_H
#define APPROVALTESTS_CPP_DIFFREPORTER_H

#include "FirstWorkingReporter.h"
#include "WindowsReporters.h"
#include "MacReporters.h"
#include "LinuxReporters.h"

class DiffReporter : public FirstWorkingReporter
{
public:
    DiffReporter() : FirstWorkingReporter(
            {
                    new Mac::MacDiffReporter(),
                    new Linux::LinuxDiffReporter(),
                    new Windows::WindowsDiffReporter()
            }
    )
    {
    }
};

#endif //APPROVALTESTS_CPP_DIFFREPORTER_H
