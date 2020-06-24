#include "ApprovalTests/reporters/DefaultReporterDisposer.h"

namespace ApprovalTests
{
    DefaultReporterDisposer::DefaultReporterDisposer(
        const std::shared_ptr<Reporter>& reporter)
    {
        previous_result = DefaultReporterFactory::getDefaultReporter();
        DefaultReporterFactory::setDefaultReporter(reporter);
    }

    DefaultReporterDisposer::~DefaultReporterDisposer()
    {
        DefaultReporterFactory::setDefaultReporter(previous_result);
    }
}
