#include "ApprovalTests/reporters/FrontLoadedReporterDisposer.h"

namespace ApprovalTests
{
    FrontLoadedReporterDisposer::FrontLoadedReporterDisposer(
        const std::shared_ptr<Reporter>& reporter)
    {
        previous_result = FrontLoadedReporterFactory::getFrontLoadedReporter();
        FrontLoadedReporterFactory::setFrontLoadedReporter(reporter);
    }

    FrontLoadedReporterDisposer::~FrontLoadedReporterDisposer()
    {
        FrontLoadedReporterFactory::setFrontLoadedReporter(previous_result);
    }
}
