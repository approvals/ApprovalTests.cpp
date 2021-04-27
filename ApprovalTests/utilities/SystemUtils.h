#pragma once

#include "ApprovalTests/utilities/WinMinGWUtils.h"
#ifdef _WIN32
// ReSharper disable once CppUnusedIncludeDirective
#include <io.h>
#include <direct.h>
#else
// ReSharper disable once CppUnusedIncludeDirective
#include <unistd.h>
#endif

#include "ApprovalTests/utilities/FileUtils.h"
#include "ApprovalTests/utilities/StringUtils.h"
#include "ApprovalTests/utilities/Macros.h"

#include <stdexcept>

namespace ApprovalTests
{
    class SystemUtils
    {
    public:
        static bool isWindowsOs();

        static bool isCygwin();

        static bool isMacOs();

        static std::string getDirectorySeparator();

        // Properly cases the filename, but not the directories, on Windows.
        static std::string checkFilenameCase(const std::string& fullPath);

        static std::string safeGetEnvForWindows(char const* name);

        static std::string safeGetEnvForNonWindows(char const* name);

        //! Return the value of the environment variable, or an empty string if the variable is not set.
        static std::string safeGetEnv(char const* name);

        static std::string getMachineName();

        static void makeDirectoryForWindows(const std::string& directory);

        static void makeDirectoryForNonWindows(const std::string& directory);

        static void makeDirectory(const std::string& directory);

        static void ensureDirectoryExists(const std::string& fullDirectoryPath);

        static void ensureParentDirectoryExists(const std::string& fullFilePath);

        static void runSystemCommandOrThrow(const std::string& command,
                                            bool allowNonZeroExitCodes = false);
    };
}
