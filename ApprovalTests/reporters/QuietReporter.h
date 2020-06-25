#pragma once

#include "ApprovalTests/core/Reporter.h"

namespace ApprovalTests
{
    // A reporter that does nothing. Failing tests will still fail, but nothing will be launched.
    class QuietReporter : public Reporter
    {
    public:
        bool report(std::string /*received*/, std::string /*approved*/) const override;
    };
}
