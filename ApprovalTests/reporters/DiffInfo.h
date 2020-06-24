#pragma once

#include <string>
#include <utility>
#include <vector>

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
        static std::string receivedFileTemplate();

        static std::string approvedFileTemplate();

        static std::string programFileTemplate();

        static std::string getDefaultArguments();

        DiffInfo(std::string program_, Type type_);

        DiffInfo(std::string program_, std::string arguments_, Type type_);

        std::string program;
        std::string arguments;
        Type type;

        static std::vector<std::string> getProgramFileLocations();

        std::string getProgramForOs() const;
    };
}
