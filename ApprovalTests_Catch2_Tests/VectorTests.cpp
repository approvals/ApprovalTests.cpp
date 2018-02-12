#include "../ApprovalTests/Catch2Approvals.h"

using namespace std;

TEST_CASE("YouCanVerifyVectors") {
    std::vector<std::string> v{"hello", "world"};
    Approvals::verifyAll<std::string>("UPPER CASE", v, [](std::string s, std::ostream& os){os << s << " => " << s;});
}
