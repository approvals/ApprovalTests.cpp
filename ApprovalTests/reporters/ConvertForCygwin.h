#pragma once

#include <string>

namespace ApprovalTests
{
    class ConvertForCygwin
    {
    public:
        virtual ~ConvertForCygwin() = default;

        virtual std::string convertProgramForCygwin(const std::string& filePath)
        {
            return "$(cygpath '" + filePath + "')";
        }

        virtual std::string convertFileArgumentForCygwin(const std::string& filePath)
        {
            return "$(cygpath -aw '" + filePath + "')";
        }
    };

    class DoNothing : public ConvertForCygwin
    {
    public:
        std::string convertProgramForCygwin(const std::string& filePath) override
        {
            return filePath;
        }

        std::string convertFileArgumentForCygwin(const std::string& filePath) override
        {
            return filePath;
        }
    };
}
