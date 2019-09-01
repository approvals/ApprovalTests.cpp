#include "Catch.hpp"
#include <map>
#include <vector>
#include <string>
#include "PairUtilities.h"
#include "ApprovalTests/CombinationApprovals.h"
#include "reporters/FakeReporter.h"

TEST_CASE("YouCanVerifyCombinationsOf1") {
    std::vector<std::string> words{"hello", "world"};
    ApprovalTests::CombinationApprovals::verifyAllCombinations([](const std::string& s){return s + "!";}, words);
}

TEST_CASE("YouCanVerifyCombinationsOf1WithTemplateParameters") {
    std::vector<std::string> words{"hello", "world"};
    ApprovalTests::CombinationApprovals::verifyAllCombinations([](const std::string& s){return s + "!";}, words);
}

TEST_CASE("YouCanVerifyCombinationsOf1Reports") {
    std::vector<std::string> words{"hello", "world"};
    FakeReporter reporter;
    try
    {
        ApprovalTests::CombinationApprovals::verifyAllCombinations([](const std::string& s){return s + "!";}, words, reporter);
    }
    catch(const ApprovalTests::ApprovalException&)
    {
        // ignore
    }
    REQUIRE(reporter.called == true);
}

// begin-snippet: YouCanVerifyCombinationsOf2
TEST_CASE("YouCanVerifyCombinationsOf2") {
    std::vector<std::string> v{"hello", "world"};
    std::vector<int> numbers{1, 2, 3};
    ApprovalTests::CombinationApprovals::verifyAllCombinations(
            [](const std::string& s, int i){return std::make_pair(s, i);},
            v,
            numbers);
}
// end-snippet

TEST_CASE("YouCanVerifyCombinationsOf9") {
    std::vector<std::string> letters{"a", "b"};
    ApprovalTests::CombinationApprovals::verifyAllCombinations([](
                                                               const std::string& s1,
                                                               const std::string& s2,
                                                               const std::string& s3,
                                                               const std::string& s4,
                                                               const std::string& s5,
                                                               const std::string& s6,
                                                               const std::string& s7,
                                                               const std::string& s8,
                                                               const std::string& s9)
                              {return s1 + s2 + s3 + s4 + s5 + s6 + s7 + s8 + s9;}, letters, letters, letters, letters, letters, letters, letters, letters, letters);
}
