#include "../ApprovalTests/Catch2Approvals.h"

using namespace std;

TEST_CASE("Reporters Launch Command") {
    TestReporter m(true);
    bool result = m.Report("r.txt", "a.txt");
    REQUIRE(m.launcher.ReceivedCommand() == "fake r.txt a.txt ");
    REQUIRE(true == result);
}

TEST_CASE("FirstWorkingReporter") {
    TestReporter* m1 = new TestReporter(false);
    TestReporter* m2 = new TestReporter(true);
    TestReporter* m3 = new TestReporter(true);
    FirstWorkingReporter reporter({m1, m2, m3});
    bool result = reporter.Report("r.txt", "a.txt");
    REQUIRE(m2->launcher.ReceivedCommand() == "fake r.txt a.txt ");
    REQUIRE(m3->launcher.ReceivedCommand() == "");
    REQUIRE(true == result);
}

TEST_CASE("Reporters Report Failure Status") {
    GenericDiffReporter m("this_does_not_exist");
    bool result = m.Report("r.txt", "a.txt");
    REQUIRE(false == result);
}

TEST_CASE("Reporters Report Success Status") {
    std::string knownCommand = SystemUtils::isWindowsOs() ? "C:\\Windows\\System32\\user.exe" : "echo";
    GenericDiffReporter m(knownCommand);
    bool result = m.Report("r.txt", "a.txt");
    REQUIRE(true == result);
}

TEST_CASE("CommandLauncher can detect missing file") {
    REQUIRE(false == SystemLauncher().exists("this_file_does_not_exist.txxxxxt"));
}

