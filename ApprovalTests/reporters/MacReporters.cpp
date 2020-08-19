#include "ApprovalTests/reporters/MacReporters.h"

#include "DiffPrograms.h"

namespace ApprovalTests
{
    namespace Mac
    {
        DiffMergeReporter::DiffMergeReporter()
            : GenericDiffReporter(DiffPrograms::Mac::DIFF_MERGE())
        {
        }

        // begin-snippet: add_reporter_class_implementation
        AraxisMergeReporter::AraxisMergeReporter()
            : GenericDiffReporter(DiffPrograms::Mac::ARAXIS_MERGE())
        {
        }
        // end-snippet

        VisualStudioCodeReporter::VisualStudioCodeReporter()
            : GenericDiffReporter(DiffPrograms::Mac::VS_CODE())
        {
        }

        BeyondCompareReporter::BeyondCompareReporter()
            : GenericDiffReporter(DiffPrograms::Mac::BEYOND_COMPARE())
        {
        }

        KaleidoscopeReporter::KaleidoscopeReporter()
            : GenericDiffReporter(DiffPrograms::Mac::KALEIDOSCOPE())
        {
        }

        SublimeMergeReporter::SublimeMergeReporter()
            : GenericDiffReporter(DiffPrograms::Mac::SUBLIME_MERGE())
        {
            launcher.setForeground(true);
        }

        KDiff3Reporter::KDiff3Reporter()
            : GenericDiffReporter(DiffPrograms::Mac::KDIFF3())
        {
        }

        P4MergeReporter::P4MergeReporter()
            : GenericDiffReporter(DiffPrograms::Mac::P4MERGE())
        {
        }
        TkDiffReporter::TkDiffReporter()
            : GenericDiffReporter(DiffPrograms::Mac::TK_DIFF())
        {
        }

        CLionDiffReporter::CLionDiffReporter()
            : GenericDiffReporter(DiffPrograms::Mac::CLION())
        {
        }

        MacDiffReporter::MacDiffReporter()
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

        bool MacDiffReporter::report(std::string received, std::string approved) const
        {
            if (!SystemUtils::isMacOs())
            {
                return false;
            }
            return FirstWorkingReporter::report(received, approved);
        }
    }
}
