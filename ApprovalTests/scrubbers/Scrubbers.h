#pragma once

#include <string>

#include <iostream>
#include <regex>

namespace ApprovalTests
{
    namespace Scrubbers
    {
        inline std::string scrubGuid(const std::string& input)
        {
            static const std::regex regex("[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-["
                                          "0-9a-fA-F]{4}-[0-9a-fA-F]{12}");
            std::match_results<std::string::const_iterator> match;

            auto result = std::regex_replace(input, regex, "guid_1");
            return result;
        }
    }
}
