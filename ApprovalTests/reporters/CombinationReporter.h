#ifndef CATCHPLAYGROUND_COMBINATIONREPORTER_H
#define CATCHPLAYGROUND_COMBINATIONREPORTER_H

#include "Reporter.h"
#include <memory>
#include <vector>

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

#endif //CATCHPLAYGROUND_COMBINATIONREPORTER_H
