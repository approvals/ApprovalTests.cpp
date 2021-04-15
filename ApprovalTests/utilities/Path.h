#pragma once

#include "ApprovalTests/utilities/StringUtils.h"
#include "ApprovalTests/utilities/SystemUtils.h"

#include <string>

namespace ApprovalTests
{
    class Path
    {
        std::string path_;
        std::string separator_ = SystemUtils::getDirectorySeparator();

    public:
        Path(const std::string& start) : path_(start)
        {
        }

        std::string toString() const
        {
            return toString(separator_);
        }

        std::string toString(const std::string& directoryPathSeparator) const
        {
            if (separator_ == directoryPathSeparator)
            {
                return path_;
            }
            return StringUtils::replaceAll(path_, separator_, directoryPathSeparator);
        }

        Path operator/(const std::string& addition) const
        {
            auto first = path_;
            if (StringUtils::endsWith(first, separator_))
            {
                first = first.substr(0, path_.size() - 1);
            }

            auto second = addition;
            if (StringUtils::beginsWith(second, separator_))
            {
                second = second.substr(1);
            }

            return Path(first + separator_ + second);
        }
    };
}
