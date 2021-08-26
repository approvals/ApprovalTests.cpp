#include "doctest/doctest.h"
#include <vector>
#include <string>
#include "ApprovalTests/CombinationApprovals.h"

// begin-snippet: YouCanVerifyCombinationsOf2
TEST_CASE("YouCanVerifyCombinationsOf2")
{
    std::vector<std::string> v{"hello", "world"};
    std::vector<int> numbers{1, 2, 3};
    ApprovalTests::CombinationApprovals::verifyAllCombinations(
        [](std::string s, int i) {
            return std::string("(") + s + ", " + std::to_string(i) + ")";
        },
        v,
        numbers);
}
// end-snippet

// begin-snippet: CombinationsStartingPoint
TEST_CASE("CombinationsStartingPoint")
{
    std::vector<std::string> inputs1{"input1.value1", "input1.value2"};
    std::vector<std::string> inputs2{"input2.value1", "input2.value2", "input2.value3"};
    ApprovalTests::CombinationApprovals::verifyAllCombinations(
        "TITLE",
        [&](auto /*input1*/, auto /*input2*/) { return "placeholder"; },
        inputs1,
        inputs2);
}
// end-snippet
