#ifndef APPROVALTESTS_CPP_LINUXREPORTERS_H
#define APPROVALTESTS_CPP_LINUXREPORTERS_H

#include "DiffPrograms.h"
#include "GenericDiffReporter.h"
#include "FirstWorkingReporter.h"

namespace Linux
{
    class KDiff3Reporter : public GenericDiffReporter {
    public:
        KDiff3Reporter() : GenericDiffReporter(DiffPrograms::Linux::KDIFF3()) {};
    };

    class MeldReporter : public GenericDiffReporter {
    public:
        MeldReporter() : GenericDiffReporter(DiffPrograms::Linux::MELD()) {};
    };

    class LinuxDiffReporter : public FirstWorkingReporter
    {
    public:
        LinuxDiffReporter() : FirstWorkingReporter(
                {
                        // begin-snippet: linux_diff_reporters
                        new MeldReporter(),
                        new KDiff3Reporter()
                        // end-snippet
                }
        )
        {
        }
    };

}

#endif //APPROVALTESTS_CPP_LINUXREPORTERS_H
