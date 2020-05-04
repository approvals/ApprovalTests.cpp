#include <ostream>
#include <stdexcept>
#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/CombinationApprovals.h"

//using namespace ApprovalTests;

namespace
{
    class CustomToStringClass
    {
    public:
        static std::string toString(int /*value*/)
        {
            return "Hello from CustomToStringClass";
        }
    };
}

TEST_CASE("Test Custom toString")
{
    ApprovalTests::TApprovals<
        ApprovalTests::ToStringCompileTimeOptions<CustomToStringClass>>::verify(42);
}

TEST_CASE("Test Custom toString with using")
{
    using Approvals = ApprovalTests::TApprovals<
        ApprovalTests::ToStringCompileTimeOptions<CustomToStringClass>>;

    Approvals::verify(42);
}

// For combination inputs
TEST_CASE("Test Custom toString for Combinations")
{
    std::vector<int> inputs1{1, 2, 3, 4};
    std::vector<int> inputs2{20, 21};
    ApprovalTests::CombinationApprovals::verifyAllCombinations(
        [](auto /*input1*/, auto /*input2*/) { return "placeholder"; }, inputs1, inputs2);
}
