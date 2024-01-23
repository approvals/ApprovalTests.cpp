
#pragma once

#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/integrations/FrameworkIntegrations.h"

#if defined(APPROVALS_CATCH_EXISTING_MAIN)
#define APPROVALS_CATCH
#define CATCH_CONFIG_RUNNER
#elif defined(APPROVALS_CATCH)
#define CATCH_CONFIG_MAIN
#endif

#ifdef APPROVALS_CATCH2_V3
#define APPROVAL_TESTS_INCLUDE_CPPS

#include <catch2/catch_all.hpp>

//namespace ApprovalTests {
struct Catch2ApprovalListener : Catch::EventListenerBase
{
    ApprovalTests::TestName currentTest;
    using EventListenerBase::
        EventListenerBase; // This using allows us to use all base-class constructors
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
