#ifndef CATCHPLAYGROUND_DIFFREPORTER_H
#define CATCHPLAYGROUND_DIFFREPORTER_H

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

#endif //CATCHPLAYGROUND_DIFFREPORTER_H
