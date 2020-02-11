#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/writers/StringWriter.h"
#include "ApprovalTests/reporters/CustomReporter.h"

using namespace ApprovalTests;

TEST_CASE("YouCanUseAWriter")
{
    // begin-snippet: use_custom_writer
    auto path =
        "/Applications/Sublime Merge.app/Contents/SharedSupport/bin/smerge";
    auto arguments = "mergetool --no-wait {Received} {Approved} -o {Approved}";
    auto reporter = CustomReporter::create(path, arguments);
    // end-snippet

    reporter->useCygwinConversions(false);
    reporter->launcher.invokeForWindows(false);
    Approvals::verify(reporter->getCommandLine("r.txt", "a.txt"));
}
