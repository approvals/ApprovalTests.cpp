#include "../ApprovalTests/Catch2Approvals.h"

using namespace std;

TEST_CASE("Reporters Launch Command") {
    TestReporter m;
    m.Report("r.txt", "a.txt");
    REQUIRE(m.launcher.ReceivedCommand() == "fake r.txt a.txt ");
}

TEST_CASE("Reporters Report Success Status") {
    GenericDiffReporter m("this_does_not_exist");
    bool result = m.Report("r.txt", "a.txt");
    REQUIRE(false == result);
}
