#include "../ApprovalTests/Catch2Approvals.h"

using namespace std;

TEST_CASE("YouCanVerifyVectors") {
    std::vector<std::string> v{"hello", "world"};
    Approvals::verifyAll<std::string>("FIRST LETTER", v, [](std::string s, std::ostream& os){os << s << " => " << s[0];});
}

TEST_CASE("YouCanVerifyVectorsWithStandardText") {
    std::vector<std::string> v{"hello", "world"};
    Approvals::verifyAll<std::string>("WORDS", v);
}
