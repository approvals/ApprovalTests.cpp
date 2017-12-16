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
    WindowsDiffReporter() : FirstWorkingReporter({new WinMergeReporter()})
    {
        std::cout << "windowsDiff:" << std::endl;

    }
};

class DiffReporter : public FirstWorkingReporter
{
public:
    DiffReporter() : FirstWorkingReporter({new MacDiffReporter(), new LinuxDiffReporter(), new WindowsDiffReporter()})
    {
        std::cout << "diff:" << std::endl;

    }

};

#endif //CATCHPLAYGROUND_DIFFREPORTER_H
