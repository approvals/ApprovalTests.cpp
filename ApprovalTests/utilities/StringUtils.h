

#pragma once

#include "StringMaker.h"

#include <string>
#include <algorithm>
#include <sstream>

namespace ApprovalTests
{
    class StringUtils
    {
    public:
        static std::string replaceAll(std::string inText,
                                      const std::string& find,
                                      const std::string& replaceWith);

        static bool contains(const std::string& inText, const std::string& find);

        static std::string toLower(std::string inText);

        static bool endsWith(std::string value, std::string ending);

        template <typename T> static std::string toString(const T& contents)
        {
            return StringMaker::toString(contents);
        }
    };
}
