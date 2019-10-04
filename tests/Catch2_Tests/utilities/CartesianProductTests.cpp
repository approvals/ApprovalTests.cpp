#include "Catch.hpp"
#include "ApprovalTests/CombinationApprovals.h"

using namespace ApprovalTests;
using namespace ApprovalTests::CombinationApprovals;

template<class Converter, class Container, class... Containers>
std::string run_cartesian_product(Converter&& converter, const Container& input0, const Containers&... inputs)
{
    std::stringstream s;
    Detail::cartesian_product(Detail::serialize<Converter>{s, std::forward<Converter>(converter)}, input0, inputs...);
    return s.str();
}

TEST_CASE("Single Container-Single Value")
{
    std::vector<std::string> words{"hello"};
    auto result = run_cartesian_product([](const std::string& s){return s + "!";}, words);
    REQUIRE(result == "(hello) => hello!\n");
}
