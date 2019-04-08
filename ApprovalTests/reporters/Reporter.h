#ifndef APPROVALTESTS_CPP_REPORTER_H
#define APPROVALTESTS_CPP_REPORTER_H

#include <string>

// Reporters are called on test failure
class Reporter {
public:
    virtual ~Reporter() = default;
    virtual bool report(std::string received, std::string approved) const = 0;
};

#endif
