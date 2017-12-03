#ifndef REPORTER_H
#define REPORTER_H

#include "CommandLauncher.h"
#include "../FileUtils.h"
#include "../Macros.h"

class Reporter {
public:
    virtual bool Report(std::string received, std::string approved) = 0;
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
    bool Report(std::string received, std::string approved) override {
        FileUtils::ensureFileExists(approved);
        std::vector<std::string> fullCommand;
        fullCommand.push_back(cmd);
        fullCommand.push_back(received);
        fullCommand.push_back(approved);
        return l->Launch(fullCommand);
    }
};

class GenericDiffReporter : public CommandReporter {
private:
    SystemLauncher launcher;

public:
    GenericDiffReporter(const std::string& program) : CommandReporter(program, &launcher) {};
};
class MeldReporter : public GenericDiffReporter {
public:
    MeldReporter() : GenericDiffReporter("meld") {};
};

class DiffMerge : public GenericDiffReporter {
public:
    DiffMerge() : GenericDiffReporter("/Applications/DiffMerge.app/Contents/MacOS/DiffMerge") {};
};

class TestReporter : public CommandReporter {
public:
    DoNothingLauncher launcher;

    TestReporter(bool working = true) : CommandReporter("fake", &launcher) {
        launcher.working = working;
    };
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
