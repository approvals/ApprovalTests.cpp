#ifndef APPROVALTESTS_CPP_CIBUILDONLYREPORTER_H
#define APPROVALTESTS_CPP_CIBUILDONLYREPORTER_H

#include "ApprovalTests/core/Reporter.h"
#include "ApprovalTests/utilities/SystemUtils.h"
#include "ApprovalTests/reporters/QuietReporter.h"

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
        explicit CIBuildOnlyReporter(std::shared_ptr<Reporter> reporter = std::make_shared<QuietReporter>())
            : m_reporter(reporter)
        {
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
            /*
            auto Travis = {"CI", "TRAVIS", "CONTINUOUS_INTEGRATION"}; // https://docs.travis-ci.com/user/environment-variables/#default-environment-variables
            auto AppVeyor = {"CI", "APPVEYOR"}; // https://www.appveyor.com/docs/environment-variables/
            auto TeamCity = {"TEAMCITY_VERSION"}; // https://confluence.jetbrains.com/display/TCD18/Predefined+Build+Parameters
            auto environmentVariablesForCI = combine({
                // begin-snippet: supported_ci_systems
                Travis,
                AppVeyor,
                TeamCity
                // end-snippet
            });
             */
            auto environmentVariablesForCI = {
                    // begin-snippet: supported_ci_env_vars
                    "CI",
                    "CONTINUOUS_INTEGRATION",
                    "TEAMCITY_VERSION"
                    // end-snippet
            };
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
