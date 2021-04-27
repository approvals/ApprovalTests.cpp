#include "ApprovalTests/utilities/SystemUtils.h"

#include <sys/stat.h>

namespace ApprovalTests
{
    bool SystemUtils::isWindowsOs()
    {
#ifdef _WIN32
        return true;
#else
        return false;
#endif
    }

    bool SystemUtils::isCygwin()
    {
#ifdef __CYGWIN__
        return true;
#else
        return false;
#endif
    }

    bool SystemUtils::isMacOs()
    {
#ifdef __APPLE__
        return true;
#else
        return false;
#endif
    }
    std::string SystemUtils::getDirectorySeparator()
    {
        return isWindowsOs() ? "\\" : "/";
    }

    std::string SystemUtils::checkFilenameCase(const std::string& fullPath)
    {
        if (!isWindowsOs() || !FileUtils::fileExists(fullPath))
        {
            return fullPath;
        }
#ifdef _WIN32

        _finddata_t findFileData;
        auto hFind = _findfirst(fullPath.c_str(), &findFileData);

        if (hFind != -1)
        {
            const std::string fixedFilename = findFileData.name;
            const std::string fixedPath = StringUtils::replaceAll(
                fullPath, StringUtils::toLower(fixedFilename), fixedFilename);
            _findclose(hFind);
            return fixedPath;
        }

#endif
        return fullPath;
    }

    std::string SystemUtils::safeGetEnvForWindows(const char* name)
    {
        APPROVAL_TESTS_UNUSED(name);
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

    std::string SystemUtils::safeGetEnvForNonWindows(const char* name)
    {
        APPROVAL_TESTS_UNUSED(name);
        char* p = nullptr;
#ifndef _WIN32
        p = getenv(name);
#endif
        return (p != nullptr) ? p : std::string();
    }

    std::string SystemUtils::safeGetEnv(const char* name)
    {
        return isWindowsOs() ? safeGetEnvForWindows(name) : safeGetEnvForNonWindows(name);
    }

    std::string SystemUtils::getMachineName()
    {
        auto name = safeGetEnv("COMPUTERNAME");
        if (!name.empty())
        {
            return name;
        }

        name = safeGetEnv("HOSTNAME");
        if (!name.empty())
        {
            return name;
        }

        return "Unknown Computer";
    }

    void SystemUtils::makeDirectoryForWindows(const std::string& directory)
    {
        APPROVAL_TESTS_UNUSED(directory);
#ifdef _WIN32
        int nError = _mkdir(directory.c_str());
        if (nError != 0)
        {
            std::string helpMessage =
                std::string("Unable to create directory: ") + directory;
            throw std::runtime_error(helpMessage);
        }
#endif
    }

    void SystemUtils::makeDirectoryForNonWindows(const std::string& directory)
    {
        APPROVAL_TESTS_UNUSED(directory);
#ifndef _WIN32
        mode_t nMode = 0733; // UNIX style permissions
        int nError = mkdir(directory.c_str(), nMode);
        if (nError != 0)
        {
            std::string helpMessage =
                std::string("Unable to create directory: ") + directory;
            throw std::runtime_error(helpMessage);
        }
#endif
    }

    void SystemUtils::makeDirectory(const std::string& directory)
    {
        makeDirectoryForWindows(directory);
        makeDirectoryForNonWindows(directory);
    }

    void SystemUtils::ensureDirectoryExists(const std::string& fullDirectoryPath)
    {
        if (!FileUtils::fileExists(fullDirectoryPath))
        {
            makeDirectory(fullDirectoryPath);
        }
    }

    void SystemUtils::ensureParentDirectoryExists(const std::string& fullFilePath)
    {
        const std::string parentDirectory = FileUtils::getDirectory(fullFilePath);
        if (!parentDirectory.empty())
        {
            SystemUtils::ensureDirectoryExists(parentDirectory);
        }
    }

    void SystemUtils::runSystemCommandOrThrow(const std::string& command,
                                              bool allowNonZeroExitCodes)
    {
        int exitCode = system(command.c_str());

        if (!allowNonZeroExitCodes && exitCode != 0)
        {
            throw std::runtime_error(command + ": failed with exit code " +
                                     std::to_string(exitCode));
        }
    }
}
