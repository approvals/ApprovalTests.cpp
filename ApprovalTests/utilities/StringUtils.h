

#pragma once

#include "ApprovalTests/utilities/StringMaker.h"

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

        static bool beginsWith(std::string value, std::string beginning);
        static bool endsWith(std::string value, std::string ending);

        template <typename T> static std::string toString(const T& contents)
        {
            return StringMaker::toString(contents);
        }

        static std::string leftTrim(std::string s);

        static std::string rightTrim(std::string s);

        static std::string trim(std::string s);
    };
}
