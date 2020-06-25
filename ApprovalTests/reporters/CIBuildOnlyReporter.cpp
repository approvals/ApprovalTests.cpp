#include "ApprovalTests/reporters/CIBuildOnlyReporter.h"
#include "ApprovalTests/utilities/SystemUtils.h"

namespace ApprovalTests
{
    CIBuildOnlyReporter::CIBuildOnlyReporter(std::shared_ptr<Reporter> reporter)
        : m_reporter(reporter)
    {
    }

    bool CIBuildOnlyReporter::report(std::string received, std::string approved) const
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

    bool CIBuildOnlyReporter::isRunningUnderCI()
    {
        /*
        auto AppVeyor = {"CI", "APPVEYOR"}; // https://www.appveyor.com/docs/environment-variables/
        auto AzurePipelines = {"TF_BUILD"}; // https://docs.microsoft.com/en-us/azure/devops/pipelines/build/variables?view=azure-devops&viewFallbackFrom=vsts&tabs=yaml
        auto GitHubActions = {"GITHUB_ACTIONS"}; // https://help.github.com/en/actions/configuring-and-managing-workflows/using-environment-variables
        auto GoCD = {"GO_SERVER_URL"}: // https://docs.gocd.org/current/faq/dev_use_current_revision_in_build.html
        auto Jenkins = {"JENKINS_URL"}: // https://wiki.jenkins.io/display/JENKINS/Building+a+software+project
        auto TeamCity = {"TEAMCITY_VERSION"}; // https://confluence.jetbrains.com/display/TCD18/Predefined+Build+Parameters
        auto Travis = {"CI", "TRAVIS", "CONTINUOUS_INTEGRATION"}; // https://docs.travis-ci.com/user/environment-variables/#default-environment-variables
        auto environmentVariablesForCI = combine({
            // begin-snippet: supported_ci_systems
            AppVeyor,
            AzurePipelines,
            GitHubActions,
            GoCD
            Jenkins,
            TeamCity,
            Travis,
            // end-snippet
        });
         */
        auto environmentVariablesForCI = {
            // begin-snippet: supported_ci_env_vars
            "CI",
            "CONTINUOUS_INTEGRATION",
            "GITHUB_ACTIONS",
            "GO_SERVER_URL",
            "JENKINS_URL",
            "TEAMCITY_VERSION",
            "TF_BUILD"
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
}
