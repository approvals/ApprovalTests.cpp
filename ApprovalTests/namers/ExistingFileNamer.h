#pragma once

#include <utility>
#include "ApprovalTests/core/ApprovalNamer.h"
#include "DefaultNamerFactory.h"

namespace ApprovalTests
{
    class ExistingFileNamer : public ApprovalNamer
    {
        std::string filePath;

    public:
        explicit ExistingFileNamer(std::string filePath_) : filePath(std::move(filePath_))
        {
        }
        virtual std::string getApprovedFile(std::string extensionWithDot) const override
        {
            return DefaultNamerFactory::getDefaultNamer()()->getApprovedFile(
                extensionWithDot);
        }
        virtual std::string
            getReceivedFile(std::string /*extensionWithDot*/) const override
        {
            return filePath;
        }
    };
}
