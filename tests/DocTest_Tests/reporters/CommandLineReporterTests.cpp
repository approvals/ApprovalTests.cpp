#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/writers/StringWriter.h"
#include "ApprovalTests/reporters/CustomReporter.h"

using namespace ApprovalTests;

TEST_CASE("Test Command Lines")
{
    std::stringstream stream;
    SystemUtils::debugCommandLines().isTest = true;
    auto reporter = Mac::BeyondCompareReporter();
    reporter.report("a.txt", "b.txt");
    stream << "BeyondCompareReporter => "
           << SystemUtils::debugCommandLines().lastCommand << '\n';
    SystemUtils::debugCommandLines().isTest = false;
    Approvals::verify(stream.str());
}
