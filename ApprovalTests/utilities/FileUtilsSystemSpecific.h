#pragma once

#include "ApprovalTests/utilities/SystemUtils.h"

namespace ApprovalTests
{
    class FileUtilsSystemSpecific
    {
    public:
        static std::string getCommandLineForCopy(const std::string& source,
                                                 const std::string& destination,
                                                 bool isWindows);

        static void copyFile(const std::string& source, const std::string& destination);
    };
}
