#include "ApprovalTests/reporters/QuietReporter.h"
#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/writers/StringWriter.h"

TEST_CASE("YouCanUseAWriter")
{
    using HtmlWriter = ApprovalTests::StringWriter;
    // begin-snippet: use_custom_writer
    HtmlWriter writer("<h1>hello world</h1>", ".html");
    ApprovalTests::Approvals::verify(writer);
    // end-snippet
}

TEST_CASE("YouCanSpecifyYourFileExtension")
{
    // begin-snippet: use_custom_file_extension
    ApprovalTests::Approvals::verify(
        "<h1>hello world</h1>",
        ApprovalTests::Options().fileOptions().withFileExtension(".html"));
    // end-snippet
}

TEST_CASE("YouCanSpecifyYourFileExtensionWithToString")
{
    ApprovalTests::Approvals::verify(
        1337, ApprovalTests::Options().fileOptions().withFileExtension(".csv"));
}

TEST_CASE("YouCanSpecifyYourFileExtensionWithFormatter")
{
    using namespace ApprovalTests;

    Approvals::verify(
        1337,
        [](auto value, auto& os) { os << "**value:** " << value; },
        Options().fileOptions().withFileExtension(".md"));
}

TEST_CASE("YouCanSpecifyAllOptions")
{

    ApprovalTests::Approvals::verify(
        R"({
    name: frances
    id: 05f77de3-3790-4d45-b045-def96c9cd371
}
)",
        // clang-format off
        // begin-snippet: specify_all_the_options
        ApprovalTests::Options()
            .withReporter(ApprovalTests::QuietReporter())
            .withScrubber(ApprovalTests::Scrubbers::scrubGuid)
            .fileOptions().withFileExtension(".json")
        // end-snippet
        // clang-format on
    );
}
