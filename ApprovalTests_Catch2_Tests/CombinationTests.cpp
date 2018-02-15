#include "../ApprovalTests/Catch2Approvals.h"
#include "../ApprovalTests/CombinationApprovals.h"

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
