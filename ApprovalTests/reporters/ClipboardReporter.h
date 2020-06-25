#pragma once

#include "ApprovalTests/core/Reporter.h"

#include <string>

namespace ApprovalTests
{
    class ClipboardReporter : public Reporter
    {
    public:
        static std::string getCommandLineFor(const std::string& received,
                                             const std::string& approved,
                                             bool isWindows);

        virtual bool report(std::string received, std::string approved) const override;

        static void copyToClipboard(const std::string& newClipboard);
    };
}
