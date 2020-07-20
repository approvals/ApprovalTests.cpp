#include "ApprovalTests/reporters/DefaultReporter.h"
#include "DefaultReporterFactory.h"

namespace ApprovalTests
{
    bool DefaultReporter::report(std::string received, std::string approved) const
    {
        return DefaultReporterFactory::getDefaultReporter()->report(received, approved);
    }
}
