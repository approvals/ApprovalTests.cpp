#pragma once

#include "ApprovalTests/reporters/GenericDiffReporter.h"
#include "ApprovalTests/reporters/FirstWorkingReporter.h"

namespace ApprovalTests
{
    namespace Linux
    {
        class SublimeMergeSnapReporter : public GenericDiffReporter
        {
        public:
            SublimeMergeSnapReporter();
        };

        class SublimeMergeFlatpakReporter : public GenericDiffReporter
        {
        public:
            SublimeMergeFlatpakReporter();
        };

        class SublimeMergeRepositoryPackageReporter : public GenericDiffReporter
        {
        public:
            SublimeMergeRepositoryPackageReporter();
        };

        class SublimeMergeDirectDownloadReporter : public GenericDiffReporter
        {
        public:
            SublimeMergeDirectDownloadReporter();
        };

        class SublimeMergeReporter : public FirstWorkingReporter
        {
        public:
            SublimeMergeReporter();
        };

        class KDiff3Reporter : public GenericDiffReporter
        {
        public:
            KDiff3Reporter();
        };

        class MeldReporter : public GenericDiffReporter
        {
        public:
            MeldReporter();
        };

        class BeyondCompareReporter : public GenericDiffReporter
        {
        public:
            BeyondCompareReporter();
        };

        class LinuxDiffReporter : public FirstWorkingReporter
        {
        public:
            LinuxDiffReporter();
        };
    }
}
