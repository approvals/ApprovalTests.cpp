#include <ostream>
#include <stdexcept>
#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"

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
