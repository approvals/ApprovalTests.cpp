#ifndef APPROVALTESTS_CPP_FILEUTILSSYSTEMSPECIFIC_H
#define APPROVALTESTS_CPP_FILEUTILSSYSTEMSPECIFIC_H

#include "SystemUtils.h"

namespace ApprovalTests {
class FileUtilsSystemSpecific
{
public:
    static std::string getCommandLineForCopy(std::string source, std::string destination, bool isWindows)
    {
        if (isWindows) {
            return std::string("copy /Y ") + "\"" + source + "\" \"" + destination + "\"";
        } else {
            return std::string("cp ") + "\"" + source + "\" \"" + destination + "\"";
        }
    }

    static void copyFile( std::string source, std::string destination )
    {
        system( getCommandLineForCopy(source, destination, SystemUtils::isWindowsOs()).c_str() );
    }
};
}
#endif
