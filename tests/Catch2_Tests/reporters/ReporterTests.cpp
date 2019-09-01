
#include "Catch.hpp"
#include "TestReporter.h"
#include "FakeReporter.h"
#include "ApprovalTests/reporters/FirstWorkingReporter.h"
#include "ApprovalTests/reporters/ClipboardReporter.h"
#include "ApprovalTests/reporters/CombinationReporter.h"
#include "ApprovalTests/reporters/WindowsReporters.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/utilities/StringUtils.h"
#include "ApprovalTests/core/FileApprover.h"

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
    ApprovalTests::FirstWorkingReporter reporter({m1, m2, m3});
    bool result = reporter.report("r.txt", "a.txt");
    REQUIRE(m2->launcher.receivedCommand() == "fake r.txt a.txt ");
    REQUIRE(m3->launcher.receivedCommand() == "");
    REQUIRE(true == result);
}

TEST_CASE("Reporters Report Failure Status") {
    ApprovalTests::GenericDiffReporter m("this_does_not_exist");
    bool result = m.report("r.txt", "a.txt");
    REQUIRE(false == result);
}

TEST_CASE("Reporters Report Success Status") {
    std::string knownCommand = ApprovalTests::SystemUtils::isWindowsOs() ? R"(C:\Windows\System32\help.exe)" : "echo";
    ApprovalTests::GenericDiffReporter m(knownCommand);
    bool result = m.report("r.txt", "a.txt");
    REQUIRE(true == result);
}

TEST_CASE("CommandLauncher can detect missing file") {
    REQUIRE(false == ApprovalTests::SystemLauncher().exists("this_file_does_not_exist.txxxxxt"));
}

TEST_CASE("ClipboardReporter") {
    REQUIRE("move /Y \"a.txt\" \"b.txt\"" == ApprovalTests::ClipboardReporter::getCommandLineFor("a.txt", "b.txt", true));
    REQUIRE("mv \"a.txt\" \"b.txt\"" == ApprovalTests::ClipboardReporter::getCommandLineFor("a.txt", "b.txt", false));
}

TEST_CASE("CombinationReporter succeeds if any succeed") {
    FakeReporter* m1 = new FakeReporter(true);
    FakeReporter* m2 = new FakeReporter(true);
    ApprovalTests::CombinationReporter reporter({m1, m2});
    bool result = reporter.report("r.txt", "a.txt");
    REQUIRE(m1->called == true);
    REQUIRE(m2->called == true);
    REQUIRE(result == true);
}

TEST_CASE("CombinationReporter fails if all fail") {
    FakeReporter* m1 = new FakeReporter(false);
    FakeReporter* m2 = new FakeReporter(false);
    ApprovalTests::CombinationReporter reporter({m1, m2});
    bool result = reporter.report("r.txt", "a.txt");
    REQUIRE(m1->called == true);
    REQUIRE(m2->called == true);
    REQUIRE(result == false);
}

TEST_CASE("Launching on PC with cygwin and Araxis Merge")
{
    // Keeping for manual testing when needed
    
//    REQUIRE_FALSE(SystemUtils::isWindowsOs());
//    auto reporter = new Windows::AraxisMergeReporter;
//    auto namer = Approvals::getDefaultNamer();
//    auto fullCommand = reporter->getFullCommand(
//        namer->getReceivedFile(".txt"),
//        namer->getApprovedFile(".txt"));
//    Approvals::verifyAll(fullCommand, *reporter);
}



TEST_CASE("Registering default Reporter")
{
    auto fake_reporter = std::make_shared<FakeReporter>(true);
    auto default_reporter_disposer = ApprovalTests::Approvals::useAsDefaultReporter(fake_reporter);
    {
        auto fake_reporter2 = std::make_shared<FakeReporter>(true);
        auto default_reporter_disposer2 = ApprovalTests::Approvals::useAsDefaultReporter(fake_reporter2);

        ApprovalTests::DefaultReporter r;
        r.report("r.txt", "a.txt");

        REQUIRE(fake_reporter->called == false);
        REQUIRE(fake_reporter2->called == true);
    }
    ApprovalTests::DefaultReporter r;
    r.report("r.txt", "a.txt");
    REQUIRE(fake_reporter->called == true);
}


TEST_CASE("Front Loaded Reporter Always Takes Precedence")
{
    auto front_loader = std::make_shared<FakeReporter>(true);
    auto our_reporter = std::make_shared<FakeReporter>(true);

    auto default_reporter_disposer = ApprovalTests::Approvals::useAsFrontLoadedReporter(front_loader);

    try
    {
        ApprovalTests::Approvals::verify("cucumber", *our_reporter);
    }
    catch(const std::exception&)
    {
    }

    REQUIRE(front_loader->called == true);
    REQUIRE(our_reporter->called == false);
}

TEST_CASE("Front Loaded Reporter flows through if not needed")
{
    auto front_loader = std::make_shared<FakeReporter>(false);
    auto our_reporter = std::make_shared<FakeReporter>(true);

    auto default_reporter_disposer = ApprovalTests::Approvals::useAsFrontLoadedReporter(front_loader);

    try
    {
        ApprovalTests::Approvals::verify("cucumber", *our_reporter);
    }
    catch(const std::exception&)
    {
    }

    REQUIRE(front_loader->called == true);
    REQUIRE(our_reporter->called == true);
}

TEST_CASE("Unregistering Front Loaded Reporter restores previous")
{
    auto front_loader1 = std::make_shared<FakeReporter>(true);
    auto front_loaded_reporter_disposer1 = ApprovalTests::Approvals::useAsFrontLoadedReporter(front_loader1);

    FakeReporter our_reporter1(true);

    {
        auto front_loader2 = std::make_shared<FakeReporter>(true);
        auto front_loaded_reporter_disposer2 = ApprovalTests::Approvals::useAsFrontLoadedReporter(front_loader2);

        ApprovalTests::FileApprover::reportAfterTryingFrontLoadedReporter("r.txt", "a.txt", our_reporter1);

        REQUIRE(front_loader2->called == true);
        REQUIRE(front_loader1->called == false);
        REQUIRE(our_reporter1.called == false);
    }
    ApprovalTests::FileApprover::reportAfterTryingFrontLoadedReporter("r.txt", "a.txt", our_reporter1);

    REQUIRE(front_loader1->called == true);
    REQUIRE(our_reporter1.called == false);
}

