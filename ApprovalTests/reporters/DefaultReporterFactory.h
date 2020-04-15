#pragma once

#include "ApprovalTests/core/Reporter.h"
#include "DiffReporter.h"

#include <memory>

namespace ApprovalTests
{
    //! Implementation detail of Approvals::useAsDefaultReporter()
    class DefaultReporterFactory
    {
        // begin-snippet: static_variable_sample
    private:
        static std::shared_ptr<Reporter>& defaultReporter()
        {
            static std::shared_ptr<Reporter> reporter = std::make_shared<DiffReporter>();
            return reporter;
        }

    public:
        static std::shared_ptr<Reporter> getDefaultReporter()
        {
            return defaultReporter();
        }

        static void setDefaultReporter(const std::shared_ptr<Reporter>& reporter)
        {
            defaultReporter() = reporter;
        }
        // end-snippet
    };
}
