#include <iostream>
#include <ostream>
#include <stdexcept>
#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/utilities/SystemUtils.h"

using namespace ApprovalTests;

TEST_CASE("YouCanVerifyText")
{
    Approvals::verify("My objects!");
    Approvals::verify("My objects!", Options());
}

TEST_CASE("TestStreamableObject")
{
    Approvals::verify(42);
    Approvals::verify(42, Options());
}

class NonCopyable
{
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable& x) = delete; // prevent copy construction

    friend std::ostream& operator<<(std::ostream& os, const NonCopyable& /*copyable*/)
    {
        return os << 999;
    }
};

TEST_CASE("TestNonCopyableStreamableObject")
{
    NonCopyable object;
    Approvals::verify(object);
    Approvals::verify(object, Options());
}

TEST_CASE("Test Unicode")
{
    Approvals::verify("I like unicode ☃");
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
    auto converter = [](const auto& p, auto& os) {
        os << "[x: " << p.x << " y: " << p.y << "]";
    };
    Approvals::verify(getPoint(), converter);
    Approvals::verify(getPoint(), converter, Options());
}

// ==============================================================

struct FormatNonStreamablePoint
{
    explicit FormatNonStreamablePoint(const NonStreamablePoint& point_) : point(point_)
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
    auto converter = [](auto r, auto& os) { os << FormatNonStreamablePoint(r); };
    Approvals::verify(getPoint(), converter);
    Approvals::verify(getPoint(), converter, Options());
}

// ==============================================================

std::ostream& customToStreamFunction(std::ostream& os, const NonStreamablePoint& point)
{
    os << point.x << "," << point.y;
    return os;
}

TEST_CASE("YouCanVerifyWithConverterWrapperFunction")
{
    auto converter = [](auto r, auto& os) { customToStreamFunction(os, r); };
    Approvals::verify(getPoint(), converter);
    Approvals::verify(getPoint(), converter, Options());
}

// ==============================================================

TEST_CASE("VerifyingException")
{
    auto throws = []() { throw std::runtime_error("Here is my exception message"); };
    Approvals::verifyExceptionMessage(throws);
    Approvals::verifyExceptionMessage(throws, Options());
}
