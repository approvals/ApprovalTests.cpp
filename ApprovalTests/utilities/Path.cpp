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
        std::string path = removeRedundantDirectorySeparators(path_);

        if (separator_ == directoryPathSeparator)
        {
            return path;
        }
        return StringUtils::replaceAll(path, separator_, directoryPathSeparator);
    }

    std::string Path::removeRedundantDirectorySeparators(std::string path) const
    {
        bool changed = true;
        while (changed)
        {
            std::string reducePath = path;
            reducePath = StringUtils::replaceAll(reducePath, "//", "/");
            reducePath = StringUtils::replaceAll(reducePath, "\\\\", "\\");
            changed = (reducePath != path);
            path = reducePath;
        };
        return path;
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
