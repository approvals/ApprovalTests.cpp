#ifndef CATCHPLAYGROUND_DIFFREPORTER_H
#define CATCHPLAYGROUND_DIFFREPORTER_H

#include "FirstWorkingReporter.h"
#include "WindowsReporters.h"
#include "MacReporters.h"

class LinuxDiffReporter : public FirstWorkingReporter
{
public:
    LinuxDiffReporter() : FirstWorkingReporter({new MeldReporter()})
    {
    }
};

class DiffReporter : public FirstWorkingReporter
{
public:
    DiffReporter() : FirstWorkingReporter({new Mac::MacDiffReporter(), new LinuxDiffReporter(), new WindowsDiffReporter()})
    {
    }
};

#endif //CATCHPLAYGROUND_DIFFREPORTER_H
