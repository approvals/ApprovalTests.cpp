#include "ApprovalTests/utilities/SystemUtils.h"
#include "EnvironmentVariableReporter.h"
#include "DiffReporter.h"
#include "ClipboardReporter.h"
#include "ReporterFactory.h"

namespace ApprovalTests
{
    EnvironmentVariableReporter::EnvironmentVariableReporter()
        : defaultIfNotFound_(std::make_shared<ApprovalTests::DiffReporter>())
    {
    }

    EnvironmentVariableReporter::EnvironmentVariableReporter(
        std::shared_ptr<Reporter> defaultIfNotFound)
        : defaultIfNotFound_(defaultIfNotFound)
    {
    }

    bool EnvironmentVariableReporter::report(std::string received,
                                             std::string approved) const
    {
        // Get the env var
        const auto envVar = SystemUtils::safeGetEnv("APPROVAL_TESTS_USE_REPORTER");
        if (!envVar.empty())
        {
            ReporterFactory factory;
            auto reporter = factory.createReporter(envVar);

            if (reporter)
            {
                return reporter->report(received, approved);
            }
        }
        // Or return false
        return defaultIfNotFound_->report(received, approved);
    }
}
