#include <sstream>
#include "ApprovalTests/namers/FileNameSanitizerDisposer.h"

namespace ApprovalTests
{

    FileNameSanitizerDisposer::FileNameSanitizerDisposer(FileNameSanitizer sanitizer)
    {
        previous_result = std::move(FileNameSanitizerFactory::currentSanitizer);
        FileNameSanitizerFactory::currentSanitizer = std::move(sanitizer);
    }

    FileNameSanitizerDisposer::~FileNameSanitizerDisposer()
    {
        FileNameSanitizerFactory::currentSanitizer = std::move(previous_result);
    }
}
