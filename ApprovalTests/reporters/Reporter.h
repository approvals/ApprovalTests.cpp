#ifndef REPORTER_H
#define REPORTER_H

#include "CommandLauncher.h"
#include "../FileUtils.h"
class Reporter {
public:
    virtual bool Report(std::string received, std::string approved) const = 0;
};

class CommandReporter : public Reporter {
private:
    std::string cmd;
    CommandLauncher *l;

protected:
    CommandReporter(std::string command, CommandLauncher *launcher)
            : cmd(command), l(launcher) {
    }

public:
    bool Report(std::string received, std::string approved) const override {
        FileUtils::ensureFileExists(approved);
        std::vector<std::string> fullCommand;
        fullCommand.push_back(cmd);
        fullCommand.push_back(received);
        fullCommand.push_back(approved);
        return l->Launch(fullCommand);
    }
};
#endif
