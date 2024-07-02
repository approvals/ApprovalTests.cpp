#pragma once

#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/integrations/FrameworkIntegrations.h"

#if defined(APPROVALS_CATCH2_V3) || defined(APPROVALS_CATCH2_V3_AMALGAMATED)
#define APPROVAL_TESTS_INCLUDE_CPPS

#ifdef APPROVALS_CATCH2_V3_AMALGAMATED
// begin-snippet: required_header_for_catch_2_v3_amalgamated
#include "catch_amalgamated.hpp"
// end-snippet
#else
// begin-snippet: required_header_for_catch_2_v3
#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>
#include <catch2/catch_test_case_info.hpp>
// end-snippet
#endif

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
