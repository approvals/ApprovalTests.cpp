#ifndef APPROVALTESTS_CPP_LINUXREPORTERS_H
#define APPROVALTESTS_CPP_LINUXREPORTERS_H

#include "FirstWorkingReporter.h"

namespace Linux
{
    class MeldReporter : public GenericDiffReporter {
    public:
        MeldReporter() : GenericDiffReporter("meld") {};
    };

    class LinuxDiffReporter : public FirstWorkingReporter
    {
    public:
        LinuxDiffReporter() : FirstWorkingReporter({new MeldReporter()})
        {
        }
    };

}

#endif //APPROVALTESTS_CPP_LINUXREPORTERS_H
