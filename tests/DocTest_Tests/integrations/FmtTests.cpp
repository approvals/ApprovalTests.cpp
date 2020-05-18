#include "doctest/doctest.h"
#include <string>
#include <vector>
#include <fmt/ranges.h>
#include <fmt/ostream.h>
#include <fmt/format.h>

#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/integrations/fmt/FmtToString.h"

using namespace ApprovalTests;


    TEST_CASE("FmtContainers")
{

    std::vector<int> numbers = {1,2,3};
    FmtApprovals::verify(numbers);
}
