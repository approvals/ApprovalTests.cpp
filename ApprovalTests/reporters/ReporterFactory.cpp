#include "ReporterFactory.h"
#include "ApprovalTests/reporters/AutoApproveReporter.h"
#include "ApprovalTests/reporters/ClipboardReporter.h"

#include <map>
#include <functional>

#define APPROVAL_TESTS_REGISTER_REPORTER(name)                                           \
    map[#name] = []() { return std::unique_ptr<Reporter>(new name); };

namespace ApprovalTests
{
    std::unique_ptr<Reporter>
    ReporterFactory::createReporter(const std::string& reporterName)
    {
        std::map<std::string, std::function<std::unique_ptr<Reporter>()>> map;

        APPROVAL_TESTS_REGISTER_REPORTER(AutoApproveReporter);
        APPROVAL_TESTS_REGISTER_REPORTER(ClipboardReporter);

        auto iter = map.find(reporterName);
        if (iter != map.end())
        {
            return iter->second();
        }

        return std::unique_ptr<Reporter>();
    }
}
