#include "Catch.hpp"
#include "ApprovalTests/CombinationApprovals.h"

using namespace ApprovalTests;
using namespace ApprovalTests::CombinationApprovals;

using Result = std::string;

template<class Converter>
struct serialize
{
    Result& out;
    Converter converter;
    template<class T, class... Ts>
    void operator()(T&& input1, Ts&&... inputs) {
        out += converter(input1, inputs...) + '\n';
    }
};

template<class Converter, class Container, class... Containers>
Result run_cartesian_product(Converter&& converter, const Container& input0, const Containers&... inputs)
{
    Result s;
    Detail::cartesian_product(serialize<Converter>{s, std::forward<Converter>(converter)}, input0, inputs...);
    return s;
}

TEST_CASE("Single Container-Single Value")
{
    std::vector<std::string> words{"hello"};
    auto result = run_cartesian_product([](const std::string& s){return s + "!";}, words);
    Result expected = "hello!\n";
    REQUIRE(result == expected);
}

TEST_CASE("Two Containers-Single Value")
{
    std::vector<std::string> input1{"hello"};
    std::vector<std::string> input2{"world"};
    auto result = run_cartesian_product([](const std::string& s1, const std::string& s2){return s1 + "," + s2;}, input1, input2);
    Result expected = "hello,world\n";
    REQUIRE(result == expected);
}

TEST_CASE("Two Containers-Two Values")
{
    std::vector<std::string> input1{"A", "B"};
    std::vector<std::string> input2{"1", "2"};
    auto result = run_cartesian_product([](const std::string& s1, const std::string& s2){return s1 + "," + s2;}, input1, input2);
    Result expected = "A,1\nA,2\nB,1\nB,2\n";
    REQUIRE(result == expected);
}
