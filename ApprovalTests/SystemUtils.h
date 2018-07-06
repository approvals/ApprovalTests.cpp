#ifndef SYSTEMUTILS_H
#define SYSTEMUTILS_H
// <SingleHpp unalterable>
#ifdef _WIN32
	// ReSharper disable once CppUnusedIncludeDirective
	#include <io.h>
	#include <windows.h>
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

	// Properly cases the filename, but not the directories, on Windows.
    static std::string checkFilenameCase(const std::string& fullPath)
    {
        if (!isWindowsOs() || !FileUtils::fileExists(fullPath))
        {
            return fullPath;
        }
#ifdef _WIN32

        WIN32_FIND_DATA findFileData;
        HANDLE hFind = FindFirstFileA(fullPath.c_str(), &findFileData);

        if (hFind != INVALID_HANDLE_VALUE)
        {
            const std::string fixedFilename = findFileData.cFileName;
            const std::string fixedPath = 
                StringUtils::replaceAll( fullPath, StringUtils::toLower(fixedFilename), fixedFilename );
            FindClose(hFind);
            return fixedPath;
        }


#endif
        return fullPath;

    }
};
#endif