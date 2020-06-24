#include "ApprovalTests/utilities/FileUtilsSystemSpecific.h"

namespace ApprovalTests
{
    std::string FileUtilsSystemSpecific::getCommandLineForCopy(
        const std::string& source, const std::string& destination, bool isWindows)
    {
        if (isWindows)
        {
            return std::string("copy /Y ") + "\"" + source + "\" \"" + destination + "\"";
        }
        else
        {
            return std::string("cp ") + "\"" + source + "\" \"" + destination + "\"";
        }
    }

    void FileUtilsSystemSpecific::copyFile(const std::string& source,
                                           const std::string& destination)
    {
        auto cmd = getCommandLineForCopy(source, destination, SystemUtils::isWindowsOs());
        SystemUtils::runSystemCommandOrThrow(cmd);
    }
}
