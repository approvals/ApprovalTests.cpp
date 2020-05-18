#include "doctest/doctest.h"
#include <string>
#include <vector>
#include <fmt/ranges.h>
// begin-snippet: fmt_set_as_default
#define APPROVAL_TESTS_DEFAULT_STREAM_CONVERTER FmtToString
// end-snippet
#include "ApprovalTests/integrations/fmt/FmtApprovals.h"

using namespace ApprovalTests;

TEST_CASE("UsingFmtAsDefault")
{
    std::vector<int> numbers = {1, 2, 3};
    Approvals::verify(numbers);
}
