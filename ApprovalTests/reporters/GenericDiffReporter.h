#ifndef APPROVALTESTS_CPP_GENERICDIFFREPORTER_H
#define APPROVALTESTS_CPP_GENERICDIFFREPORTER_H

#include "DiffPrograms.h"
#include "CommandReporter.h"
#include "SystemLauncher.h"

class GenericDiffReporter : public CommandReporter {
private:
    SystemLauncher launcher;

public:
    GenericDiffReporter(const std::string& program) : CommandReporter(program, &launcher) {};
    GenericDiffReporter(const DiffInfo& info) : CommandReporter(info.getProgramForOs().c_str(), &launcher) {};
};

#endif //APPROVALTESTS_CPP_GENERICDIFFREPORTER_H
