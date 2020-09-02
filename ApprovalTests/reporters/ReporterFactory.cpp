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
    map[#name] = []() { return std::unique_ptr<Reporter>(new name); };

namespace ApprovalTests
{
    std::unique_ptr<Reporter>
    ReporterFactory::createReporter(const std::string& reporterName)
    {
        std::map<std::string, std::function<std::unique_ptr<Reporter>()>> map;

        APPROVAL_TESTS_REGISTER_REPORTER(AutoApproveIfMissingReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(AutoApproveReporter);
        // APPROVAL_TESTS_REGISTER_REPORTER(BlockingReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(CIBuildOnlyReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(ClipboardReporter);
        // APPROVAL_TESTS_REGISTER_REPORTER(CombinationReporter);
        // APPROVAL_TESTS_REGISTER_REPORTER(CommandReporter);
        // APPROVAL_TESTS_REGISTER_REPORTER(CustomReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(DefaultFrontLoadedReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(DefaultReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(DiffReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(EnvironmentVariableReporter);
        // APPROVAL_TESTS_REGISTER_REPORTER(FirstWorkingReporter);
        // APPROVAL_TESTS_REGISTER_REPORTER(FrontLoadedReporterDisposer);
        // APPROVAL_TESTS_REGISTER_REPORTER(GenericDiffReporter);
        // APPROVAL_TESTS_REGISTER_REPORTER(LinuxReporters);
        // APPROVAL_TESTS_REGISTER_REPORTER(MacReporters);
        APPROVAL_TESTS_REGISTER_REPORTER(QuietReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(TextDiffReporter);
        // APPROVAL_TESTS_REGISTER_REPORTER(WindowsReporters);

        auto iter = map.find(reporterName);
        if (iter != map.end())
        {
            return iter->second();
        }

        return std::unique_ptr<Reporter>();
    }
}
