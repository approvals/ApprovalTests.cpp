#include "ApprovalTests/utilities/SystemUtils.h"
#include "EnvironmentVariableReporter.h"
#include "DiffReporter.h"
#include "ClipboardReporter.h"

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
            if (envVar == "ClipboardReporter")
            {
                return ClipboardReporter().report(received, approved);
            }
            // Switch on env var names
            // Create reporter and call it - then return
        }
        // Or return false
        return defaultIfNotFound_->report(received, approved);
    }
}
