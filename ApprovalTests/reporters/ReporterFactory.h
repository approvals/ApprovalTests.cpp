#pragma once

#include "ApprovalTests/core/Reporter.h"

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace ApprovalTests
{
    class ReporterFactory
    {
    public:
        std::vector<std::string> allSupportedReporterNames(const std::string& osPrefix);

        std::unique_ptr<Reporter> createReporter(const std::string& reporterName) const;

    private:
        std::map<std::string, std::function<std::unique_ptr<Reporter>()>> createMap() const;
    };
}
