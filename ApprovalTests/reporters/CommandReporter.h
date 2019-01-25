#ifndef APPROVALTESTS_CPP_COMMANDREPORTER_H
#define APPROVALTESTS_CPP_COMMANDREPORTER_H

#include "CommandLauncher.h"
#include "../FileUtils.h"
#include "Reporter.h"

// Generic reporter to launch arbitrary command
class CommandReporter : public Reporter {
private:
    std::string cmd;
    CommandLauncher *l;

protected:
    CommandReporter(std::string command, CommandLauncher *launcher)
            : cmd(command), l(launcher) {
    }

public:
    bool report(std::string received, std::string approved) const override {
        FileUtils::ensureFileExists(approved);
        std::vector<std::string> fullCommand;
        fullCommand.push_back(cmd);
        fullCommand.push_back(received);
        fullCommand.push_back(approved);
        return l->launch(fullCommand);
    }
};
#endif //APPROVALTESTS_CPP_COMMANDREPORTER_H
