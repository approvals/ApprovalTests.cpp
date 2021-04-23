#include "Path.h"

namespace ApprovalTests
{

    Path::Path(const std::string& start) : path_(start)
    {
    }

    std::string Path::toString() const
    {
        return toString(separator_);
    }

    std::string Path::toString(const std::string& directoryPathSeparator) const
    {
        if (separator_ == directoryPathSeparator)
        {
            return path_;
        }
        return StringUtils::replaceAll(path_, separator_, directoryPathSeparator);
    }

    Path Path::operator+(const std::string& addition) const
    {
        return Path(path_ + addition);
    }

    Path Path::operator/(const std::string& addition) const
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

    Path Path::operator/(const Path addition) const
    {
        return *this / addition.path_;
    }
}
