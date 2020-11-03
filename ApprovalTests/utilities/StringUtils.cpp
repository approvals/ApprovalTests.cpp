#include "ApprovalTests/utilities/StringUtils.h"

namespace ApprovalTests
{
    std::string StringUtils::replaceAll(std::string inText,
                                        const std::string& find,
                                        const std::string& replaceWith)
    {
        size_t start_pos = 0;
        while ((start_pos = inText.find(find, start_pos)) != std::string::npos)
        {
            inText.replace(start_pos, find.length(), replaceWith);
            start_pos +=
                replaceWith.length(); // Handles case where 'to' is a substring of 'from'
        }
        return inText;
    }

    bool StringUtils::contains(const std::string& inText, const std::string& find)
    {
        return inText.find(find, 0) != std::string::npos;
    }

    std::string StringUtils::toLower(std::string inText)
    {
        std::string copy(inText);
        std::transform(inText.begin(), inText.end(), copy.begin(), [](char c) {
            return static_cast<char>(tolower(c));
        });
        return copy;
    }

    bool StringUtils::endsWith(std::string value, std::string ending)
    {
        if (ending.size() > value.size())
        {
            return false;
        }
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }

    std::string StringUtils::leftTrim(std::string s)
    {

        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
                    return !std::isspace(ch);
                }));
        return s;
    }

    std::string StringUtils::rightTrim(std::string s)
    {
        s.erase(std::find_if(s.rbegin(),
                             s.rend(),
                             [](unsigned char ch) { return !std::isspace(ch); })
                    .base(),
                s.end());
        return s;
    }

    std::string StringUtils::trim(std::string s)
    {
        s = leftTrim(s);
        s = rightTrim(s);
        return s;
    }
}
