#include "../ApprovalTests/Catch2Approvals.h"

using namespace std;

TEST_CASE("Reporters Launch Command") {
    TestReporter m;
    m.Report("r.txt", "a.txt");
    REQUIRE(m.launcher.ReceivedCommand() == "fake r.txt a.txt ");
}

