#pragma once

#include "ApprovalTests/core/Reporter.h"
#include "DefaultFrontLoadedReporter.h"

#include <memory>

namespace ApprovalTests
{
    //! Implementation detail of Approvals::useAsFrontLoadedReporter()
    class FrontLoadedReporterFactory
    {
        static std::shared_ptr<Reporter>& frontLoadedReporter()
        {
            static std::shared_ptr<Reporter> reporter =
                std::make_shared<DefaultFrontLoadedReporter>();
            return reporter;
        }

    public:
        static std::shared_ptr<Reporter> getFrontLoadedReporter()
        {
            return frontLoadedReporter();
        }

        static void setFrontLoadedReporter(const std::shared_ptr<Reporter>& reporter)
        {
            frontLoadedReporter() = reporter;
        }
    };
}
