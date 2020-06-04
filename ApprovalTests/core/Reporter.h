#pragma once

#include <string>

// Force the include with Version information to appear at the start
// of the release single-header.
#include "ApprovalTestsVersion.h"

namespace ApprovalTests
{
    class Reporter
    {
    public:
        virtual ~Reporter() = default;
        virtual bool report(std::string received, std::string approved) const = 0;
    };
}
