#include "doctest.h"
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
    Approvals::verifyWithExtension("<h1>hello world</h1>", ".html");
    // end-snippet
}

TEST_CASE("YouCanSpecifyYourFileExtensionWithToString")
{
    Approvals::verifyWithExtension(1337, ".csv");
}

TEST_CASE("YouCanSpecifyYourFileExtensionWithFormatter")
{
    Approvals::verifyWithExtension(
        1337,
        [](auto value, auto& os) { os << "**value:** " << value; },
        ".md");
}
