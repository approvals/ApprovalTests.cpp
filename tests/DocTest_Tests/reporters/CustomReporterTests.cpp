#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/writers/StringWriter.h"
#include "ApprovalTests/reporters/CustomReporter.h"

using namespace ApprovalTests;

TEST_CASE("YouCanUseAWriter")
{
    // begin-snippet: use_custom_writer
    // end-snippet

    //    auto path = "/Applications/Sublime Merge.app/Contents/SharedSupport/bin/smerge";
    auto path = "/Applications/Araxis Merge.app/Contents/Utilities/compare";
    auto arguments = "mergetool --no-wait {received} {approved} -o {approved}";
    auto reporter = CustomReporter::create(path, arguments);

    //    Approvals::verify("apple sauce", *reporter);
}
