#pragma once

#include "ApprovalTests/core/Reporter.h"

#include <memory>
#include <iosfwd>

namespace ApprovalTests
{
    // A Reporter class that only uses text-based diff tools, with output written
    // to the console. It provides no opportunity for interactive approving
    // of files.
    // It currently has a short, hard-coded list of diffing tools.
    class TextDiffReporter : public Reporter
    {
    private:
        std::unique_ptr<Reporter> m_reporter;
        std::ostream& stream_;

    public:
        TextDiffReporter();
        explicit TextDiffReporter(std::ostream& stream);

        bool report(std::string received, std::string approved) const override;
    };
} // namespace ApprovalTests
