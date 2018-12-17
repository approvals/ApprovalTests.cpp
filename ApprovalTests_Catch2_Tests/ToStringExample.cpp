#include "Catch.hpp"
#include "../ApprovalTests/Approvals.h"

using namespace std;

struct Rectangle1{

    int x,y, width, height;

    // Using Template instead of ostream for embedded instances where ostream aren't available 
    template <class STREAM>
    friend STREAM &operator<<(STREAM &os, const Rectangle1 &rectangle) {
        os << "[x: " << rectangle.x << " y: " << rectangle.y << " width: " << rectangle.width << " height: "
           << rectangle.height << "]";
        return os;
    }

};
TEST_CASE("ToStringsAreHelpful") {
    Rectangle1 r = {40,50,100,60};
    Approvals::verify(r);

}

