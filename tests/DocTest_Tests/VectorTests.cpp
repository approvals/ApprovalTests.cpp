#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include <vector>

using namespace ApprovalTests;

TEST_CASE("YouCanVerifyIteratorRange")
{
    std::vector<std::string> v{"hello", "world"};
    auto converter = [](auto s, auto& os) { os << s << " => " << s[0]; };
    Approvals::verifyAll("FIRST LETTER", v.begin(), v.end(), converter);
    Approvals::verifyAll("FIRST LETTER", v.begin(), v.end(), converter, Options());
}

TEST_CASE("YouCanVerifyVectors")
{
    std::vector<std::string> v{"hello", "world"};
    auto converter = [](auto s, auto& os) { os << s << " => " << s[0]; };
    Approvals::verifyAll("FIRST LETTER", v, converter);
    Approvals::verifyAll("FIRST LETTER", v, converter, Options());
}

TEST_CASE("YouCanVerifyVectorsWithStandardText")
{
    // begin-snippet: VerifyAllStartingPointContainer
    std::vector<std::string> objectsToVerify{"hello", "world"};
    Approvals::verifyAll("TITLE", objectsToVerify);
    Approvals::verifyAll("TITLE", objectsToVerify, Options());
    // end-snippet
}

TEST_CASE("YouCanVerifyVectorsWithStandardTextNoHeader")
{
    std::vector<std::string> v{"hello", "world"};
    Approvals::verifyAll(v);
    Approvals::verifyAll(v, Options());
}

// begin-snippet: VerifyAllStartingPoint
TEST_CASE("VerifyAllStartingPoint")
{
    std::vector<std::string> inputs{"input.value1", "input.value2"};
    Approvals::verifyAll("TITLE", inputs, [](auto input, auto& stream) {
        stream << input << " => "
               << "placeholder";
    });
}
// end-snippet

TEST_CASE("YouCanVerifyInitializerLists")
{
    Approvals::verifyAll("", {10, 20, 30});
    Approvals::verifyAll("", {10, 20, 30}, Options());

    Approvals::verifyAll(std::initializer_list<int>{10, 20, 30});
    Approvals::verifyAll(std::initializer_list<int>{10, 20, 30}, Options());

    Approvals::verifyAll({10, 20, 30});
    Approvals::verifyAll({10, 20, 30}, Options());

    int i = 0;
    Approvals::verifyAll("", {10, 20, 30}, [&](int e, std::ostream& s) {
        s << "[" << i++ << "] = " << e;
    });
    i = 0;
    Approvals::verifyAll(
        "",
        {10, 20, 30},
        [&](int e, std::ostream& s) { s << "[" << i++ << "] = " << e; },
        Options());
}