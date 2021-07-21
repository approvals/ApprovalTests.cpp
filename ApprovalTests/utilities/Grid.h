#pragma once
#include <sstream>
#include <functional>

namespace ApprovalTests
{
    class Grid
    {
    public:
        static std::string print(int width,
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
    };
}
