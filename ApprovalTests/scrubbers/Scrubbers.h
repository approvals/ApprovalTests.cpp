#pragma once

#include <string>

#include <iostream>
#include <regex>
#include <ApprovalTests/utilities/StringUtils.h>

namespace ApprovalTests
{
    namespace Scrubbers
    {
        inline std::string scrubGuid(const std::string& input)
        {
            static const std::regex regex("[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-["
                                          "0-9a-fA-F]{4}-[0-9a-fA-F]{12}");

            int matchNumber = 1;
            auto result = input;
            std::smatch m;
            while (std::regex_search(result, m, regex))
            {
                auto guid_match = m.str();
                auto replacement = "guid_" + std::to_string(matchNumber);
                result = StringUtils::replaceAll(result, guid_match, replacement);
                matchNumber += 1;
            }
            return result;
        }
    }
}
