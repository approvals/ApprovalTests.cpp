#ifndef REPORTER_H
#define REPORTER_H

class Reporter {
public:
    virtual bool Report(std::string received, std::string approved) const = 0;
};

#endif
