#ifndef APPROVALTESTS_CPP_COMBINATIONREPORTER_H
#define APPROVALTESTS_CPP_COMBINATIONREPORTER_H

#include "ApprovalTests/core/Reporter.h"
#include <memory>
#include <vector>

namespace ApprovalTests {
class CombinationReporter : public Reporter
{
private:
    std::vector< std::unique_ptr<Reporter> > reporters;
public:
    // Note that CombinationReporter takes ownership of the given Reporter objects
    CombinationReporter(std::vector<Reporter*> theReporters)
    {
        for(auto r : theReporters)
        {
            reporters.push_back(std::unique_ptr<Reporter>(r));
        }
    }

    bool report(std::string received, std::string approved) const override
    {
        bool result = false;
        for(auto& r : reporters)
        {
            result |= r->report(received, approved);
        }
        return result;
    }
};
}

#endif //APPROVALTESTS_CPP_COMBINATIONREPORTER_H
