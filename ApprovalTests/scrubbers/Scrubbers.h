#pragma once

#include <string>
#include <functional>
#include <iostream>
#include <regex>
#include <map>
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

        using RegexMatch = std::sub_match<std::string::const_iterator>;
        using RegexReplacer = std::function<std::string(const RegexMatch)>;
        inline std::string scrubRegex(const std::string& input,
                                      const std::regex& regex,
                                      const RegexReplacer& replaceFunction)
        {
            std::string result;
            std::string remainder = input;
            std::smatch m;
            while (std::regex_search(remainder, m, regex))
            {
                auto match = m[0];
                auto original_matched_text = match.str();
                auto replacement = replaceFunction(match);
                result += std::string(m.prefix()) + replacement;
                remainder = m.suffix();
            }
            result += remainder;
            return result;
        }

        inline std::string scrubGuid(const std::string& input)
        {
            static const std::regex regex("[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-["
                                          "0-9a-fA-F]{4}-[0-9a-fA-F]{12}");

            int matchNumber = 1;
            std::map<std::string, int> matchIndices;
            return scrubRegex(input, regex, [&](RegexMatch m) {
                auto guid_match = m.str();

                if (matchIndices[guid_match] == 0)
                {
                    matchIndices[guid_match] = matchNumber++;
                }
                return "guid_" + std::to_string(matchIndices[guid_match]);
            });
        }
    }
}
