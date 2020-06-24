#include "ApprovalTests/reporters/WindowsReporters.h"

#include "DiffPrograms.h"

namespace ApprovalTests
{

    Windows::VisualStudioCodeReporter::VisualStudioCodeReporter()
        : GenericDiffReporter(DiffPrograms::Windows::VS_CODE())
    {
    }

    // ----------------------- Beyond Compare ----------------------------------
    Windows::BeyondCompare3Reporter::BeyondCompare3Reporter()
        : GenericDiffReporter(DiffPrograms::Windows::BEYOND_COMPARE_3())
    {
    }

    Windows::BeyondCompare4Reporter::BeyondCompare4Reporter()
        : GenericDiffReporter(DiffPrograms::Windows::BEYOND_COMPARE_4())
    {
    }

    Windows::BeyondCompareReporter::BeyondCompareReporter()
        : FirstWorkingReporter(
              {new BeyondCompare4Reporter(), new BeyondCompare3Reporter()})
    {
    }

    // ----------------------- Tortoise SVN ------------------------------------
    Windows::TortoiseImageDiffReporter::TortoiseImageDiffReporter()
        : GenericDiffReporter(DiffPrograms::Windows::TORTOISE_IMAGE_DIFF())
    {
    }

    Windows::TortoiseTextDiffReporter::TortoiseTextDiffReporter()
        : GenericDiffReporter(DiffPrograms::Windows::TORTOISE_TEXT_DIFF())
    {
    }

    Windows::TortoiseDiffReporter::TortoiseDiffReporter()
        : FirstWorkingReporter(
              {new TortoiseTextDiffReporter(), new TortoiseImageDiffReporter()})
    {
    }

    // ----------------------- Tortoise Git ------------------------------------
    Windows::TortoiseGitTextDiffReporter::TortoiseGitTextDiffReporter()
        : GenericDiffReporter(DiffPrograms::Windows::TORTOISE_GIT_TEXT_DIFF())
    {
    }

    Windows::TortoiseGitImageDiffReporter::TortoiseGitImageDiffReporter()
        : GenericDiffReporter(DiffPrograms::Windows::TORTOISE_GIT_IMAGE_DIFF())
    {
    }

    Windows::TortoiseGitDiffReporter::TortoiseGitDiffReporter()
        : FirstWorkingReporter(
              {new TortoiseGitTextDiffReporter(), new TortoiseGitImageDiffReporter()})
    {
    }

    // -------------------------------------------------------------------------
    Windows::WinMergeReporter::WinMergeReporter()
        : GenericDiffReporter(DiffPrograms::Windows::WIN_MERGE_REPORTER())
    {
    }

    Windows::AraxisMergeReporter::AraxisMergeReporter()
        : GenericDiffReporter(DiffPrograms::Windows::ARAXIS_MERGE())
    {
    }

    Windows::CodeCompareReporter::CodeCompareReporter()
        : GenericDiffReporter(DiffPrograms::Windows::CODE_COMPARE())
    {
    }

    Windows::SublimeMergeReporter::SublimeMergeReporter()
        : GenericDiffReporter(DiffPrograms::Windows::SUBLIME_MERGE())
    {
        launcher.setForeground(true);
    }

    Windows::KDiff3Reporter::KDiff3Reporter()
        : GenericDiffReporter(DiffPrograms::Windows::KDIFF3())
    {
    }

    Windows::WindowsDiffReporter::WindowsDiffReporter()
        : FirstWorkingReporter({
              // begin-snippet: windows_diff_reporters
              new TortoiseDiffReporter(), // Note that this uses Tortoise SVN Diff
              new TortoiseGitDiffReporter(),
              new BeyondCompareReporter(),
              new WinMergeReporter(),
              new AraxisMergeReporter(),
              new CodeCompareReporter(),
              new SublimeMergeReporter(),
              new KDiff3Reporter(),
              new VisualStudioCodeReporter(),
              // end-snippet
          })
    {
    }
}
