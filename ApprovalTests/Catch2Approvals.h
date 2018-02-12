
#ifndef CATCHPLAYGROUND_CATCH2APPROVALS_H_H
#define CATCHPLAYGROUND_CATCH2APPROVALS_H_H
#include "ApprovalTests.h"

// <SingleHpp unalterable>
#ifdef APPROVALS_CATCH
#define CATCH_CONFIG_MAIN
#endif

#include "Catch.hpp"
// </SingleHpp>

using std::string;

#ifdef APPROVALS_CATCH

struct Catch2ApprovalListener : Catch::TestEventListenerBase {
    using TestEventListenerBase::TestEventListenerBase; // inherit constructor
    TestName currentTest;

    virtual void testCaseStarting(Catch::TestCaseInfo const &testInfo) override {
        // Perform some setup before a test case is run
        currentTest.fileName = testInfo.lineInfo.file;
        currentTest.testCase = testInfo.name;
        ApprovalNamer::currentTest(&currentTest);
    }

    virtual void testCaseEnded(Catch::TestCaseStats const &testCaseStats) override {
        while (!currentTest.sections.empty()) {
            currentTest.sections.pop_back();
        }
    }

    virtual void sectionStarting(Catch::SectionInfo const &sectionInfo) override {
        currentTest.sections.push_back(sectionInfo.name);
    }

    virtual void sectionEnded(Catch::SectionStats const &sectionStats) override {
        currentTest.sections.pop_back();
    }
};

CATCH_REGISTER_LISTENER(Catch2ApprovalListener)

#endif
#endif //CATCHPLAYGROUND_CATCH2APPROVALS_H_H
