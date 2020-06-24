#include "ApprovalTests/reporters/LinuxReporters.h"

namespace ApprovalTests
{
    Linux::SublimeMergeSnapReporter::SublimeMergeSnapReporter()
        : GenericDiffReporter(DiffPrograms::Linux::SUBLIME_MERGE_SNAP())
    {
        launcher.setForeground(true);
    }

    Linux::SublimeMergeFlatpakReporter::SublimeMergeFlatpakReporter()
        : GenericDiffReporter(DiffPrograms::Linux::SUBLIME_MERGE_FLATPAK())
    {
        launcher.setForeground(true);
    }

    Linux::SublimeMergeRepositoryPackageReporter::SublimeMergeRepositoryPackageReporter()
        : GenericDiffReporter(DiffPrograms::Linux::SUBLIME_MERGE_REPOSITORY_PACKAGE())
    {
        launcher.setForeground(true);
    }

    Linux::SublimeMergeDirectDownloadReporter::SublimeMergeDirectDownloadReporter()
        : GenericDiffReporter(DiffPrograms::Linux::SUBLIME_MERGE_DIRECT_DOWNLOAD())
    {
        launcher.setForeground(true);
    }

    Linux::SublimeMergeReporter::SublimeMergeReporter()
        : FirstWorkingReporter({new SublimeMergeSnapReporter(),
                                new SublimeMergeFlatpakReporter(),
                                new SublimeMergeRepositoryPackageReporter(),
                                new SublimeMergeDirectDownloadReporter()})
    {
    }

    Linux::KDiff3Reporter::KDiff3Reporter()
        : GenericDiffReporter(DiffPrograms::Linux::KDIFF3())
    {
    }

    Linux::MeldReporter::MeldReporter() : GenericDiffReporter(DiffPrograms::Linux::MELD())
    {
    }

    Linux::BeyondCompareReporter::BeyondCompareReporter()
        : GenericDiffReporter(DiffPrograms::Linux::BEYOND_COMPARE())
    {
    }

    Linux::LinuxDiffReporter::LinuxDiffReporter()
        : FirstWorkingReporter({
              // begin-snippet: linux_diff_reporters
              new BeyondCompareReporter(),
              new MeldReporter(),
              new SublimeMergeReporter(),
              new KDiff3Reporter()
              // Note: ApprovalTests::Mac::CLionDiffReporter also works on Linux
              // end-snippet
          })
    {
    }
}
