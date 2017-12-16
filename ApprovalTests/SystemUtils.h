#ifndef SYSTEMUTILS_H
#define SYSTEMUTILS_H
// <SingleHpp unalterable>
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
// </SingleHpp>


class SystemUtils
{
public:
    static bool isWindowsOs()
    {
#ifdef _WIN32
        return true;
#else
        return false;
#endif 

    }

    static std::string getDirectorySeparator()
    {
        return isWindowsOs() ? "\\" : "/";
    }


};
#endif