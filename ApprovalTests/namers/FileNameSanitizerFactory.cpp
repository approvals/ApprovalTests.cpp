#include <sstream>
#include "FileNameSanitizerFactory.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"
namespace ApprovalTests
{

    std::string FileNameSanitizerFactory::defaultSanitizer(std::string fileName)
    {
        std::stringstream result;
        for (auto ch : fileName)
        {
            if (!ApprovalTestNamer::isForbidden(ch))
            {
                result << ch;
            }
            else
            {
                result << "_";
            }
        }
        return result.str();
    };
    FileNameSanitizer FileNameSanitizerFactory::currentSanitizer = FileNameSanitizerFactory::defaultSanitizer;

}