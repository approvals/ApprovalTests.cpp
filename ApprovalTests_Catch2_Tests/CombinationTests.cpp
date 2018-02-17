#include "../ApprovalTests/Catch2Approvals.h"

#include <map>
#include <vector>
#include <string>
#include <ostream>

using namespace std;

ostream &operator<<(ostream &os, const std::pair<std::string, int>& pair)
{
    os << "(" << pair.first << ", " << pair.second << ")";
        return os;
}

TEST_CASE("YouCanVerifyCombinationsOf1") {
    std::vector<std::string> words{"hello", "world"};
    CombinationApprovals::verifyAllCombinations<std::vector<std::string>, std::string>( [](std::string s){return s + "!";}, words);
}

TEST_CASE("YouCanVerifyCombinationsOf2") {
    std::vector<std::string> v{"hello", "world"};
    std::vector<int> numbers{1, 2, 3};
    CombinationApprovals::verifyAllCombinations<std::vector<std::string>, std::vector<int>, std::pair<std::string, int>>( [](std::string s, int i){return std::make_pair(s, i);}, v, numbers);
}

TEST_CASE("YouCanVerifyCombinationsOf9") {
    std::vector<std::string> letters{"a", "b"};
    CombinationApprovals::verifyAllCombinations<
            std::vector<std::string>,
            std::vector<std::string>,
            std::vector<std::string>,
            std::vector<std::string>,
            std::vector<std::string>,
            std::vector<std::string>,
            std::vector<std::string>,
            std::vector<std::string>,
            std::vector<std::string>,
            std::string>( [](
            std::string s1,
            std::string s2,
            std::string s3,
            std::string s4,
            std::string s5,
            std::string s6,
            std::string s7,
            std::string s8,
            std::string s9)
                              {return s1 + s2 + s3 + s4 + s5 + s6 + s7 + s8 + s9;}, letters, letters, letters, letters, letters, letters, letters, letters, letters);
}
