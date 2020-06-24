#include "Scrubbers.h"

#include <string>
#include <functional>
#include <regex>
#include <map>

namespace ApprovalTests
{
    std::string Scrubbers::doNothing(const std::string& input)
    {
        return input;
    }
    std::string Scrubbers::scrubRegex(const std::string& input,
                                      const std::regex& regex,
                                      const Scrubbers::RegexReplacer& replaceFunction)
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

    Scrubber Scrubbers::createRegexScrubber(const std::regex& regexPattern,
                                            const Scrubbers::RegexReplacer& replacer)
    {
        return [=](const std::string& input) {
            return scrubRegex(input, regexPattern, replacer);
        };
    }

    Scrubber Scrubbers::createRegexScrubber(const std::regex& regexPattern,
                                            const std::string& replacementText)
    {
        return createRegexScrubber(regexPattern,
                                   [=](const RegexMatch&) { return replacementText; });
    }

    Scrubber Scrubbers::createRegexScrubber(const std::string& regexString,
                                            const std::string& replacementText)
    {
        return createRegexScrubber(std::regex(regexString), replacementText);
    }

    std::string Scrubbers::scrubGuid(const std::string& input)
    {
        static const std::regex regex("[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-["
                                      "0-9a-fA-F]{4}-[0-9a-fA-F]{12}");

        int matchNumber = 0;
        std::map<std::string, int> matchIndices;
        return scrubRegex(input, regex, [&](const RegexMatch& m) {
            auto guid_match = m.str();

            if (matchIndices[guid_match] == 0)
            {
                matchIndices[guid_match] = ++matchNumber;
            }
            return "guid_" + std::to_string(matchIndices[guid_match]);
        });
    }
}
