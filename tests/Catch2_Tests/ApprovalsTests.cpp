#include <ostream>
#include <stdexcept>
#include <iostream>
#include "catch2/catch.hpp"
#include "ApprovalTests/Approvals.h"

using namespace ApprovalTests;

TEST_CASE("Print debug info to check Ninja workaround")
{
#ifdef _MSC_VER
    // This is defined for both Visual C++ and clang-cl
    std::cout << "_MSC_VER is defined " << std::endl;
#else
    std::cout << "_MSC_VER is NOT defined " << std::endl;
#endif
    std::cout << __FILE__ << std::endl;
}

TEST_CASE("YouCanVerifyText")
{
    Approvals::verify("My objects!");
}

TEST_CASE("TestStreamableObject")
{
    Approvals::verify(42);
}

class NonCopyable
{
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable& x) = delete; // prevent copy construction

    friend std::ostream& operator<<(std::ostream& os,
                                    const NonCopyable& /*copyable*/)
    {
        return os << 999;
    }
};

TEST_CASE("TestNonCopyableStreamableObject")
{
    NonCopyable object;
    Approvals::verify(object);
}

// ==============================================================

struct NonStreamablePoint
{
    int x = 0;
    int y = 0;
    // Note that NonStreamablePoint does not provide operator<<( ostream &os, const NonStreamablePoint& )
};

NonStreamablePoint getPoint()
{
    return NonStreamablePoint{4, 7};
}

TEST_CASE("YouCanVerifyWithConverterLambda")
{
    Approvals::verify(getPoint(), [](const auto& p, auto& os) {
        os << "[x: " << p.x << " y: " << p.y << "]";
    });
}

// ==============================================================

struct FormatNonStreamablePoint
{
    explicit FormatNonStreamablePoint(const NonStreamablePoint& point)
        : point(point)
    {
    }

    const NonStreamablePoint& point;

    friend std::ostream& operator<<(std::ostream& os,
                                    const FormatNonStreamablePoint& wrapper)
    {
        os << "(x,y) = (" << wrapper.point.x << "," << wrapper.point.y << ")";
        return os;
    }
};

TEST_CASE("YouCanVerifyWithConverterWrapperClass")
{
    Approvals::verify(getPoint(), [](auto r, auto& os) {
        os << FormatNonStreamablePoint(r);
    });
}

// ==============================================================

std::ostream& customToStreamFunction(std::ostream& os,
                                     const NonStreamablePoint& point)
{
    os << point.x << "," << point.y;
    return os;
}

TEST_CASE("YouCanVerifyWithConverterWrapperFunction")
{
    Approvals::verify(getPoint(),
                      [](auto r, auto& os) { customToStreamFunction(os, r); });
}

// ==============================================================

TEST_CASE("VerifyingException")
{
    Approvals::verifyExceptionMessage(
        []() { throw std::runtime_error("Here is my exception message"); });
}

TEST_CASE("VerifyingNoException")
{
    // begin-snippet: verify_exception_message_example
    Approvals::verifyExceptionMessage([]() { /* your code goes here */ });
    // end-snippet
}
