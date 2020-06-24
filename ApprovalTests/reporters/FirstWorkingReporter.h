#pragma once

#include "ApprovalTests/core/Reporter.h"
#include <memory>
#include <vector>

namespace ApprovalTests
{
    class FirstWorkingReporter : public Reporter
    {
    private:
        std::vector<std::shared_ptr<Reporter>> reporters;

    public:
        // Note that FirstWorkingReporter takes ownership of the given Reporter objects
        explicit FirstWorkingReporter(const std::vector<Reporter*>& theReporters);

        explicit FirstWorkingReporter(
            const std::vector<std::shared_ptr<Reporter>>& reporters_);

        bool report(std::string received, std::string approved) const override;
    };
}
