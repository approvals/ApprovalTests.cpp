#include "ApprovalTests/reporters/MacReporters.h"

#include "DiffPrograms.h"

namespace ApprovalTests
{
    Mac::DiffMergeReporter::DiffMergeReporter()
        : GenericDiffReporter(DiffPrograms::Mac::DIFF_MERGE())
    {
    }

    // begin-snippet: add_reporter_class_implementation
    Mac::AraxisMergeReporter::AraxisMergeReporter()
        : GenericDiffReporter(DiffPrograms::Mac::ARAXIS_MERGE())
    {
    }
    // end-snippet

    Mac::VisualStudioCodeReporter::VisualStudioCodeReporter()
        : GenericDiffReporter(DiffPrograms::Mac::VS_CODE())
    {
    }

    Mac::BeyondCompareReporter::BeyondCompareReporter()
        : GenericDiffReporter(DiffPrograms::Mac::BEYOND_COMPARE())
    {
    }

    Mac::KaleidoscopeReporter::KaleidoscopeReporter()
        : GenericDiffReporter(DiffPrograms::Mac::KALEIDOSCOPE())
    {
    }

    Mac::SublimeMergeReporter::SublimeMergeReporter()
        : GenericDiffReporter(DiffPrograms::Mac::SUBLIME_MERGE())
    {
        launcher.setForeground(true);
    }

    Mac::KDiff3Reporter::KDiff3Reporter()
        : GenericDiffReporter(DiffPrograms::Mac::KDIFF3())
    {
    }

    Mac::P4MergeReporter::P4MergeReporter()
        : GenericDiffReporter(DiffPrograms::Mac::P4MERGE())
    {
    }
    Mac::TkDiffReporter::TkDiffReporter()
        : GenericDiffReporter(DiffPrograms::Mac::TK_DIFF())
    {
    }

    Mac::CLionDiffReporter::CLionDiffReporter()
        : GenericDiffReporter(DiffPrograms::Mac::CLION())
    {
    }

    Mac::MacDiffReporter::MacDiffReporter()
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
              new VisualStudioCodeReporter(),
              new CLionDiffReporter()
              // end-snippet
          })
    {
    }
}
