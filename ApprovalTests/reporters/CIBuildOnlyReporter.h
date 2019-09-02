#ifndef APPROVALTESTS_CPP_CIBUILDONLYREPORTER_H
#define APPROVALTESTS_CPP_CIBUILDONLYREPORTER_H

#include "reporters/Reporter.h"
#include "SystemUtils.h"
#include "ApprovalTests/Approvals.h"

#include <vector>
#include <memory>

namespace ApprovalTests
{
    // A reporter which uses the supplied reporter, if called on a supported Continuous Integration system
    class CIBuildOnlyReporter : public Reporter
    {
    private:
        std::shared_ptr<Reporter> m_reporter;

    public:
        explicit CIBuildOnlyReporter(std::shared_ptr<Reporter> reporter)
            : m_reporter(reporter)
        {
        }

        static FrontLoadedReporterDisposer useAsFrontLoadedReporter(const std::shared_ptr<Reporter>& reporter)
        {
            return Approvals::useAsFrontLoadedReporter(
                    std::make_shared<ApprovalTests::CIBuildOnlyReporter>( reporter ));
        }

        bool report(std::string received, std::string approved) const override
        {
            if (!isRunningUnderCI())
            {
                return false;
            }
            m_reporter->report(received, approved);
            // Return true regardless of whether our report succeeded or not,
            // so that no later reporters run.
            return true;
        }

        static bool isRunningUnderCI()
        {
//            auto travis = {"CI", "TRAVIS", "CONTINUOUS_INTEGRATION"}; // https://docs.travis-ci.com/user/environment-variables/#default-environment-variables
//            auto appVeyor = {"CI", "APPVEYOR"}; // https://www.appveyor.com/docs/environment-variables/
//            auto teamCity = {"TEAMCITY_VERSION"}; // https://confluence.jetbrains.com/display/TCD18/Predefined+Build+Parameters
            auto environmentVariablesForCI = {"CI", "CONTINUOUS_INTEGRATION", "TEAMCITY_VERSION"};
            for (const auto& variable : environmentVariablesForCI)
            {
                if (!SystemUtils::safeGetEnv(variable).empty())
                {
                    return true;
                }
            }
            return false;
        }
    };
} // namespace ApprovalTests

#endif //APPROVALTESTS_CPP_CIBUILDONLYREPORTER_H
