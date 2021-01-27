#pragma once

#include <iosfwd>
#include <string>

namespace ApprovalTests
{
    class ApprovalUtils
    {
    public:
        static void writeHeader(std::ostream& stream, const std::string& header);
    };
}
