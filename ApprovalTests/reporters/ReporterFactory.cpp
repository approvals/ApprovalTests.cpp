#include "ReporterFactory.h"

#include "ApprovalTests/reporters/AutoApproveIfMissingReporter.h"
#include "ApprovalTests/reporters/AutoApproveReporter.h"
#include "ApprovalTests/reporters/BlockingReporter.h"
#include "ApprovalTests/reporters/CIBuildOnlyReporter.h"
#include "ApprovalTests/reporters/ClipboardReporter.h"
#include "ApprovalTests/reporters/CombinationReporter.h"
#include "ApprovalTests/reporters/CommandReporter.h"
#include "ApprovalTests/reporters/CustomReporter.h"
#include "ApprovalTests/reporters/DefaultFrontLoadedReporter.h"
#include "ApprovalTests/reporters/DefaultReporter.h"
#include "ApprovalTests/reporters/DiffReporter.h"
#include "ApprovalTests/reporters/EnvironmentVariableReporter.h"
#include "ApprovalTests/reporters/FirstWorkingReporter.h"
#include "ApprovalTests/reporters/FrontLoadedReporterDisposer.h"
#include "ApprovalTests/reporters/GenericDiffReporter.h"
#include "ApprovalTests/reporters/LinuxReporters.h"
#include "ApprovalTests/reporters/MacReporters.h"
#include "ApprovalTests/reporters/QuietReporter.h"
#include "ApprovalTests/reporters/TextDiffReporter.h"
#include "ApprovalTests/reporters/WindowsReporters.h"

#include <map>
#include <functional>

#define APPROVAL_TESTS_REGISTER_REPORTER(name)                                           \
    map[#name] = []() { return std::unique_ptr<Reporter>(new name); }

namespace ApprovalTests
{
    std::unique_ptr<Reporter>
    ReporterFactory::createReporter(const std::string& reporterName)
    {
        std::map<std::string, std::function<std::unique_ptr<Reporter>()>> map;

        APPROVAL_TESTS_REGISTER_REPORTER(AutoApproveIfMissingReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(AutoApproveReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(CIBuildOnlyReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(ClipboardReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(DefaultFrontLoadedReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(DefaultReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(DiffReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(EnvironmentVariableReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(QuietReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(TextDiffReporter);

        APPROVAL_TESTS_REGISTER_REPORTER(Linux::BeyondCompareReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(Linux::MeldReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(Linux::SublimeMergeReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(Linux::KDiff3Reporter);

        APPROVAL_TESTS_REGISTER_REPORTER(Mac::AraxisMergeReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(Mac::BeyondCompareReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(Mac::DiffMergeReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(Mac::KaleidoscopeReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(Mac::P4MergeReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(Mac::SublimeMergeReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(Mac::KDiff3Reporter);
        APPROVAL_TESTS_REGISTER_REPORTER(Mac::TkDiffReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(Mac::VisualStudioCodeReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(Mac::CLionDiffReporter);

        APPROVAL_TESTS_REGISTER_REPORTER(Windows::TortoiseDiffReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(Windows::TortoiseGitDiffReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(Windows::BeyondCompareReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(Windows::WinMergeReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(Windows::AraxisMergeReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(Windows::CodeCompareReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(Windows::SublimeMergeReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(Windows::KDiff3Reporter);
        APPROVAL_TESTS_REGISTER_REPORTER(Windows::VisualStudioCodeReporter);

        std::vector<std::string> candidateNames = {
            reporterName,
            // Allow program names to be specified without Reporter suffix
            reporterName + "Reporter"};

        for (auto& candidateName : candidateNames)
        {
            auto iter = map.find(candidateName);
            if (iter != map.end())
            {
                return iter->second();
            }
        }

        return std::unique_ptr<Reporter>();
    }
}
