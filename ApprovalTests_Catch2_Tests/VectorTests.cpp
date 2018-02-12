#include "../ApprovalTests/Catch2Approvals.h"

using namespace std;

TEST_CASE("YouCanVerifyIteratorRange") {
    std::vector<std::string> v{"hello", "world"};
    Approvals::verifyAll<std::vector<std::string>::const_iterator, std::string>("FIRST LETTER",v.begin(), v.end(), [](std::string s, std::ostream& os){os << s << " => " << s[0];});
}

TEST_CASE("YouCanVerifyVectors") {
    std::vector<std::string> v{"hello", "world"};
    Approvals::verifyAll<std::string>("FIRST LETTER", v, [](std::string s, std::ostream& os){os << s << " => " << s[0];});
}

TEST_CASE("YouCanVerifyVectorsWithStandardText") {
    std::vector<std::string> v{"hello", "world"};
    Approvals::verifyAll("WORDS", v);
}

TEST_CASE("YouCanVerifyVectorsWithStandardTextNoHeader") {
    std::vector<std::string> v{"hello", "world"};
    Approvals::verifyAll(v);
}
