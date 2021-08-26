#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include <vector>

TEST_CASE("YouCanVerifyIteratorRange")
{
    using namespace ApprovalTests;

    std::vector<std::string> v{"hello", "world"};
    auto converter = [](auto s, auto& os) { os << s << " => " << s[0]; };
    Approvals::verifyAll("FIRST LETTER", v.begin(), v.end(), converter);
    Approvals::verifyAll("FIRST LETTER", v.begin(), v.end(), converter, Options());
}

TEST_CASE("YouCanVerifyVectors")
{
    using namespace ApprovalTests;

    std::vector<std::string> v{"hello", "world"};
    auto converter = [](auto s, auto& os) { os << s << " => " << s[0]; };
    Approvals::verifyAll("FIRST LETTER", v, converter);
    Approvals::verifyAll("FIRST LETTER", v, converter, Options());
}

TEST_CASE("YouCanVerifyVectorsWithStandardText")
{
    // begin-snippet: VerifyAllStartingPointContainer
    std::vector<std::string> objectsToVerify{"hello", "world"};
    ApprovalTests::Approvals::verifyAll("TITLE", objectsToVerify);
    // end-snippet
    ApprovalTests::Approvals::verifyAll(
        "TITLE", objectsToVerify, ApprovalTests::Options());
}

TEST_CASE("YouCanVerifyVectorsWithStandardTextNoHeader")
{
    using namespace ApprovalTests;

    std::vector<std::string> v{"hello", "world"};
    Approvals::verifyAll(v);
    Approvals::verifyAll(v, Options());
}

// begin-snippet: VerifyAllStartingPoint
TEST_CASE("VerifyAllStartingPoint")
{
    std::vector<std::string> inputs{"input.value1", "input.value2"};
    ApprovalTests::Approvals::verifyAll("TITLE", inputs, [](auto input, auto& stream) {
        stream << input << " => "
               << "placeholder";
    });
}
// end-snippet

TEST_CASE("YouCanVerifyInitializerLists")
{
    // begin-snippet: initializer_list
    ApprovalTests::Approvals::verifyAll({10, 20, 30});
    // end-snippet

    using namespace ApprovalTests;
    Approvals::verifyAll("", {10, 20, 30});
    Approvals::verifyAll("", {10, 20, 30}, Options());

    Approvals::verifyAll(std::initializer_list<int>{10, 20, 30});
    Approvals::verifyAll(std::initializer_list<int>{10, 20, 30}, Options());

    Approvals::verifyAll({10, 20, 30}, Options());

    int i = 0;
    auto converter = [&](int e, std::ostream& s) { s << "[" << i++ << "] = " << e; };
    Approvals::verifyAll("", {10, 20, 30}, converter);
    i = 0;
    Approvals::verifyAll("", {10, 20, 30}, converter, Options());
}
