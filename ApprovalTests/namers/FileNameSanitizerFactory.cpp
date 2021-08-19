#include <sstream>
#include "FileNameSanitizerFactory.h"
namespace ApprovalTests
{
    bool FileNameSanitizerFactory::isForbidden(char c)
    {
        static std::string forbiddenChars("\\/:?\"<>|' ");
        return std::string::npos != forbiddenChars.find(c);
    }

    std::string FileNameSanitizerFactory::defaultSanitizer(std::string fileName)
    {
        std::stringstream result;
        for (auto ch : fileName)
        {
            if (!isForbidden(ch))
            {
                result << ch;
            }
            else
            {
                result << "_";
            }
        }
        return result.str();
    }

    FileNameSanitizer FileNameSanitizerFactory::currentSanitizer =
        FileNameSanitizerFactory::defaultSanitizer;

}
