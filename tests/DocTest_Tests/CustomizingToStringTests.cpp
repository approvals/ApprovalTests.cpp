#include "doctest/doctest.h"

#include "ApprovalTests/utilities/StringMaker.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/CombinationApprovals.h"

//----------------------------------------------------------------------------------------
// operator<<(std::ostream&)
struct OStreamPrintable
{
    int field1_ = 0;

    // begin-snippet: customising_to_string_with_ostream_operator
    friend std::ostream& operator<<(std::ostream& os, const OStreamPrintable& printable)
    {
        os << "From ostream: " << printable.field1_ << '\n';
        return os;
    }
    // end-snippet
};

TEST_CASE("Test toString from ostream operator")
{
    // This tests verifying an object with its own operator<<
    OStreamPrintable p;
    ApprovalTests::Approvals::verify(p);
}

//----------------------------------------------------------------------------------------
// StringMaker
struct StringMakerPrintable
{
    int field1_ = 0;
};

#if defined(__GNUC__) && __GNUC__ < 7
// begin-snippet: customising_to_string_with_string_maker_specialization_gcc5_and_6
namespace ApprovalTests
{
    template <> std::string StringMaker::toString(const StringMakerPrintable& printable)
    {
        return "From StringMaker: " + std::to_string(printable.field1_);
    }
}
// end-snippet
#else
// begin-snippet: customising_to_string_with_string_maker_specialization
template <>
std::string ApprovalTests::StringMaker::toString(const StringMakerPrintable& printable)
{
    return "From StringMaker: " + std::to_string(printable.field1_);
}
// end-snippet
#endif

TEST_CASE("Test toString from StringMaker")
{
    // This tests verifying an object that has a matching ApprovalTests::StringMaker::toString
    StringMakerPrintable p;
    ApprovalTests::Approvals::verify(p);
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
    int field1_ = 0;
};

// begin-snippet: customising_to_string_with_custom_to_string_class
class CustomToStringClass
{
public:
    template <typename T> static std::string toString(const T& printable)
    {
        return "From Template: " + std::to_string(printable.field1_);
    }
};
// end-snippet

TEST_CASE("Test toString from Template")
{
    // This tests verifying an object by supplying a custom template type to ApprovalTests::TApprovals<>

    TemplatePrintable p;
    // begin-snippet: customising_to_string_with_custom_to_string_class_usage1
    ApprovalTests::TApprovals<
        ApprovalTests::ToStringCompileTimeOptions<CustomToStringClass>>::verify(p);
    // end-snippet
}

TEST_CASE("Test toString from Template and using")
{
    // This tests verifying an object by supplying a custom template type to ApprovalTests::TApprovals<>,
    // and demos use of 'using' to make the verify call more readable

    TemplatePrintable p;
    // begin-snippet: customising_to_string_with_custom_to_string_class_usage2
    using MyApprovals = ApprovalTests::TApprovals<
        ApprovalTests::ToStringCompileTimeOptions<CustomToStringClass>>;

    MyApprovals::verify(p);
    // end-snippet
}

TEST_CASE("Combinations with CustomToStringClass")
{
    std::vector<TemplatePrintable> inputs1{TemplatePrintable(), TemplatePrintable()};
    std::vector<TemplatePrintable> inputs2{TemplatePrintable()};

    using MyCombinationApprovals = ApprovalTests::TCombinationApprovals<
        ApprovalTests::ToStringCompileTimeOptions<CustomToStringClass>>;
    MyCombinationApprovals::verifyAllCombinations(
        [](auto /*input1*/, auto /*input2*/) { return "placeholder"; }, inputs1, inputs2);
}
