#include "ApprovalFileLog.hpp"
#include <fstream>

void ApprovalFileLog::initialize()
{
    static bool isInitialized{false};
    if (isInitialized)
    {
        return;
    }
    isInitialized = true;
    ApprovalTests::FileUtils::writeToFile(getLogFilePath(), "");
}

std::string ApprovalFileLog::getLogFilePath()
{
    //auto const rootDirectory = ApprovalTests::TestName::getRootDirectory();
    auto const rootDirectory = "";
    // Note: Need to figure out where the actual root directory is.
    std::string const filePath =
        rootDirectory + std::string(APPROVAL_TEMP_DIRECTORY) + "/.approved_files.log";
    ApprovalTests::SystemUtils::ensureDirectoryExists(APPROVAL_TEMP_DIRECTORY);
    return filePath;
}

void ApprovalFileLog::log(const std::string& filePath)
{
    initialize();
    std::ofstream ofs(getLogFilePath(), std::ios::app);
    ofs << filePath << std::endl;
}
