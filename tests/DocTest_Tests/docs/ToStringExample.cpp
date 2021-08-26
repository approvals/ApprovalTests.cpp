#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"

#include <ostream>

struct Rectangle1
{

    int x, y, width, height;

    // begin-snippet: to_string_standard_example
    friend std::ostream& operator<<(std::ostream& os, const Rectangle1& rectangle)
    {
        os << "[x: " << rectangle.x << " y: " << rectangle.y
           << " width: " << rectangle.width << " height: " << rectangle.height << "]";
        return os;
    }
    // end-snippet
};
TEST_CASE("ToStringsAreHelpful")
{
    Rectangle1 r = {40, 50, 100, 60};
    ApprovalTests::Approvals::verify(r);
}
