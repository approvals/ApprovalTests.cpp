// begin-snippet: doctest_main
// main.cpp:
#define APPROVALS_DOCTEST // This tells Approval Tests to provide a main() - only do this in one cpp file
#include "ApprovalTests.hpp"
// end-snippet

using namespace ApprovalTests;

#include "core/Reporter.h"
#include "utilities/FileUtils.h"
#include "reporters/TextDiffReporter.h"

#include <iostream>

namespace ApprovalTests
{
    // A reporter which uses doctest CHECK statement to check the output
    class DocTestReporter : public Reporter
    {
    public:
        bool report(std::string received, std::string approved) const override
        {
            const auto receivedText =
                FileUtils::readFileReturnEmptyIfMissing(received);
            const auto approvedText =
                FileUtils::readFileReturnEmptyIfMissing(approved);
            // By using CHECK instead of REQUIRE, program flow continues - Catch does not throw an exception
            // Note that ApprovalTests will later throw an exception though.
            std::cout << "Checking content of files:" << std::endl;
            std::cout << "received: " << received << std::endl;
            std::cout
                << "********************************************************\n"
                << receivedText << std::endl;
            std::cout
                << "********************************************************\n"
                << std::endl;
            std::cout << "approved: " << approved << std::endl;
            std::cout
                << "********************************************************\n"
                << approvedText << std::endl;
            std::cout
                << "********************************************************\n"
                << std::endl;
            //            CHECK(receivedText == approvedText);
            return true;
        }
    };
} // namespace ApprovalTests

auto ciReporterDisposer = CIBuildOnlyReporterUtils::useAsFrontLoadedReporter(
    std::make_shared<TextDiffReporter>());

auto directory = Approvals::useApprovalsSubdirectory("approval_tests");
