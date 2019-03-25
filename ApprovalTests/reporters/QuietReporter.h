#ifndef APPROVALTESTS_CPP_QUIETREPORTER_H
#define APPROVALTESTS_CPP_QUIETREPORTER_H

#include "Reporter.h"
#include <memory>
#include <vector>

// A reporter that does nothing. Failing tests will still fail, but nothing will be launched.
class QuietReporter : public Reporter
{
public:
    bool report(std::string received, std::string approved) const override
    {
        return true;
    }
};

#endif //APPROVALTESTS_CPP_QUIETREPORTER_H
