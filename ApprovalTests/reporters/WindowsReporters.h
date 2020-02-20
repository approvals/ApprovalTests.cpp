#ifndef APPROVALTESTS_CPP_WINDOWSREPORTERS_H
#define APPROVALTESTS_CPP_WINDOWSREPORTERS_H

#include "DiffPrograms.h"
#include "FirstWorkingReporter.h"
#include "GenericDiffReporter.h"

namespace ApprovalTests
{
    namespace Windows
    {

        class VisualStudioCodeReporter : public GenericDiffReporter
        {
        public:
            VisualStudioCodeReporter()
                : GenericDiffReporter(DiffPrograms::Windows::VS_CODE())
            {
            }
        };

        // ----------------------- Beyond Compare ----------------------------------
        class BeyondCompare3Reporter : public GenericDiffReporter
        {
        public:
            BeyondCompare3Reporter()
                : GenericDiffReporter(DiffPrograms::Windows::BEYOND_COMPARE_3())
            {
            }
        };

        class BeyondCompare4Reporter : public GenericDiffReporter
        {
        public:
            BeyondCompare4Reporter()
                : GenericDiffReporter(DiffPrograms::Windows::BEYOND_COMPARE_4())
            {
            }
        };

        class BeyondCompareReporter : public FirstWorkingReporter
        {
        public:
            BeyondCompareReporter()
                : FirstWorkingReporter({new BeyondCompare4Reporter(),
                                        new BeyondCompare3Reporter()})
            {
            }
        };

        // ----------------------- Tortoise SVN ------------------------------------
        class TortoiseImageDiffReporter : public GenericDiffReporter
        {
        public:
            TortoiseImageDiffReporter()
                : GenericDiffReporter(
                      DiffPrograms::Windows::TORTOISE_IMAGE_DIFF())
            {
            }
        };

        class TortoiseTextDiffReporter : public GenericDiffReporter
        {
        public:
            TortoiseTextDiffReporter()
                : GenericDiffReporter(
                      DiffPrograms::Windows::TORTOISE_TEXT_DIFF())
            {
            }
        };

        class TortoiseDiffReporter : public FirstWorkingReporter
        {
        public:
            TortoiseDiffReporter()
                : FirstWorkingReporter({new TortoiseTextDiffReporter(),
                                        new TortoiseImageDiffReporter()})
            {
            }
        };

        // ----------------------- Tortoise Git ------------------------------------
        class TortoiseGitTextDiffReporter : public GenericDiffReporter
        {
        public:
            TortoiseGitTextDiffReporter()
                : GenericDiffReporter(
                      DiffPrograms::Windows::TORTOISE_GIT_TEXT_DIFF())
            {
            }
        };

        class TortoiseGitImageDiffReporter : public GenericDiffReporter
        {
        public:
            TortoiseGitImageDiffReporter()
                : GenericDiffReporter(
                      DiffPrograms::Windows::TORTOISE_GIT_IMAGE_DIFF())
            {
            }
        };

        class TortoiseGitDiffReporter : public FirstWorkingReporter
        {
        public:
            TortoiseGitDiffReporter()
                : FirstWorkingReporter({new TortoiseGitTextDiffReporter(),
                                        new TortoiseGitImageDiffReporter()})
            {
            }
        };

        // -------------------------------------------------------------------------
        class WinMergeReporter : public GenericDiffReporter
        {
        public:
            WinMergeReporter()
                : GenericDiffReporter(
                      DiffPrograms::Windows::WIN_MERGE_REPORTER())
            {
            }
        };

        class AraxisMergeReporter : public GenericDiffReporter
        {
        public:
            AraxisMergeReporter()
                : GenericDiffReporter(DiffPrograms::Windows::ARAXIS_MERGE())
            {
            }
        };

        class CodeCompareReporter : public GenericDiffReporter
        {
        public:
            CodeCompareReporter()
                : GenericDiffReporter(DiffPrograms::Windows::CODE_COMPARE())
            {
            }
        };

        class SublimeMergeReporter : public GenericDiffReporter
        {
        public:
            SublimeMergeReporter()
                : GenericDiffReporter(DiffPrograms::Windows::SUBLIME_MERGE())
            {
                launcher.setForeground(true);
            }
        };

        class KDiff3Reporter : public GenericDiffReporter
        {
        public:
            KDiff3Reporter()
                : GenericDiffReporter(DiffPrograms::Windows::KDIFF3())
            {
            }
        };

        class WindowsDiffReporter : public FirstWorkingReporter
        {
        public:
            WindowsDiffReporter()
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
        };
    }
}

#endif //APPROVALTESTS_CPP_WINDOWSREPORTERS_H
