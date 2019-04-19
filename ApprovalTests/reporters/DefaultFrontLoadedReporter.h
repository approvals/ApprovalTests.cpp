#ifndef APPROVALTESTS_CPP_DEFAULTFRONTLOADEDREPORTER_H
#define APPROVALTESTS_CPP_DEFAULTFRONTLOADEDREPORTER_H

#include "Reporter.h"

class DefaultFrontLoadedReporter : public Reporter
{
public:
    virtual bool report(std::string /*received*/, std::string /*approved*/) const override
    {
        return false;
    }
};

#endif //APPROVALTESTS_CPP_DEFAULTFRONTLOADEDREPORTER_H
