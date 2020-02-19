#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/writers/StringWriter.h"
#include "ApprovalTests/reporters/CustomReporter.h"

using namespace ApprovalTests;

TEST_CASE("Creating Custom Reporters")
{
    // begin-snippet: use_custom_reporter
    const auto path =
        "/Applications/Sublime Merge.app/Contents/SharedSupport/bin/smerge";
    const auto arguments = "mergetool --no-wait {Received} {Approved} -o {Approved}";
    const auto reporter = CustomReporter::create(path, arguments);
    // end-snippet

    reporter->useCygwinConversions(false);
    reporter->launcher.invokeForWindows(false);
    Approvals::verify(
        reporter->getCommandLine("test.received.txt", "test.approved.txt"));
}

TEST_CASE("Demo Windows")
{
    // begin-snippet: use_custom_windows_reporter
    const auto path = "{ProgramFiles}Beyond Compare 4\\BCompare.exe";
    auto reporter = CustomReporter::create(path);
    // end-snippet
}

TEST_CASE("Can construct a CustomReporter from const std::string arguments")
{
    const std::string program = "diff";
    const std::string arguments = DiffInfo::getDefaultArguments();
    auto reporter = CustomReporter::create(program, arguments);
}
