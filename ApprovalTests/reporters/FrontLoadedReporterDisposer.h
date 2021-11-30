#pragma once

#include "ApprovalTests/reporters/FrontLoadedReporterFactory.h"
#include "ApprovalTests/utilities/Macros.h"

namespace ApprovalTests
{
    //! Implementation detail of Approvals::useAsFrontLoadedReporter()
    class APPROVAL_TESTS_NO_DISCARD FrontLoadedReporterDisposer
    {
    private:
        std::shared_ptr<Reporter> previous_result;

    public:
        explicit FrontLoadedReporterDisposer(const std::shared_ptr<Reporter>& reporter);
        FrontLoadedReporterDisposer(const FrontLoadedReporterDisposer&) = default;

        ~FrontLoadedReporterDisposer();
    };
}
