#include "ApprovalTests/reporters/CombinationReporter.h"

namespace ApprovalTests
{
    CombinationReporter::CombinationReporter(const std::vector<Reporter*>& theReporters)
    {
        for (auto r : theReporters)
        {
            reporters.push_back(std::unique_ptr<Reporter>(r));
        }
    }

    bool CombinationReporter::report(std::string received, std::string approved) const
    {
        bool result = false;
        for (auto& r : reporters)
        {
            result |= r->report(received, approved);
        }
        return result;
    }
}
