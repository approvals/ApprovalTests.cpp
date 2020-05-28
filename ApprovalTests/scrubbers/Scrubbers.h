#pragma once

#include <string>
#include <functional>
#include <iostream>
#include <regex>
#include "ApprovalTests/utilities/StringUtils.h"

namespace ApprovalTests
{
    using Scrubber = std::function<std::string(const std::string&)>;
    namespace Scrubbers
    {
        inline std::string doNothing(const std::string& input)
        {
            return input;
        }

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

        using Match = std::sub_match<std::string::const_iterator>;
        using RegexReplacer = std::function<std::string(const Match)>;
        inline std::string scrubRegex(const std::string& input,
                                      const std::regex& regex,
                                      const RegexReplacer& replaceFunction)
        {
            auto result = input;
            std::smatch m;
            if (std::regex_search(result, m, regex))
            {
                for (size_t i = 0; i < m.size(); ++i)
                {
                    auto match = m[i];
                    auto original_matched_text = match.str();
                    auto replacement = replaceFunction(match);
                    result = StringUtils::replaceAll(
                        result, original_matched_text, replacement);
                }
            }
            return result;
        }

    }
}
