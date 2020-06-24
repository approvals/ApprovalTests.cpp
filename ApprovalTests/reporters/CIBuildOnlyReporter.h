#pragma once

#include "ApprovalTests/core/Reporter.h"
#include "ApprovalTests/reporters/TextDiffReporter.h"

#include <memory>

namespace ApprovalTests
{
    // A reporter which uses the supplied reporter, if called on a supported Continuous Integration system
    class CIBuildOnlyReporter : public Reporter
    {
    private:
        std::shared_ptr<Reporter> m_reporter;

    public:
        explicit CIBuildOnlyReporter(
            std::shared_ptr<Reporter> reporter = std::make_shared<TextDiffReporter>());

        bool report(std::string received, std::string approved) const override;

        static bool isRunningUnderCI();
    };
} // namespace ApprovalTests
