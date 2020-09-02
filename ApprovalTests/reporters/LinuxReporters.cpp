#include "ApprovalTests/reporters/LinuxReporters.h"

namespace ApprovalTests
{
    namespace Linux
    {
        SublimeMergeSnapReporter::SublimeMergeSnapReporter()
            : GenericDiffReporter(DiffPrograms::Linux::SUBLIME_MERGE_SNAP())
        {
            launcher.setForeground(true);
        }

        SublimeMergeFlatpakReporter::SublimeMergeFlatpakReporter()
            : GenericDiffReporter(DiffPrograms::Linux::SUBLIME_MERGE_FLATPAK())
        {
            launcher.setForeground(true);
        }

        SublimeMergeRepositoryPackageReporter::SublimeMergeRepositoryPackageReporter()
            : GenericDiffReporter(DiffPrograms::Linux::SUBLIME_MERGE_REPOSITORY_PACKAGE())
        {
            launcher.setForeground(true);
        }

        SublimeMergeDirectDownloadReporter::SublimeMergeDirectDownloadReporter()
            : GenericDiffReporter(DiffPrograms::Linux::SUBLIME_MERGE_DIRECT_DOWNLOAD())
        {
            launcher.setForeground(true);
        }

        SublimeMergeReporter::SublimeMergeReporter()
            : FirstWorkingReporter({new SublimeMergeSnapReporter(),
                                    new SublimeMergeFlatpakReporter(),
                                    new SublimeMergeRepositoryPackageReporter(),
                                    new SublimeMergeDirectDownloadReporter()})
        {
        }

        KDiff3Reporter::KDiff3Reporter()
            : GenericDiffReporter(DiffPrograms::Linux::KDIFF3())
        {
        }

        MeldReporter::MeldReporter() : GenericDiffReporter(DiffPrograms::Linux::MELD())
        {
        }

        BeyondCompareReporter::BeyondCompareReporter()
            : GenericDiffReporter(DiffPrograms::Linux::BEYOND_COMPARE())
        {
        }

        LinuxDiffReporter::LinuxDiffReporter()
            : FirstWorkingReporter({
                  // begin-snippet: linux_diff_reporters
                  new BeyondCompareReporter(),
                  new MeldReporter(),
                  new SublimeMergeReporter(),
                  new KDiff3Reporter()
                  // end-snippet
              })
        {
        }
    }
}
