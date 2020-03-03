#include "doctest/doctest.h"
#include "ApprovalTests/utilities/CartesianProduct.h"

#include <string>
#include <vector>
#include <set>

using namespace ApprovalTests;

using Results = std::vector<std::string>;

// ------------------------------------------------------------------
// Tests which use a non-template object for accumulating results
// from CartesianProduct::cartesian_product(), to show the simplest
// way of using that function.
// ------------------------------------------------------------------

namespace
{
    // A hard-coded struct for accumulating results
    struct AccumulateResults2StringsCommaSeparated
    {
        Results results;
        void operator()(std::string&& s1, std::string&& s2)
        {
            results.push_back(s1 + "," + s2);
        }
    };
}

TEST_CASE("Cartesian product with hard-coded-converter")
{
    const std::vector<std::string> input1{"hello"};
    const std::vector<std::string> input2{"world"};
    AccumulateResults2StringsCommaSeparated results_store;
    CartesianProduct::cartesian_product(results_store, input1, input2);
    const Results expected{"hello,world"};
    REQUIRE(results_store.results == expected);
}

// ------------------------------------------------------------------
// Tests which use template object for accumulating results
// from CartesianProduct::cartesian_product(). This gives greater
// flexibility, but perhaps slightly more complex code.
// ------------------------------------------------------------------

namespace
{
    // Converter is the lambda, function or similar, that takes a set of input values, and returns a calculated result
    template <class Converter> struct AccumulateResults
    {
        Results results;
        Converter converter;
        template <class T, class... Ts> void operator()(T&& input1, Ts&&... inputs)
        {
            results.push_back(converter(input1, inputs...));
        }
    };

    template <class Converter, class Container, class... Containers>
    void test_cartesian_product(const Results& expected,
                                Converter&& converter,
                                const Container& input0,
                                const Containers&... inputs)
    {
        auto results_store =
            AccumulateResults<Converter>{Results(), std::forward<Converter>(converter)};
        CartesianProduct::cartesian_product(results_store, input0, inputs...);
        REQUIRE(results_store.results == expected);
    }

    std::string concatenate_2_strings_comma_separated(const std::string& s1,
                                                      const std::string& s2)
    {
        return (s1 + "," + s2);
    }
}

TEST_CASE("Cartesian product with iterator types")
{
    const Results expected{"A,1", "A,2", "B,1", "B,2"};
    DOCTEST_SUBCASE("random-access")
    {
        const std::vector<std::string> input1{"A", "B"};
        const std::vector<std::string> input2{"1", "2"};
        test_cartesian_product(
            expected, concatenate_2_strings_comma_separated, input1, input2);
    }

    DOCTEST_SUBCASE("bi-directional-access")
    {
        const std::set<std::string> input1{"A", "B"};
        const std::set<std::string> input2{"1", "2"};
        test_cartesian_product(
            expected, concatenate_2_strings_comma_separated, input1, input2);
    }
}

TEST_CASE("Cartesian product with different types of converter")
{
    const Results expected{"A,1", "A,2", "B,1", "B,2"};
    const std::vector<std::string> input1{"A", "B"};
    const std::vector<std::string> input2{"1", "2"};
    DOCTEST_SUBCASE("free function")
    {
        test_cartesian_product(
            expected, concatenate_2_strings_comma_separated, input1, input2);
    }

    DOCTEST_SUBCASE("lambda expression")
    {
        test_cartesian_product(
            expected,
            [](const std::string& s1, const std::string& s2) { return s1 + "," + s2; },
            input1,
            input2);
    }
}

TEST_CASE("Cartesian product works with mixed input types")
{
    const std::vector<std::string> input1{"hello"};
    const std::set<std::string> input2{"world"};
    const Results expected{"hello,world"};
    test_cartesian_product(
        expected, concatenate_2_strings_comma_separated, input1, input2);
}

TEST_CASE("Cartesian product with an empty input gives empty output")
{
    const std::set<std::string> input1{"A", "B"};
    const std::set<std::string> input2;
    const Results expected;
    test_cartesian_product(
        expected, concatenate_2_strings_comma_separated, input1, input2);
}
