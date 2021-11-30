#pragma once

#include "ApprovalTests/reporters/GenericDiffReporter.h"
#include "ApprovalTests/reporters/FirstWorkingReporter.h"

namespace ApprovalTests
{
    namespace Mac
    {
        class DiffMergeReporter : public GenericDiffReporter
        {
        public:
            DiffMergeReporter();
        };

        // begin-snippet: add_reporter_class_header
        class AraxisMergeReporter : public GenericDiffReporter
        {
        public:
            AraxisMergeReporter();
        };
        // end-snippet

        class VisualStudioCodeReporter : public GenericDiffReporter
        {
        public:
            VisualStudioCodeReporter();
        };

        class BeyondCompareReporter : public GenericDiffReporter
        {
        public:
            BeyondCompareReporter();
        };

        class KaleidoscopeReporter : public GenericDiffReporter
        {
        public:
            KaleidoscopeReporter();
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

        class P4MergeReporter : public GenericDiffReporter
        {
        public:
            P4MergeReporter();
        };

        class TkDiffReporter : public GenericDiffReporter
        {
        public:
            TkDiffReporter();
        };

        // Note that this will be found on Linux too.
        // See https://github.com/approvals/ApprovalTests.cpp/issues/138 for limitations
        class CLionDiffReporter : public GenericDiffReporter
        {
        public:
            CLionDiffReporter();
        };

        class MacDiffReporter : public FirstWorkingReporter
        {
        public:
            MacDiffReporter();

            bool report(std::string received, std::string approved) const override;
        };
    }
}
