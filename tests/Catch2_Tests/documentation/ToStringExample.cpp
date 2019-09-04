#include "Catch.hpp"
#include "ApprovalTests/Approvals.h"

#include <ostream>

using namespace ApprovalTests;

struct Rectangle2{

    int x,y, width, height;

    // begin-snippet: to_string_standard_example
    friend std::ostream &operator<<(std::ostream &os, const Rectangle2 &rectangle) {
        os << "[x: " << rectangle.x << " y: " << rectangle.y << " width: " << rectangle.width << " height: "
           << rectangle.height << "]";
        return os;
    }
    // end-snippet

};
TEST_CASE("ToStringsAreHelpful") {
    Rectangle2 r = {40,50,100,60};
    Approvals::verify(r);

}

