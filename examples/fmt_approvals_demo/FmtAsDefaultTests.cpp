#include "doctest/doctest.h"
#include <string>
#include <vector>
#include <fmt/ranges.h>

#include "FmtAsDefault.h"
#include "ApprovalTests/integrations/fmt/FmtApprovals.h"

using namespace ApprovalTests;

TEST_CASE("UsingFmtAsDefault")
{
    std::vector<int> numbers = {1, 2, 3};
    Approvals::verify(numbers);
}
