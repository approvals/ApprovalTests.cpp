#ifndef APPROVALTESTS_CPP_TESTREPORTER_H
#define APPROVALTESTS_CPP_TESTREPORTER_H

#include "../../ApprovalTests/reporters/GenericDiffReporter.h"

class TestReporter : public CommandReporter {
public:
    DoNothingLauncher launcher;

    TestReporter(bool working = true) : CommandReporter("fake", &launcher) {
        launcher.working = working;
    };
};
#endif //APPROVALTESTS_CPP_TESTREPORTER_H
