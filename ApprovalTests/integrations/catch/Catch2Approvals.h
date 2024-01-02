
#pragma once

#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/integrations/FrameworkIntegrations.h"

#include <iostream>

#if defined(APPROVALS_CATCH_EXISTING_MAIN)
#define APPROVALS_CATCH
#define CATCH_CONFIG_RUNNER
#elif defined(APPROVALS_CATCH)
#define CATCH_CONFIG_MAIN
#endif

#ifdef APPROVALS_CATCH
#define APPROVAL_TESTS_INCLUDE_CPPS

// begin-snippet: required_header_for_catch
#include "ApprovalTests/integrations/catch/Catch2Include.h"
// end-snippet

//namespace ApprovalTests {
#ifdef APPROVAL_TESTS_USE_CATCH2V3
using CatchListener = Catch::EventListenerBase;
#else
using CatchListener = Catch::TestEventListenerBase;
#endif

struct Catch2ApprovalListener : CatchListener
{
    ApprovalTests::TestName currentTest;
    using CatchListener::
        CatchListener; // This using allows us to use all base-class constructors
    virtual void testCaseStarting(Catch::TestCaseInfo const& testInfo) override
    {

        currentTest.setFileName(testInfo.lineInfo.file);
        ApprovalTests::FrameworkIntegrations::setCurrentTest(&currentTest);
        ApprovalTests::FrameworkIntegrations::setTestPassedNotification(
            []() { REQUIRE(true); });
    }

    virtual void testCaseEnded(Catch::TestCaseStats const& /*testCaseStats*/) override
    {
        while (!currentTest.sections.empty())
        {
            currentTest.sections.pop_back();
        }
    }

    virtual void sectionStarting(Catch::SectionInfo const& sectionInfo) override
    {
        currentTest.sections.push_back(sectionInfo.name);
    }

    virtual void sectionEnded(Catch::SectionStats const& /*sectionStats*/) override
    {
        currentTest.sections.pop_back();
    }
};
//}
CATCH_REGISTER_LISTENER(Catch2ApprovalListener)

#endif
#ifdef TEST_COMMIT_REVERT_CATCH

//namespace ApprovalTests {
struct Catch2TestCommitRevert : CatchListener
{
    using CatchListener::
        CatchListener; // This using allows us to use all base-class constructors
    virtual void testRunEnded(Catch::TestRunStats const& testRunStats) override
    {
        bool commit = testRunStats.totals.testCases.allOk();
        std::string message = "r ";
        if (commit)
        {
            std::cout << "git add -A \n";
            std::cout << "git commit -m " << message;
        }
        else
        {
            std::cout << "git clean -fd \n";
            std::cout << "git reset --hard HEAD \n";
        }
    }
};
//}
CATCH_REGISTER_LISTENER(Catch2TestCommitRevert)
#endif
