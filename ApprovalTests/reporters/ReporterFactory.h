#pragma once

#include "ApprovalTests/core/Reporter.h"

#include <memory>
#include <string>

namespace ApprovalTests
{
    class ReporterFactory
    {
    public:
        std::unique_ptr<Reporter> createReporter(const std::string& reporterName);
    };
}
