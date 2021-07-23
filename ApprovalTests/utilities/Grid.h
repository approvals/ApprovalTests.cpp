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
                                 std::function<void(int, int, std::ostream&)> printCell);
        static std::string print(int width, int height, std::string text);
    };
}
