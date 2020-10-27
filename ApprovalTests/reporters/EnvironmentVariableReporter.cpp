#include "ApprovalTests/namers/HelpMessages.h"
#include "ApprovalTests/utilities/SystemUtils.h"
#include "EnvironmentVariableReporter.h"
#include "DiffReporter.h"
#include "ReporterFactory.h"

namespace ApprovalTests
{
    bool EnvironmentVariableReporter::report(std::string received,
                                             std::string approved) const
    {
        // Get the env var
        const auto envVarName = environmentVariableName();
        const auto envVar = SystemUtils::safeGetEnv(envVarName.c_str());
        return report(envVar, received, approved);
    }

    bool EnvironmentVariableReporter::report(const std::string& envVar,
                                             const std::string& received,
                                             const std::string& approved) const
    {
        if (envVar.empty())
        {
            return false;
        }

        ReporterFactory factory;
        auto reporter = factory.createReporter(envVar);

        if (!reporter)
        {
            auto known = factory.allSupportedReporterNames();
            auto message = HelpMessages::getUnknownEnvVarReporterHelp(
                EnvironmentVariableReporter::environmentVariableName(), envVar, known);
            throw std::runtime_error(message);
        }

        return reporter->report(received, approved);
    }

    std::string EnvironmentVariableReporter::environmentVariableName()
    {
        return "APPROVAL_TESTS_USE_REPORTER";
    }
}
