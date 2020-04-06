#ifndef APPROVALTESTS_CPP_FILEUTILSSYSTEMSPECIFIC_H
#define APPROVALTESTS_CPP_FILEUTILSSYSTEMSPECIFIC_H

#include "SystemUtils.h"

namespace ApprovalTests
{
    class FileUtilsSystemSpecific
    {
    public:
        static std::string getCommandLineForCopy(const std::string& source,
                                                 const std::string& destination,
                                                 bool isWindows)
        {
            if (isWindows)
            {
                return std::string("copy /Y ") + "\"" + source + "\" \"" + destination +
                       "\"";
            }
            else
            {
                return std::string("cp ") + "\"" + source + "\" \"" + destination + "\"";
            }
        }

        static void copyFile(const std::string& source, const std::string& destination)
        {
            auto cmd =
                getCommandLineForCopy(source, destination, SystemUtils::isWindowsOs());
            SystemUtils::runSystemCommandOrThrow(cmd);
        }
    };
}
#endif // APPROVALTESTS_CPP_FILEUTILSSYSTEMSPECIFIC_H
