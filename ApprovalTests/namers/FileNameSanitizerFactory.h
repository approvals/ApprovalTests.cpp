#pragma once
#include <functional>

namespace ApprovalTests
{
    using FileNameSanitizer = std::function<std::string(std::string)>;

    class FileNameSanitizerFactory
    {
    public:
        static bool isForbidden(char c);
        static std::string defaultSanitizer(std::string fileName);
        static FileNameSanitizer currentSanitizer;
    };
}
