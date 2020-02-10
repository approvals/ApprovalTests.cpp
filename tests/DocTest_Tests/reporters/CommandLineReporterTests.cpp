#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/writers/StringWriter.h"
#include "ApprovalTests/reporters/CustomReporter.h"

using namespace ApprovalTests;

TEST_CASE("Test Command Lines")
{
    SystemUtils::debugCommandLines().isTest = true;
    auto reporter = Mac::BeyondCompareReporter();
    reporter.report("a.txt", "b.txt");
    std::string output = "BeyondCompareReporter => " +
                         SystemUtils::debugCommandLines().lastCommand;
    SystemUtils::debugCommandLines().isTest = false;
    Approvals::verify(output);
}
