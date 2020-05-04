#include "doctest/doctest.h"

#include "ApprovalTests/utilities/StringMaker.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/CombinationApprovals.h"

#include <ostream>

using namespace ApprovalTests;

//----------------------------------------------------------------------------------------
// operator<<(std::ostream&)
struct OStreamPrintable
{
    friend std::ostream& operator<<(std::ostream& os,
                                    const OStreamPrintable& /*printable*/)
    {
        os << "From ostream\n";
        return os;
    }
};

TEST_CASE("Test toString from ostream operator")
{
    OStreamPrintable p;
    Approvals::verify(p);
}

//----------------------------------------------------------------------------------------
// StringMaker
struct StringMakerPrintable
{
};

template <>
std::string ApprovalTests::StringMaker::toString(const StringMakerPrintable& /*contents*/)
{
    return "From StringMaker";
}

TEST_CASE("Test toString from StringMaker")
{
    StringMakerPrintable p;
    Approvals::verify(p);
}

TEST_CASE("Test Combinations inputs from StringMaker")
{
    std::vector<StringMakerPrintable> inputs1{StringMakerPrintable(),
                                              StringMakerPrintable()};
    std::vector<StringMakerPrintable> inputs2{StringMakerPrintable()};
    ApprovalTests::CombinationApprovals::verifyAllCombinations(
        [](auto /*input1*/, auto /*input2*/) { return "placeholder"; }, inputs1, inputs2);
}

//----------------------------------------------------------------------------------------
// Template
struct TemplatePrintable
{
};

class CustomToStringClass
{
public:
    template <typename T> static std::string toString(const T& /*value*/)
    {
        return "From Template";
    }
};

TEST_CASE("Test toString from Template")
{
    TemplatePrintable p;
    ApprovalTests::TApprovals<
        ApprovalTests::ToStringCompileTimeOptions<CustomToStringClass>>::verify(p);
}

TEST_CASE("Test toString from Template and using")
{
    using MyApprovals = ApprovalTests::TApprovals<
        ApprovalTests::ToStringCompileTimeOptions<CustomToStringClass>>;

    TemplatePrintable p;
    MyApprovals::verify(p);
}
