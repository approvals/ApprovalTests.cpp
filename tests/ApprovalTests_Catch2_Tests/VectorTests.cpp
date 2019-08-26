#include "Catch.hpp"
#include "ApprovalTests/Approvals.h"
#include "Approvals.h"
#include <vector>

TEST_CASE("YouCanVerifyIteratorRange") {
    std::vector<std::string> v{"hello", "world"};
    ApprovalTests::Approvals::verifyAll("FIRST LETTER", v.begin(), v.end(), [](auto s, auto& os){os << s << " => " << s[0];});
}

TEST_CASE("YouCanVerifyVectors") {
    std::vector<std::string> v{"hello", "world"};
    ApprovalTests::Approvals::verifyAll("FIRST LETTER", v, [](auto s, auto& os){os << s << " => " << s[0];});
}

TEST_CASE("YouCanVerifyVectorsWithStandardText") {
    std::vector<std::string> v{"hello", "world"};
    ApprovalTests::Approvals::verifyAll("WORDS", v);
}

TEST_CASE("YouCanVerifyVectorsWithStandardTextNoHeader") {
    std::vector<std::string> v{"hello", "world"};
    ApprovalTests::Approvals::verifyAll(v);
}
