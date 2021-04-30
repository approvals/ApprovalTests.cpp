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
        Path(const std::string& start);

        std::string toString() const;
        std::string toString(const std::string& directoryPathSeparator) const;

        Path operator+(const std::string& addition) const;
        Path operator/(const std::string& addition) const;
        Path operator/(const Path addition) const;

        static std::string normalizeSeparators(const std::string& path);
        std::string removeRedundantDirectorySeparators(std::string path) const;
    };
}
