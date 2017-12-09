#ifndef CATCHPLAYGROUND_FIRSTWORKINGREPORTER_H
#define CATCHPLAYGROUND_FIRSTWORKINGREPORTER_H

#include "Reporter.h"
#include <memory>

class FirstWorkingReporter : public Reporter
{
private:
    std::vector< std::unique_ptr<Reporter> > reporters;
public:
    // Note that FirstWorkingReporter takes ownership of the given Reporter objects
    FirstWorkingReporter(std::vector<Reporter*> theReporters)
    {
        for(auto r : theReporters)
        {
            reporters.push_back(std::unique_ptr<Reporter>(r));
        }
    }

    bool Report(std::string received, std::string approved) const override
    {
        for(auto& r : reporters)
        {
            if (r->Report(received, approved))
            {
                return true;
            }
        }
        return false;
    }
};

#endif //CATCHPLAYGROUND_FIRSTWORKINGREPORTER_H
