#include "ApprovalUtils.h"

#include <ostream>

namespace ApprovalTests
{
    void ApprovalUtils::writeHeader(std::ostream& stream, const std::string& header)
    {
        if (!header.empty())
        {
            stream << header << "\n\n\n";
        }
    }
}
