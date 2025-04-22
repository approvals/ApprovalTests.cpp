#pragma once
#include "utilities/FileUtils.h"
#include "utilities/SystemUtils.h"

auto constexpr APPROVAL_TEMP_DIRECTORY = "./.approval_tests_temp";

class ApprovalFileLog
{
public:
    // Static initializer to ensure an _empty_ log file is created
    static void initialize();

    // Function to get the log file path
    static std::string getLogFilePath();

    // Function to log the approved file path
    static void log(const std::string& filePath);
};
