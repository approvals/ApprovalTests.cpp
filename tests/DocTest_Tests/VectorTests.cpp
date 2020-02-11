#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include <vector>

using namespace ApprovalTests;

TEST_CASE("YouCanVerifyIteratorRange")
{
    std::vector<std::string> v{"hello", "world"};
    Approvals::verifyAll("FIRST LETTER",
                         v.begin(),
                         v.end(),
                         [](auto s, auto& os) { os << s << " => " << s[0]; });
}

TEST_CASE("YouCanVerifyVectors")
{
    std::vector<std::string> v{"hello", "world"};
    Approvals::verifyAll(
        "FIRST LETTER", v, [](auto s, auto& os) { os << s << " => " << s[0]; });
}

TEST_CASE("YouCanVerifyVectorsWithStandardText")
{
    std::vector<std::string> v{"hello", "world"};
    Approvals::verifyAll("WORDS", v);
}

TEST_CASE("YouCanVerifyVectorsWithStandardTextNoHeader")
{
    std::vector<std::string> v{"hello", "world"};
    Approvals::verifyAll(v);
}
