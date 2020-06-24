#pragma once

#include "DiffInfo.h"
#include "GenericDiffReporter.h"
#include <memory>

namespace ApprovalTests
{
    class CustomReporter
    {
    public:
        static std::shared_ptr<GenericDiffReporter> create(std::string path,
                                                           Type type = Type::TEXT);

        static std::shared_ptr<GenericDiffReporter>
        create(std::string path, std::string arguments, Type type = Type::TEXT);

        static std::shared_ptr<GenericDiffReporter>
        createForegroundReporter(std::string path, Type type = Type::TEXT);

        static std::shared_ptr<GenericDiffReporter> createForegroundReporter(
            std::string path, std::string arguments, Type type = Type::TEXT);
    };
}
