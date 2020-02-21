#ifndef APPROVALTESTS_CPP_MACREPORTERS_H
#define APPROVALTESTS_CPP_MACREPORTERS_H

#include "DiffPrograms.h"
#include "GenericDiffReporter.h"
#include "FirstWorkingReporter.h"

namespace ApprovalTests
{
    namespace Mac
    {
        class DiffMergeReporter : public GenericDiffReporter
        {
        public:
            DiffMergeReporter()
                : GenericDiffReporter(DiffPrograms::Mac::DIFF_MERGE())
            {
            }
        };

        // begin-snippet: add_reporter_class
        class AraxisMergeReporter : public GenericDiffReporter
        {
        public:
            AraxisMergeReporter()
                : GenericDiffReporter(DiffPrograms::Mac::ARAXIS_MERGE())
            {
            }
        };
        // end-snippet

        class VisualStudioCodeReporter : public GenericDiffReporter
        {
        public:
            VisualStudioCodeReporter()
                : GenericDiffReporter(DiffPrograms::Mac::VS_CODE())
            {
            }
        };

        class BeyondCompareReporter : public GenericDiffReporter
        {
        public:
            BeyondCompareReporter()
                : GenericDiffReporter(DiffPrograms::Mac::BEYOND_COMPARE())
            {
            }
        };

        class KaleidoscopeReporter : public GenericDiffReporter
        {
        public:
            KaleidoscopeReporter()
                : GenericDiffReporter(DiffPrograms::Mac::KALEIDOSCOPE())
            {
            }
        };

        class SublimeMergeReporter : public GenericDiffReporter
        {
        public:
            SublimeMergeReporter()
                : GenericDiffReporter(DiffPrograms::Mac::SUBLIME_MERGE())
            {
                launcher.setForeground(true);
            }
        };

        class KDiff3Reporter : public GenericDiffReporter
        {
        public:
            KDiff3Reporter() : GenericDiffReporter(DiffPrograms::Mac::KDIFF3())
            {
            }
        };

        class P4MergeReporter : public GenericDiffReporter
        {
        public:
            P4MergeReporter()
                : GenericDiffReporter(DiffPrograms::Mac::P4MERGE())
            {
            }
        };

        class TkDiffReporter : public GenericDiffReporter
        {
        public:
            TkDiffReporter() : GenericDiffReporter(DiffPrograms::Mac::TK_DIFF())
            {
            }
        };

        class MacDiffReporter : public FirstWorkingReporter
        {
        public:
            MacDiffReporter()
                : FirstWorkingReporter({
                      // begin-snippet: mac_diff_reporters
                      new AraxisMergeReporter(),
                      new BeyondCompareReporter(),
                      new DiffMergeReporter(),
                      new KaleidoscopeReporter(),
                      new P4MergeReporter(),
                      new SublimeMergeReporter(),
                      new KDiff3Reporter(),
                      new TkDiffReporter(),
                      new VisualStudioCodeReporter()
                      // end-snippet
                  })
            {
            }
        };
    }
}

#endif //APPROVALTESTS_CPP_MACREPORTERS_H
