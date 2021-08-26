#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"

#include <ostream>

struct Rectangle2
{

    int x, y, width, height;

    // Using Template instead of ostream for embedded instances where ostream aren't available
    // template implementation of output operator
    // begin-snippet: to_string_template_example
    template <class STREAM>
    friend STREAM& operator<<(STREAM& os, const Rectangle2& rectangle)
    {
        os << "[x: " << rectangle.x << " y: " << rectangle.y
           << " width: " << rectangle.width << " height: " << rectangle.height << "]";
        return os;
    }
    // end-snippet
};
TEST_CASE("ToStringTemplatesAreHelpful")
{
    Rectangle2 r = {40, 50, 100, 60};
    ApprovalTests::Approvals::verify(r);
}
