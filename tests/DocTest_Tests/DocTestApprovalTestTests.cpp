#include "ApprovalTests/reporters/QuietReporter.h"
#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/writers/StringWriter.h"

using namespace ApprovalTests;

TEST_CASE("YouCanUseAWriter")
{
    using HtmlWriter = StringWriter;
    // begin-snippet: use_custom_writer
    HtmlWriter writer("<h1>hello world</h1>", ".html");
    Approvals::verify(writer);
    // end-snippet
}

TEST_CASE("YouCanSpecifyYourFileExtension")
{
    // begin-snippet: use_custom_file_extension
    Approvals::verify("<h1>hello world</h1>",
                      Options().fileOptions().withFileExtension(".html"));
    // end-snippet
}

TEST_CASE("YouCanSpecifyYourFileExtensionWithToString")
{
    Approvals::verify(1337, Options().fileOptions().withFileExtension(".csv"));
}

TEST_CASE("YouCanSpecifyYourFileExtensionWithFormatter")
{
    Approvals::verify(
        1337,
        [](auto value, auto& os) { os << "**value:** " << value; },
        Options().fileOptions().withFileExtension(".md"));
}

TEST_CASE("YouCanSpecifyAllOptions")
{
    Approvals::verify(
        R"({
    name: frances
    id: 05f77de3-3790-4d45-b045-def96c9cd371
}
)",
        // begin-snippet: specify_all_the_options
        Options()
            //            .withReporter(QuietReporter())
            .withScrubber(Scrubbers::scrubGuid)
            .fileOptions()
            .withFileExtension(".json")
        // end-snippet
    );
}
