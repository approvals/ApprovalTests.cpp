#ifndef REPORTER_H
#define REPORTER_H

// Reporters are called on test failure
class Reporter {
public:
    virtual ~Reporter() = default;
    virtual bool Report(std::string received, std::string approved) const = 0;
};

#endif
