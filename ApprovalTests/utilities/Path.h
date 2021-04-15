#pragma once

#include "ApprovalTests/utilities/StringUtils.h"
#include "ApprovalTests/utilities/SystemUtils.h"

#include <string>

namespace ApprovalTests
{
    class Path
    {
        std::string path_;

    public:
        Path(const std::string& start) : path_(start)
        {
        }

        std::string toString() const
        {
            return toString(SystemUtils::getDirectorySeparator());
        }

        std::string toString(const std::string& directoryPathSeparator) const
        {
            if (SystemUtils::getDirectorySeparator() == directoryPathSeparator)
            {
                return path_;
            }
            return StringUtils::replaceAll(
                path_, SystemUtils::getDirectorySeparator(), directoryPathSeparator);
        }

        Path operator/(const std::string& addition) const
        {
            return Path(path_ + SystemUtils::getDirectorySeparator() + addition);
        }
    };
}
