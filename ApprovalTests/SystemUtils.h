#ifndef SYSTEMUTILS_H
#define SYSTEMUTILS_H

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif


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