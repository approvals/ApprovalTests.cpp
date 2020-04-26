// These are tests to ensure that we are maintaining the pre-Options
// interface, i.e. methods that take a Reporter as the first argument.

#undef APPROVAL_TESTS_HIDE_DEPRECATED_CODE
#undef APPROVAL_TESTS_SHOW_DEPRECATION_WARNINGS

#include "doctest/doctest.h"
#include "ApprovalTests/CombinationApprovals.h"

using namespace ApprovalTests;

TEST_CASE("verifyAllCombinations")
{
    const std::vector<std::string> v{"hello", "world"};
    const std::vector<int> numbers{1, 2, 3};
    CombinationApprovals::verifyAllCombinations(
        DefaultReporter(),
        [](const std::string& s, int i) {
            return std::string("(") + s + ", " + std::to_string(i) + ")";
        },
        v,
        numbers);
}
