#ifndef CATCHPLAYGROUND_DIFFREPORTER_H
#define CATCHPLAYGROUND_DIFFREPORTER_H

#include "FirstWorkingReporter.h"

class MacDiffReporter : public FirstWorkingReporter
{
public:
    MacDiffReporter() : FirstWorkingReporter({new DiffMergeReporter()})
    {
    }
};

class LinuxDiffReporter : public FirstWorkingReporter
{
public:
    LinuxDiffReporter() : FirstWorkingReporter({new MeldReporter()})
    {
    }
};

class WindowsDiffReporter : public FirstWorkingReporter
{
public:
    WindowsDiffReporter() : FirstWorkingReporter({})
    {
    }
};

class DiffReporter : public FirstWorkingReporter
{
public:
    DiffReporter() : FirstWorkingReporter({new MacDiffReporter(), new LinuxDiffReporter(), new WindowsDiffReporter()})
    {
    }

};

#endif //CATCHPLAYGROUND_DIFFREPORTER_H
