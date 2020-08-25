#include "ReporterFactory.h"
#include "ApprovalTests/reporters/ClipboardReporter.h"

namespace ApprovalTests
{
    std::unique_ptr<Reporter> ReporterFactory::createReporter(const std::string&)
    {
        return std::unique_ptr<Reporter>(new ClipboardReporter);
    }
}
