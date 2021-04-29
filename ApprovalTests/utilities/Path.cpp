#include "Path.h"

namespace ApprovalTests
{

    Path::Path(const std::string& start) : path_(normalizeSeparators(start))
    {
    }

    std::string Path::toString() const
    {
        return toString(separator_);
    }

    std::string Path::toString(const std::string& directoryPathSeparator) const
    {
        auto path = path_;
        path = StringUtils::replaceAll(path, "//", "/");
        path = StringUtils::replaceAll(path, "\\\\", "\\");
        if (separator_ == directoryPathSeparator)
        {
            return path;
        }
        return StringUtils::replaceAll(path, separator_, directoryPathSeparator);
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

    std::string Path::normalizeSeparators(const std::string& path)
    {
        auto separator = SystemUtils::getDirectorySeparator();
        auto otherSeparator = (separator == "/" ? "\\" : "/");
        return StringUtils::replaceAll(path, otherSeparator, separator);
    }
}
