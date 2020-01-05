
#ifndef APPROVALTESTS_CPP_CATCH2APPROVALS_H
#define APPROVALTESTS_CPP_CATCH2APPROVALS_H

#include "ApprovalTests/namers/ApprovalTestNamer.h"

// <SingleHpp unalterable>
#if defined(APPROVALS_CATCH_EXISTING_MAIN)
#define APPROVALS_CATCH
#define CATCH_CONFIG_RUNNER
#elif defined(APPROVALS_CATCH)
#define CATCH_CONFIG_MAIN
#endif

#ifdef APPROVALS_CATCH
// begin-snippet: required_header_for_catch
#include <catch2/catch.hpp>
// end-snippet

//namespace ApprovalTests {
struct Catch2ApprovalListener : Catch::TestEventListenerBase
{
    ApprovalTests::TestName currentTest;
    using TestEventListenerBase::
        TestEventListenerBase; // This using allows us to use all base-class constructors
    virtual void testCaseStarting(Catch::TestCaseInfo const& testInfo) override
    {

        currentTest.setFileName(testInfo.lineInfo.file);
        ApprovalTests::ApprovalTestNamer::currentTest(&currentTest);
    }

    virtual void
    testCaseEnded(Catch::TestCaseStats const& /*testCaseStats*/) override
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

    virtual void
    sectionEnded(Catch::SectionStats const& /*sectionStats*/) override
    {
        currentTest.sections.pop_back();
    }
};
//}
CATCH_REGISTER_LISTENER(Catch2ApprovalListener)

#endif
#ifdef TEST_COMMIT_REVERT_CATCH

//namespace ApprovalTests {
struct Catch2TestCommitRevert : Catch::TestEventListenerBase
{
    using TestEventListenerBase::
        TestEventListenerBase; // This using allows us to use all base-class constructors
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
// </SingleHpp>
#endif //APPROVALTESTS_CPP_CATCH2APPROVALS_H
