#include "Catch.hpp"
#include "ApprovalTests/Approvals.h"

#include <ostream>

using namespace ApprovalTests;

struct Rectangle3{

    int x,y, width, height;

    friend std::ostream &operator<<(std::ostream &os, const Rectangle3 &rectangle) {
        os << "[x: " << rectangle.x << " y: " << rectangle.y << " width: " << rectangle.width << " height: "
           << rectangle.height << "]";
        return os;
    }
};

std::vector<Rectangle3> getRectangles()
{
    return
    {
        {4, 50, 100, 61},
        {50, 5200, 400, 62},
        {60, 3, 7, 63},
    };
}

TEST_CASE("MultipleLinesCanBeHardToRead") {
    // begin-snippet: verify_list
    Approvals::verifyAll(
        "rectangles",
        getRectangles());
    // end-snippet

}

// begin-snippet: to_string_wrapper_example
struct FormatRectangleForMultipleLines{

    explicit FormatRectangleForMultipleLines(const Rectangle3& rectangle) : rectangle(rectangle)
    {
    }

    const Rectangle3& rectangle;

    friend std::ostream &operator<<(std::ostream &os, const FormatRectangleForMultipleLines &wrapper) {
        os << "(x,y,width,height) = (" <<
           wrapper.rectangle.x << "," <<
           wrapper.rectangle.y << "," <<
           wrapper.rectangle.width << "," <<
           wrapper.rectangle.height << ")";
        return os;
    }
};

TEST_CASE("AlternativeFormattingCanBeEasyToRead") {
    Approvals::verifyAll(
        "rectangles",
        getRectangles(),
        [](auto r, auto& os){os << FormatRectangleForMultipleLines(r);}
    );
}
// end-snippet

std::ostream& toStringForMultipleLines(std::ostream &os, const Rectangle3 &rectangle) {
    os << "(x,y,width,height) = (" <<
       rectangle.x << "," <<
       rectangle.y << "," <<
       rectangle.width << "," <<
       rectangle.height << ")";
    return os;
}

TEST_CASE("AlternativeFormattingCanBeEasyToRead2") {
    Approvals::verifyAll(
        "rectangles",
        getRectangles(),
        [](auto r, auto& os){ toStringForMultipleLines(os, r);}
    );
}
