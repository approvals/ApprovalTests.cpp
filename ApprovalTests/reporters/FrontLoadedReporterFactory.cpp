#include "ApprovalTests/reporters/FrontLoadedReporterFactory.h"

namespace ApprovalTests
{
    std::shared_ptr<Reporter>& FrontLoadedReporterFactory::frontLoadedReporter()
    {
        static std::shared_ptr<Reporter> reporter =
            std::make_shared<DefaultFrontLoadedReporter>();
        return reporter;
    }

    std::shared_ptr<Reporter> FrontLoadedReporterFactory::getFrontLoadedReporter()
    {
        return frontLoadedReporter();
    }

    void FrontLoadedReporterFactory::setFrontLoadedReporter(
        const std::shared_ptr<Reporter>& reporter)
    {
        frontLoadedReporter() = reporter;
    }
}
