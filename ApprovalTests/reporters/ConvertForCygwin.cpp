#include "ApprovalTests/reporters/ConvertForCygwin.h"

namespace ApprovalTests
{
    std::string ConvertForCygwin::convertProgramForCygwin(const std::string& filePath)
    {
        return "$(cygpath '" + filePath + "')";
    }

    std::string
    ConvertForCygwin::convertFileArgumentForCygwin(const std::string& filePath)
    {
        return "$(cygpath -aw '" + filePath + "')";
    }

    std::string DoNothing::convertProgramForCygwin(const std::string& filePath)
    {
        return filePath;
    }

    std::string DoNothing::convertFileArgumentForCygwin(const std::string& filePath)
    {
        return filePath;
    }
}
