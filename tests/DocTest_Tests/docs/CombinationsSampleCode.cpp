#include "doctest/doctest.h"
#include <vector>
#include "ApprovalTests/CombinationApprovals.h"

namespace
{
    double functionThatReturnsSomethingOutputStreamable(const std::string& /*input1*/,
                                                        const int input2,
                                                        const double input3)
    {
        return input2 * input3;
    }
}

TEST_CASE("YouCanVerifyCombinationsOf3")

{
    std::vector<std::string> listOfInput1s{"a", "b"};
    std::vector<int> listOfInput2s{1, 2, 3};
    std::vector<double> listOfInput3s{1.1, 2.2};
    // begin-snippet: sample_combinations_of_three
    ApprovalTests::CombinationApprovals::verifyAllCombinations(
        [](const std::string& input1, const int input2, const double input3) {
            return functionThatReturnsSomethingOutputStreamable(input1, input2, input3);
        }, // This is the converter function
        listOfInput1s,
        listOfInput2s,
        listOfInput3s);
    // end-snippet
}

TEST_CASE("YouCanVerifyCombinationsOf3WithAuto")

{
    std::vector<std::string> listOfInput1s{"a", "b"};
    std::vector<int> listOfInput2s{1, 2, 3};
    std::vector<double> listOfInput3s{1.1, 2.2};
    // begin-snippet: sample_combinations_of_three_with_auto
    ApprovalTests::CombinationApprovals::verifyAllCombinations(
        [](auto& input1, auto& input2, auto& input3) {
            return functionThatReturnsSomethingOutputStreamable(input1, input2, input3);
        }, // This is the converter function
        listOfInput1s,
        listOfInput2s,
        listOfInput3s);
    // end-snippet
}
