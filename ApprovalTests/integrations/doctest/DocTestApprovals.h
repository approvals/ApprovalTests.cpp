#pragma once

#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/integrations/FrameworkIntegrations.h"

#if defined(APPROVALS_DOCTEST_EXISTING_MAIN)
#define APPROVALS_DOCTEST
#define DOCTEST_CONFIG_IMPLEMENT
#elif defined(APPROVALS_DOCTEST)
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#endif

#ifdef APPROVALS_DOCTEST
#define APPROVAL_TESTS_INCLUDE_CPPS

// begin-snippet: required_header_for_doctest
#include <doctest/doctest.h>
// end-snippet

namespace ApprovalTests
{
    // anonymous namespace to prevent compiler -Wsubobject-linkage warnings
    // This is OK as this code is only compiled on main()
    namespace
    {
        struct AbstractReporter : doctest::IReporter
        {
            virtual void report_query(const doctest::QueryData&) override
            {
            }
            // called when the whole test run starts
            virtual void test_run_start() override
            {
            }

            // called when the whole test run ends (caching a pointer to the input doesn't make sense here)
            virtual void test_run_end(const doctest::TestRunStats&) override
            {
            }

            // called when a test case is started (safe to cache a pointer to the input)
            virtual void test_case_start(const doctest::TestCaseData&) override
            {
            }

#if 20305 <= DOCTEST_VERSION
            // called when a test case is reentered because of unfinished subcases (safe to cache a pointer to the input)
            virtual void test_case_reenter(const doctest::TestCaseData&) override
            {
            }
#endif

            // called when a test case has ended
            virtual void test_case_end(const doctest::CurrentTestCaseStats&) override
            {
            }

            // called when an exception is thrown from the test case (or it crashes)
            virtual void test_case_exception(const doctest::TestCaseException&) override
            {
            }

            // called whenever a subcase is entered (don't cache pointers to the input)
            virtual void subcase_start(const doctest::SubcaseSignature&) override
            {
            }

            // called whenever a subcase is exited (don't cache pointers to the input)
            virtual void subcase_end() override
            {
            }

            // called for each assert (don't cache pointers to the input)
            virtual void log_assert(const doctest::AssertData&) override
            {
            }

            // called for each message (don't cache pointers to the input)
            virtual void log_message(const doctest::MessageData&) override
            {
            }

            // called when a test case is skipped either because it doesn't pass the filters, has a skip decorator
            // or isn't in the execution range (between first and last) (safe to cache a pointer to the input)
            virtual void test_case_skipped(const doctest::TestCaseData&) override
            {
            }
        };

        struct DocTestApprovalListener : AbstractReporter
        {
            TestName currentTest;

            // constructor has to accept the ContextOptions by ref as a single argument
            explicit DocTestApprovalListener(const doctest::ContextOptions& /*in*/)
            {
            }

            std::string doctestToString(const doctest::String& string) const
            {
                return string.c_str();
            }

            std::string doctestToString(const char* string) const
            {
                return string;
            }

            void test_case_start(const doctest::TestCaseData& testInfo) override
            {
                currentTest.sections.emplace_back(testInfo.m_name);
                currentTest.setFileName(doctestToString(testInfo.m_file));
                ApprovalTests::FrameworkIntegrations::setCurrentTest(&currentTest);
                ApprovalTests::FrameworkIntegrations::setTestPassedNotification(
                    []() { REQUIRE(true); });
            }

            void test_case_end(const doctest::CurrentTestCaseStats& /*in*/) override
            {

                while (!currentTest.sections.empty())
                {
                    currentTest.sections.pop_back();
                }
            }

            void subcase_start(const doctest::SubcaseSignature& signature) override
            {
                currentTest.sections.emplace_back(doctestToString(signature.m_name));
            }

            void subcase_end() override
            {

                currentTest.sections.pop_back();
            }
        };
    }
}

REGISTER_LISTENER("approvals", 0, ApprovalTests::DocTestApprovalListener);

#endif // APPROVALS_DOCTEST
