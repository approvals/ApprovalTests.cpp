#ifndef APPROVALTESTS_CPP_DIFFINFO_H
#define APPROVALTESTS_CPP_DIFFINFO_H

#include <string>
#include <utility>
#include <vector>
#include "ApprovalTests/utilities/FileUtils.h"
#include "ApprovalTests/utilities/StringUtils.h"
#include "ApprovalTests/utilities/SystemUtils.h"

namespace ApprovalTests
{
    enum class Type
    {
        TEXT,
        IMAGE,
        TEXT_AND_IMAGE
    };

    struct DiffInfo
    {
        static std::string receivedFileTemplate()
        {
            return "{Received}";
        }

        static std::string approvedFileTemplate()
        {
            return "{Approved}";
        }

        static std::string programFileTemplate()
        {
            return "{ProgramFiles}";
        }

        static std::string getDefaultArguments()
        {
            return receivedFileTemplate() + ' ' + approvedFileTemplate();
        }

        DiffInfo(std::string program, Type type)
            : program(std::move(program)), arguments(getDefaultArguments()), type(type)
        {
        }
        DiffInfo(std::string program, std::string arguments, Type type)
            : program(std::move(program)), arguments(std::move(arguments)), type(type)
        {
        }
        std::string program;
        std::string arguments;
        Type type;

        static std::vector<std::string> getProgramFileLocations()
        {
            std::vector<std::string> possibleWindowsPaths;
            const std::vector<const char*> envVars = {
                "ProgramFiles", "ProgramW6432", "ProgramFiles(x86)"};

            for (const auto& envVar : envVars)
            {
                std::string envVarValue = SystemUtils::safeGetEnv(envVar);
                if (!envVarValue.empty())
                {
                    envVarValue += '\\';
                    possibleWindowsPaths.push_back(envVarValue);
                }
            }
            return possibleWindowsPaths;
        }

        std::string getProgramForOs() const
        {
            std::string result = program;
            if (result.rfind(programFileTemplate(), 0) == 0)
            {
                std::vector<std::string> possibleWindowsPaths = getProgramFileLocations();
                for (const auto& path : possibleWindowsPaths)
                {
                    auto result1 =
                        StringUtils::replaceAll(result, programFileTemplate(), path);
                    if (FileUtils::fileExists(result1))
                    {
                        return result1;
                    }
                }
            }
            return result;
        }
    };
}

#endif //APPROVALTESTS_CPP_DIFFINFO_H
