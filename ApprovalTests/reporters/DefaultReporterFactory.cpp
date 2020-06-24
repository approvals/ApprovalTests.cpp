#include "ApprovalTests/reporters/DefaultReporterFactory.h"
#include "ApprovalTests/reporters/DiffReporter.h"

// begin-snippet: static_variable_sample_implementation
namespace ApprovalTests
{
    std::shared_ptr<Reporter>& DefaultReporterFactory::defaultReporter()
    {
        static std::shared_ptr<Reporter> reporter = std::make_shared<DiffReporter>();
        return reporter;
    }

    std::shared_ptr<Reporter> DefaultReporterFactory::getDefaultReporter()
    {
        return defaultReporter();
    }

    void
    DefaultReporterFactory::setDefaultReporter(const std::shared_ptr<Reporter>& reporter)
    {
        defaultReporter() = reporter;
    }
}
// end-snippet
