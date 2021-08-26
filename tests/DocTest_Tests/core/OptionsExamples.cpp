#include "doctest/doctest.h"
#include "ApprovalTests/core/Options.h"
#include "ApprovalTests/Approvals.h"

TEST_CASE("Options - FileExtension Example")
{
    // begin-snippet: basic_approval_with_file_extension
    using namespace ApprovalTests;

    Approvals::verify("text to be verified",
                      Options().fileOptions().withFileExtension(".xyz"));
    // end-snippet
}
