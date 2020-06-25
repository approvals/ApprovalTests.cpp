#pragma once

#include "ApprovalTests/core/Reporter.h"
#include <memory>
#include <vector>

namespace ApprovalTests
{
    class CombinationReporter : public Reporter
    {
    private:
        std::vector<std::unique_ptr<Reporter>> reporters;

    public:
        // Note that CombinationReporter takes ownership of the given Reporter objects
        explicit CombinationReporter(const std::vector<Reporter*>& theReporters);

        bool report(std::string received, std::string approved) const override;
    };
}
