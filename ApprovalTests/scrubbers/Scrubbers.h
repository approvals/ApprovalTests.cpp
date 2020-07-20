#pragma once

#include <string>
#include <functional>
#include <regex>

namespace ApprovalTests
{
    using Scrubber = std::function<std::string(const std::string&)>;
    namespace Scrubbers
    {
        std::string doNothing(const std::string& input);

        /**@name Regex-based scrubbers

         See \userguide{how_tos/ScrubNonDeterministicOutput,regular-expressions-regex,Regular Expressions (regex)}
         */
        ///@{
        using RegexMatch = std::sub_match<std::string::const_iterator>;
        using RegexReplacer = std::function<std::string(const RegexMatch&)>;

        std::string scrubRegex(const std::string& input,
                               const std::regex& regex,
                               const RegexReplacer& replaceFunction);

        Scrubber createRegexScrubber(const std::regex& regexPattern,
                                     const RegexReplacer& replacer);

        Scrubber createRegexScrubber(const std::regex& regexPattern,
                                     const std::string& replacementText);

        Scrubber createRegexScrubber(const std::string& regexString,
                                     const std::string& replacementText);
        ///@}

        std::string scrubGuid(const std::string& input);
    }
}
