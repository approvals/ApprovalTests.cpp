#ifndef CATCHPLAYGROUND_QUIETREPORTER_H
#define CATCHPLAYGROUND_QUIETREPORTER_H

#include "Reporter.h"
#include <memory>
#include <vector>

// A reporter that does nothing. Failing tests will still fail, but nothing will be launched.
class QuietReporter : public Reporter
{
public:
    bool Report(std::string received, std::string approved) const override
    {
        return true;
    }
};

#endif //CATCHPLAYGROUND_QUIETREPORTER_H
