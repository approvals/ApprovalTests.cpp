#include "ReporterFactory.h"
#include "ApprovalTests/reporters/ClipboardReporter.h"

#include <map>
#include <functional>

namespace ApprovalTests
{
    std::unique_ptr<Reporter>
    ReporterFactory::createReporter(const std::string& reporterName)
    {
        std::map<std::string, std::function<std::unique_ptr<Reporter>()>> map;
        map["ClipboardReporter"] = []() {
            return std::unique_ptr<Reporter>(new ClipboardReporter);
        };

        auto iter = map.find(reporterName);
        if (iter != map.end())
        {
            return iter->second();
        }

        return std::unique_ptr<Reporter>();
    }
}
