#ifndef REPORTER_H
#define REPORTER_H

#include "CommandLauncher.h"
#include "../FileUtils.h"
#include "../Macros.h"

class Reporter {
private:
    std::string cmd;
    CommandLauncher *l;

protected:
    Reporter(std::string command, CommandLauncher *launcher)
            : cmd(command), l(launcher) {
    }

public:
    void Report(std::string received, std::string approved) {
        FileUtils::ensureFileExists(approved);
        std::vector<std::string> fullCommand;
        fullCommand.push_back(cmd);
        fullCommand.push_back(received);
        fullCommand.push_back(approved);
        l->Launch(fullCommand);
    }
};

class MeldReporter : public Reporter {
private:
    SystemLauncher launcher;

public:
    MeldReporter() : Reporter("/Applications/DiffMerge.app/Contents/MacOS/DiffMerge", &launcher) {};
};

class TestReporter : public Reporter {
public:
    DoNothingLauncher launcher;

    TestReporter() : Reporter("fake", &launcher) {};
};

class ReporterFactory {
private:
    ReporterFactory() {}

    ~ReporterFactory() {}

public:
    STATIC(Reporter, currentReporter, new MeldReporter())

    static Reporter &getCurrentReporter() {
        return currentReporter();
    }



    template<typename ReporterType>
    static ReporterType &UseReporter() {
        delete &getCurrentReporter();
        ReporterType *t = new ReporterType();
        return currentReporter(t);
    }
};

#endif
