#include "doctest/doctest.h"
#include <vector>

// begin-snippet: fmt_includes
#include <fmt/ranges.h>
// end-snippet

#include "ApprovalTests/integrations/fmt/FmtApprovals.h"

TEST_CASE("FmtContainers")
{
    // begin-snippet: fmt_approvals
    std::vector<int> numbers = {1, 2, 3};
    ApprovalTests::FmtApprovals::verify(numbers);
    // end-snippet
}
