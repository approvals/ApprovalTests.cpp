#ifndef SYSTEMUTILS_H
#define SYSTEMUTILS_H
// <SingleHpp unalterable>
#ifdef _WIN32
// ReSharper disable once CppUnusedIncludeDirective
#include <io.h>
#include <windows.h>
//#include <iostream>
//#define BUFSIZE 4096
#else
// ReSharper disable once CppUnusedIncludeDirective
#include <unistd.h>
#endif
// </SingleHpp>

#include "FileUtils.h"
#include "StringUtils.h"

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

    // Fix problem that for some compiler arguments, Visual Studio's __FILE__
    // macro returns all-lower-case paths.
    // This fixes the filename part of the path, but not the directory part.
    static std::string checkFilenameCase(const std::string& fullPath)
    {
        if (!isWindowsOs() || !FileUtils::fileExists(fullPath))
        {
            return fullPath;
        }
#ifdef _WIN32

        // From https://msdn.microsoft.com/en-us/library/windows/desktop/aa364418(v=vs.85).aspx
        WIN32_FIND_DATA findFileData;
        HANDLE hFind = FindFirstFileA(fullPath.c_str(), &findFileData);

        if (hFind == INVALID_HANDLE_VALUE)
        {
            //std::cout << "FindFirstFile failed " << GetLastError() << std::endl;
        }
        else
        {
            // Warning - this only fixes the filename, and not the path
            //std::cout << "The first file found is " << findFileData.cFileName << std::endl;
            const std::string fixedFilename = findFileData.cFileName;
            const std::string fixedPath = 
                StringUtils::replaceAll(
                    fullPath,
                    StringUtils::toLower(fixedFilename),
                    fixedFilename );
            FindClose(hFind);
            return fixedPath;
        }

        /*

        // https://msdn.microsoft.com/en-us/library/windows/desktop/aa364963(v=vs.85).aspx
        // Second attempt, which didn't work because the case of the path wasn't changed -
        // the original path was returned

        DWORD  retval;
        TCHAR  buffer[BUFSIZE+1]=TEXT(""); 
        TCHAR** lppPart={nullptr};

        // Retrieve the full path name for a file. 
        // The file does not need to exist.

        retval = GetFullPathName(fullPath.c_str(),
                        BUFSIZE,
                        buffer,
                        lppPart);
    
        if (retval == 0) 
        {
            // Handle an error condition.
            std::cout << "GetFullPathName failed " << GetLastError() << std::endl;
        }
        else 
        {
            std::cout << "The full path name is: " << buffer << std::endl;
            return std::string(buffer);
        }
        */

#endif
        return fullPath;

    }
};
#endif