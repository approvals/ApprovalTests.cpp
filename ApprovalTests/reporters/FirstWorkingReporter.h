#ifndef CATCHPLAYGROUND_FIRSTWORKINGREPORTER_H
#define CATCHPLAYGROUND_FIRSTWORKINGREPORTER_H

#include "Reporter.h"

class FirstWorkingReporter : public Reporter
{
private:
    std::vector<Reporter*> reporters;
public:
    FirstWorkingReporter(std::vector<Reporter*> theReporters) : reporters(theReporters)
    {
    }

    bool Report(std::string received, std::string approved) const override
    {
        for(auto r : reporters)
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
