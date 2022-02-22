#pragma once

#include <utility>
#include "ApprovalTests/core/ApprovalNamer.h"
#include "ApprovalTests/core/Options.h"

namespace ApprovalTests
{
    class ExistingFileNamer : public ApprovalNamer
    {
        std::string filePath;
        const Options& options_;

    public:
        explicit ExistingFileNamer(std::string filePath_, const Options& options);
        ExistingFileNamer(const ExistingFileNamer& x)
            : filePath(x.filePath), options_(x.options_)
        {
        }
        ExistingFileNamer(ExistingFileNamer&& x)
            : filePath(x.filePath), options_(x.options_)
        {
        }

        virtual std::string getApprovedFile(std::string extensionWithDot) const override;

        virtual std::string
            getReceivedFile(std::string /*extensionWithDot*/) const override;
    };
}
