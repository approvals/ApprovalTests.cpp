#pragma once

#include <string>
#include <sstream>

namespace ApprovalTests
{
    class StringMaker
    {
    public:
        template <typename T> static std::string toString(const T& contents)
        {
            std::stringstream s;
            s << contents;
            return s.str();
        }
    };
}
