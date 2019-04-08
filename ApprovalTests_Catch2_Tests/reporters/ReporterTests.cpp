
#include "Catch.hpp"
#include "TestReporter.h"
#include "FakeReporter.h"
#include <ApprovalTests/reporters/FirstWorkingReporter.h>
#include <ApprovalTests/reporters/ClipboardReporter.h>
#include <ApprovalTests/reporters/CombinationReporter.h>
#include <ApprovalTests/reporters/WindowsReporters.h>
#include <ApprovalTests/Approvals.h>
#include <ApprovalTests/StringUtils.h>

using namespace std;

TEST_CASE("Reporters Launch Command") {
    TestReporter m(true);
    bool result = m.report("r.txt", "a.txt");
    REQUIRE(m.launcher.receivedCommand() == "fake r.txt a.txt ");
    REQUIRE(true == result);
}

TEST_CASE("FirstWorkingReporter") {
    TestReporter* m1 = new TestReporter(false);
    TestReporter* m2 = new TestReporter(true);
    TestReporter* m3 = new TestReporter(true);
    FirstWorkingReporter reporter({m1, m2, m3});
    bool result = reporter.report("r.txt", "a.txt");
    REQUIRE(m2->launcher.receivedCommand() == "fake r.txt a.txt ");
    REQUIRE(m3->launcher.receivedCommand() == "");
    REQUIRE(true == result);
}

TEST_CASE("Reporters Report Failure Status") {
    GenericDiffReporter m("this_does_not_exist");
    bool result = m.report("r.txt", "a.txt");
    REQUIRE(false == result);
}

TEST_CASE("Reporters Report Success Status") {
    std::string knownCommand = SystemUtils::isWindowsOs() ? "C:\\Windows\\System32\\user.exe" : "echo";
    GenericDiffReporter m(knownCommand);
    bool result = m.report("r.txt", "a.txt");
    REQUIRE(true == result);
}

TEST_CASE("CommandLauncher can detect missing file") {
    REQUIRE(false == SystemLauncher().exists("this_file_does_not_exist.txxxxxt"));
}

TEST_CASE("ClipboardReporter") {
    REQUIRE("move /Y \"a.txt\" \"b.txt\"" == ClipboardReporter::getCommandLineFor("a.txt", "b.txt", true));
    REQUIRE("mv \"a.txt\" \"b.txt\"" == ClipboardReporter::getCommandLineFor("a.txt", "b.txt", false));
}

TEST_CASE("CombinationReporter succeeds if any succeed") {
    FakeReporter* m1 = new FakeReporter(true);
    FakeReporter* m2 = new FakeReporter(true);
    CombinationReporter reporter({m1, m2});
    bool result = reporter.report("r.txt", "a.txt");
    REQUIRE(m1->called == true);
    REQUIRE(m2->called == true);
    REQUIRE(result == true);
}

TEST_CASE("CombinationReporter fails if all fail") {
    FakeReporter* m1 = new FakeReporter(false);
    FakeReporter* m2 = new FakeReporter(false);
    CombinationReporter reporter({m1, m2});
    bool result = reporter.report("r.txt", "a.txt");
    REQUIRE(m1->called == true);
    REQUIRE(m2->called == true);
    REQUIRE(result == false);
}

TEST_CASE("Launching on PC with cygwin and Araxis Merge")
{
    return; // Ignoring system test


    REQUIRE_FALSE(SystemUtils::isWindowsOs());
    auto reporter = new Windows::AraxisMergeReporter;
    auto namer = Approvals::getDefaultNamer();
    auto fullCommand = reporter->getFullCommand(
        namer->getReceivedFile(".txt"),
        namer->getApprovedFile(".txt"));
    Approvals::verifyAll(fullCommand, *reporter);
}
