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
                                                           Type type = Type::TEXT)
        {
            return create(std::move(path), DiffInfo::getDefaultArguments(), type);
        }

        static std::shared_ptr<GenericDiffReporter>
        create(std::string path, std::string arguments, Type type = Type::TEXT)
        {
            DiffInfo info(std::move(path), std::move(arguments), type);
            return std::make_shared<GenericDiffReporter>(info);
        }

        static std::shared_ptr<GenericDiffReporter>
        createForegroundReporter(std::string path, Type type = Type::TEXT)
        {
            return createForegroundReporter(
                std::move(path), DiffInfo::getDefaultArguments(), type);
        }

        static std::shared_ptr<GenericDiffReporter> createForegroundReporter(
            std::string path, std::string arguments, Type type = Type::TEXT)
        {
            DiffInfo info(std::move(path), std::move(arguments), type);
            auto reporter = std::make_shared<GenericDiffReporter>(info);
            reporter->launcher.setForeground(true);
            return reporter;
        }
    };
}
