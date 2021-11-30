#pragma once

#include "ApprovalTests/reporters/FirstWorkingReporter.h"
#include "ApprovalTests/reporters/GenericDiffReporter.h"

namespace ApprovalTests
{
    namespace Windows
    {

        class VisualStudioCodeReporter : public GenericDiffReporter
        {
        public:
            VisualStudioCodeReporter();
        };

        // ----------------------- Beyond Compare ----------------------------------
        class BeyondCompare3Reporter : public GenericDiffReporter
        {
        public:
            BeyondCompare3Reporter();
        };

        class BeyondCompare4Reporter : public GenericDiffReporter
        {
        public:
            BeyondCompare4Reporter();
        };

        class BeyondCompareReporter : public FirstWorkingReporter
        {
        public:
            BeyondCompareReporter();
        };

        // ----------------------- Tortoise SVN ------------------------------------
        class TortoiseImageDiffReporter : public GenericDiffReporter
        {
        public:
            TortoiseImageDiffReporter();
        };

        class TortoiseTextDiffReporter : public GenericDiffReporter
        {
        public:
            TortoiseTextDiffReporter();
        };

        class TortoiseDiffReporter : public FirstWorkingReporter
        {
        public:
            TortoiseDiffReporter();
        };

        // ----------------------- Tortoise Git ------------------------------------
        class TortoiseGitTextDiffReporter : public GenericDiffReporter
        {
        public:
            TortoiseGitTextDiffReporter();
        };

        class TortoiseGitImageDiffReporter : public GenericDiffReporter
        {
        public:
            TortoiseGitImageDiffReporter();
        };

        class TortoiseGitDiffReporter : public FirstWorkingReporter
        {
        public:
            TortoiseGitDiffReporter();
        };

        // -------------------------------------------------------------------------
        class WinMergeReporter : public GenericDiffReporter
        {
        public:
            WinMergeReporter();
        };

        class AraxisMergeReporter : public GenericDiffReporter
        {
        public:
            AraxisMergeReporter();
        };

        class CodeCompareReporter : public GenericDiffReporter
        {
        public:
            CodeCompareReporter();
        };

        class SublimeMergeReporter : public GenericDiffReporter
        {
        public:
            SublimeMergeReporter();
        };

        class KDiff3Reporter : public GenericDiffReporter
        {
        public:
            KDiff3Reporter();
        };

        class WindowsDiffReporter : public FirstWorkingReporter
        {
        public:
            WindowsDiffReporter();

            bool report(std::string received, std::string approved) const override;
        };
    }
}
