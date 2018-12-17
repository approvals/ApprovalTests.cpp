#ifndef APPROVALTESTS_CPP_COMMANDLINEREPORTER_H
#define APPROVALTESTS_CPP_COMMANDLINEREPORTER_H

#include "Reporter.h"
#include "../SystemUtils.h"


#include <string>
#include <iostream>

class ClipboardReporter : public Reporter {
public:
    static std::string getCommandLineFor(std::string received, std::string approved, bool isWindows)
    {
        if (isWindows) {
            return std::string("move /Y ") + "\"" + received + "\" \"" + approved + "\"";
        } else {
            return std::string("mv ") + "\"" + received + "\" \"" + approved + "\"";
        }
    }

    virtual bool Report(std::string received, std::string approved) const override
    {
        copyToClipboard(getCommandLineFor(received, approved, SystemUtils::isWindowsOs()));
		return true;
    }

    void copyToClipboard(const std::string& newClipboard) const {
        const std::string clipboardCommand = SystemUtils::isWindowsOs() ? "clip" : "pbclip";
        auto cmd = std::string("echo ") + newClipboard + " | " + clipboardCommand;
		system(cmd.c_str());
    }
};

#endif //APPROVALTESTS_CPP_COMMANDLINEREPORTER_H
