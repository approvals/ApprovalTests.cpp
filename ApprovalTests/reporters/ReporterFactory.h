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
        using Reporters =
            std::map<std::string, std::function<std::unique_ptr<Reporter>()>>;

        std::vector<std::string>
        allSupportedReporterNames(const std::string& osPrefix) const;

        std::unique_ptr<Reporter> createReporter(const std::string& reporterName) const;

        std::string findReporterName(const Reporters& map,
                                     const std::string& osPrefix,
                                     const std::string& reporterName) const;

        Reporters createMap() const;
    };
}
