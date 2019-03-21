#ifndef SYSTEMUTILS_H
#define SYSTEMUTILS_H
// <SingleHpp unalterable>
#ifdef _WIN32
    // ReSharper disable once CppUnusedIncludeDirective
    #include <io.h>
    #include <windows.h>
    #include <direct.h>
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

        WIN32_FIND_DATAA findFileData;
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

    static std::string safeGetEnvForWindows(char const *name)
    {
#ifdef _WIN32
        // We use getenv_s on Windows, as use of getenv there gives:
        //      warning C4996: 'getenv': This function or variable may be unsafe. Consider using _dupenv_s instead.
        //      To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.

        size_t size;
        getenv_s(&size, nullptr, 0, name);

        if (size != 0)
        {
            std::string result;
            result.resize(size);
            getenv_s(&size, &*result.begin(), size, name);
            result.pop_back();
            return result;
        }
#endif
        return std::string();
    }

    static std::string safeGetEnvForNonWindows(char const *name)
    {
        char* p = nullptr;
#ifndef _WIN32
        p = getenv(name);
#endif
        return (p != nullptr) ? p : std::string();
    }

    //! Return the value of the environment variable, or an empty string if the variable is not set.
    static std::string safeGetEnv(char const *name)
    {
        return isWindowsOs() ? safeGetEnvForWindows(name) : safeGetEnvForNonWindows(name);
    }

    static void makeDirectoryForWindows(std::string directory)
    {
#ifdef _WIN32
        int nError = _mkdir(directory.c_str());
        if (nError != 0)
        {
            std::string helpMessage = std::string("Unable to create directory: ") + directory;
            throw std::runtime_error( helpMessage );
        }
#endif
    }

    static void makeDirectoryForNonWindows(std::string directory)
    {
#ifndef _WIN32
        mode_t nMode = 0733; // UNIX style permissions
        int nError = mkdir(directory.c_str(),nMode);
        if (nError != 0)
        {
            std::string helpMessage = std::string("Unable to create directory: ") + directory;
            throw std::runtime_error( helpMessage );
        }
#endif
    }

    static void makeDirectory(std::string directory)
    {
        makeDirectoryForWindows(directory);
        makeDirectoryForNonWindows(directory);
    }

    static void ensureDirectoryExists(std::string fullFilePath)
    {
        if (!FileUtils::fileExists(fullFilePath))
        {
            makeDirectory(fullFilePath);
        }
    }
};
#endif
