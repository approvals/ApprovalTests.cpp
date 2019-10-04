#include "Catch.hpp"
#include "ApprovalTests/CombinationApprovals.h"

#include <set>

using namespace ApprovalTests;
using namespace ApprovalTests::CombinationApprovals;

using Result = std::vector<std::string>;

// ------------------------------------------------------------------

// A hard-coded struct for acculuating results
struct AccumulateResults2StringsCommaSeparated
{
    Result out;
    void operator()(std::string&& s1, std::string&& s2)
    {
        out.push_back(s1 + "," + s2);
    }
};

TEST_CASE("Two Vectors-Single Value-hard-coded-converter")
{
    std::vector<std::string> input1{"hello"};
    std::vector<std::string> input2{"world"};
    AccumulateResults2StringsCommaSeparated results_store;
    Detail::cartesian_product(results_store, input1, input2);
    Result expected{"hello,world"};
    REQUIRE(results_store.out == expected);
}

// ------------------------------------------------------------------

// Converter is the lambda, function or similar, that takes a set of input values, and returns a calculated result
template<class Converter>
struct AccumulateResults
{
    Result out;
    Converter converter;
    template<class T, class... Ts>
    void operator()(T&& input1, Ts&&... inputs) {
        out.push_back(converter(input1, inputs...));
    }
};

template<class Converter, class Container, class... Containers>
void test_cartesian_product(const Result& expected, Converter&& converter, const Container& input0, const Containers&... inputs)
{
    auto results_store = AccumulateResults<Converter>{
        Result(),
        std::forward<Converter>(converter)};
    Detail::cartesian_product(results_store, input0, inputs...);
    REQUIRE(results_store.out == expected);
}

TEST_CASE("Single Vector-Single Value")
{
    std::vector<std::string> words{"hello"};
    Result expected{"hello!"};
    test_cartesian_product(expected, [](const std::string& s){return s + "!";}, words);
}

TEST_CASE("Two Vectors-Single Value")
{
    std::vector<std::string> input1{"hello"};
    std::vector<std::string> input2{"world"};
    Result expected{"hello,world"};
    test_cartesian_product(expected, [](const std::string& s1, const std::string& s2){return s1 + "," + s2;}, input1, input2);
}

TEST_CASE("Cartesian product works with vector input")
{
    std::vector<std::string> input1{"A", "B"};
    std::vector<std::string> input2{"1", "2"};
    Result expected{"A,1", "A,2", "B,1", "B,2"};
    test_cartesian_product(expected, [](const std::string& s1, const std::string& s2){return s1 + "," + s2;}, input1, input2);
}

// TODO Rename this to describe the type of iterator
TEST_CASE("Cartesian product works with set input")
{
    std::set<std::string> input1{"A", "B"};
    std::set<std::string> input2{"1", "2"};
    Result expected{"A,1", "A,2", "B,1", "B,2"};
    test_cartesian_product(expected, [](const std::string& s1, const std::string& s2){return s1 + "," + s2;}, input1, input2);
}

TEST_CASE("Cartesian product works with mixed inputs")
{
    std::vector<std::string> input1{"hello"};
    std::set<std::string> input2{"world"};
    Result expected{"hello,world"};
    test_cartesian_product(expected, [](const std::string& s1, const std::string& s2){return s1 + "," + s2;}, input1, input2);
}

TEST_CASE("Cartesian product wwith an empty input gives empty output")
{
    std::set<std::string> input1{"A", "B"};
    std::set<std::string> input2;
    Result expected;
    test_cartesian_product(expected, [](const std::string& s1, const std::string& s2){return s1 + "," + s2;}, input1, input2);
}
