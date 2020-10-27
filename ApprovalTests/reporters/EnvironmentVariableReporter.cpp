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
        const auto envVar = SystemUtils::safeGetEnv("APPROVAL_TESTS_USE_REPORTER");
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

        if (reporter)
        {
            return reporter->report(received, approved);
        }
        return false;
    }
}
