#pragma once

#include "DefaultNamerFactory.h"
#include "ApprovalTests/utilities/Macros.h"

namespace ApprovalTests
{
    using FileNameSanitizer = std::function<std::string(std::string)>;
    class APPROVAL_TESTS_NO_DISCARD FileNameSanitizerDisposer
    {
    private:
        FileNameSanitizer previous_result;
    public:
        static FileNameSanitizer current;

    public:
        explicit FileNameSanitizerDisposer(FileNameSanitizer sanitizer);
        FileNameSanitizerDisposer(const FileNameSanitizerDisposer&) = default;

        ~FileNameSanitizerDisposer();
    };
}
