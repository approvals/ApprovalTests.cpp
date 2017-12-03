#include "../ApprovalTests/Catch2Approvals.h"

using namespace std;

TEST_CASE("Reporters Launch Command") {
    TestReporter m(true);
    bool result = m.Report("r.txt", "a.txt");
    REQUIRE(m.launcher.ReceivedCommand() == "fake r.txt a.txt ");
    REQUIRE(true == result);
}

TEST_CASE("FirstWorkingReporter") {
    TestReporter m1(false);
    TestReporter m2(true);
    TestReporter m3(true);
    FirstWorkingReporter reporter({&m1, &m2, &m3});
    bool result = reporter.Report("r.txt", "a.txt");
    REQUIRE(m2.launcher.ReceivedCommand() == "fake r.txt a.txt ");
    REQUIRE(m3.launcher.ReceivedCommand() == "");
    REQUIRE(true == result);
}

TEST_CASE("Reporters Report Success Status") {
    GenericDiffReporter m("this_does_not_exist");
    bool result = m.Report("r.txt", "a.txt");
    REQUIRE(false == result);
}
