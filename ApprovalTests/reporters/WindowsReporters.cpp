#include "ApprovalTests/reporters/WindowsReporters.h"

#include "DiffPrograms.h"

namespace ApprovalTests
{
    namespace Windows
    {
        VisualStudioCodeReporter::VisualStudioCodeReporter()
            : GenericDiffReporter(DiffPrograms::Windows::VS_CODE())
        {
        }

        // ----------------------- Beyond Compare ----------------------------------
        BeyondCompare3Reporter::BeyondCompare3Reporter()
            : GenericDiffReporter(DiffPrograms::Windows::BEYOND_COMPARE_3())
        {
        }

        BeyondCompare4Reporter::BeyondCompare4Reporter()
            : GenericDiffReporter(DiffPrograms::Windows::BEYOND_COMPARE_4())
        {
        }

        BeyondCompareReporter::BeyondCompareReporter()
            : FirstWorkingReporter(
                  {new BeyondCompare4Reporter(), new BeyondCompare3Reporter()})
        {
        }

        // ----------------------- Tortoise SVN ------------------------------------
        TortoiseImageDiffReporter::TortoiseImageDiffReporter()
            : GenericDiffReporter(DiffPrograms::Windows::TORTOISE_IMAGE_DIFF())
        {
        }

        TortoiseTextDiffReporter::TortoiseTextDiffReporter()
            : GenericDiffReporter(DiffPrograms::Windows::TORTOISE_TEXT_DIFF())
        {
        }

        TortoiseDiffReporter::TortoiseDiffReporter()
            : FirstWorkingReporter(
                  {new TortoiseTextDiffReporter(), new TortoiseImageDiffReporter()})
        {
        }

        // ----------------------- Tortoise Git ------------------------------------
        TortoiseGitTextDiffReporter::TortoiseGitTextDiffReporter()
            : GenericDiffReporter(DiffPrograms::Windows::TORTOISE_GIT_TEXT_DIFF())
        {
        }

        TortoiseGitImageDiffReporter::TortoiseGitImageDiffReporter()
            : GenericDiffReporter(DiffPrograms::Windows::TORTOISE_GIT_IMAGE_DIFF())
        {
        }

        TortoiseGitDiffReporter::TortoiseGitDiffReporter()
            : FirstWorkingReporter(
                  {new TortoiseGitTextDiffReporter(), new TortoiseGitImageDiffReporter()})
        {
        }

        // -------------------------------------------------------------------------
        WinMergeReporter::WinMergeReporter()
            : GenericDiffReporter(DiffPrograms::Windows::WIN_MERGE_REPORTER())
        {
        }

        AraxisMergeReporter::AraxisMergeReporter()
            : GenericDiffReporter(DiffPrograms::Windows::ARAXIS_MERGE())
        {
        }

        CodeCompareReporter::CodeCompareReporter()
            : GenericDiffReporter(DiffPrograms::Windows::CODE_COMPARE())
        {
        }

        SublimeMergeReporter::SublimeMergeReporter()
            : GenericDiffReporter(DiffPrograms::Windows::SUBLIME_MERGE())
        {
            launcher.setForeground(true);
        }

        KDiff3Reporter::KDiff3Reporter()
            : GenericDiffReporter(DiffPrograms::Windows::KDIFF3())
        {
        }

        WindowsDiffReporter::WindowsDiffReporter()
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

        bool WindowsDiffReporter::report(std::string received, std::string approved) const
        {
            if (!SystemUtils::isWindowsOs())
            {
                return false;
            }
            return FirstWorkingReporter::report(received, approved);
        }
    }
}
