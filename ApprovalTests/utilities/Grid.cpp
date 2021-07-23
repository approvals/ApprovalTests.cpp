#include "Grid.h"
namespace ApprovalTests
{
    std::string Grid::print(int width,
                            int height,
                            std::function<void(int, int, std::ostream&)> printCell)
    {
        std::stringstream s;
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                printCell(x, y, s);
            }
            s << '\n';
        }
        return s.str();
    }
    std::string Grid::print(int width, int height, std::string text)
    {
        return print(
            width, height, [&](int /*x*/, int /*y*/, std::ostream& os) { os << text; });
    }
}
