#include "doctest/doctest.h"
#include "ApprovalTests/reporters/TextDiffReporter.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"

using namespace ApprovalTests;

TEST_CASE("Reporters Launch Command")
{
    std::stringstream output;
    TextDiffReporter r(output);
    ApprovalTestNamer namer;
    bool result = r.report(namer.getTestSourceDirectory() + "_r.txt",
                           namer.getTestSourceDirectory() + "_a.txt");
    Approvals::verify(output.str(),
                      Options().withScrubber(Scrubbers::createRegexScrubber(
                          "ed: .*reporters[/\\\\]", "ed: <Directory>/")));
    REQUIRE(true == result);
}
