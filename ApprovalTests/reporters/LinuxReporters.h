#ifndef APPROVALTESTS_CPP_LINUXREPORTERS_H
#define APPROVALTESTS_CPP_LINUXREPORTERS_H

#include "DiffPrograms.h"
#include "GenericDiffReporter.h"
#include "FirstWorkingReporter.h"

namespace ApprovalTests
{
    namespace Linux
    {
        class SublimeMergeSnapReporter : public GenericDiffReporter
        {
        public:
            SublimeMergeSnapReporter()
                : GenericDiffReporter(DiffPrograms::Linux::SUBLIME_MERGE_SNAP())
            {
                launcher.setForeground(true);
            }
        };

        class SublimeMergeFlatpakReporter : public GenericDiffReporter
        {
        public:
            SublimeMergeFlatpakReporter()
                : GenericDiffReporter(
                      DiffPrograms::Linux::SUBLIME_MERGE_FLATPAK())
            {
                launcher.setForeground(true);
            }
        };

        class SublimeMergeReporter : public GenericDiffReporter
        {
        public:
            SublimeMergeReporter()
                : GenericDiffReporter(DiffPrograms::Linux::SUBLIME_MERGE())
            {
                launcher.setForeground(true);
            }
        };

        class SublimeMergeTarballReporter : public GenericDiffReporter
        {
        public:
            SublimeMergeTarballReporter()
                : GenericDiffReporter(
                      DiffPrograms::Linux::SUBLIME_MERGE_TARBALL())
            {
                launcher.setForeground(true);
            }
        };

        class KDiff3Reporter : public GenericDiffReporter
        {
        public:
            KDiff3Reporter()
                : GenericDiffReporter(DiffPrograms::Linux::KDIFF3())
            {
            }
        };

        class MeldReporter : public GenericDiffReporter
        {
        public:
            MeldReporter() : GenericDiffReporter(DiffPrograms::Linux::MELD())
            {
            }
        };

        class LinuxDiffReporter : public FirstWorkingReporter
        {
        public:
            LinuxDiffReporter()
                : FirstWorkingReporter({
                      // begin-snippet: linux_diff_reporters
                      new MeldReporter(),
                      new SublimeMergeSnapReporter(),
                      new SublimeMergeFlatpakReporter(),
                      new SublimeMergeReporter(),
                      new SublimeMergeTarballReporter(),
                      new KDiff3Reporter()
                      // end-snippet
                  })
            {
            }
        };
    }
}

#endif //APPROVALTESTS_CPP_LINUXREPORTERS_H
