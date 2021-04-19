#pragma once

#include <utility>
#include "ApprovalTests/utilities/SystemUtils.h"
#include "ApprovalTests/namers/NamerFactory.h"
#include "ApprovalTests/core/ApprovalNamer.h"

namespace ApprovalTests
{
    class TemplatedCustomNamer : public ApprovalTests::ApprovalNamer
    {
    private:
        ApprovalTests::ApprovalTestNamer namer_;
        std::string template_;

    public:
        explicit TemplatedCustomNamer(const std::string& templateString);

        APPROVAL_TESTS_NO_DISCARD
        std::string constructFromTemplate(const std::string& extensionWithDot,
                                          const std::string& approvedOrReceived) const;

        APPROVAL_TESTS_NO_DISCARD
        std::string getApprovedFile(std::string extensionWithDot) const override;

        APPROVAL_TESTS_NO_DISCARD
        std::string getReceivedFile(std::string extensionWithDot) const override;
    };
}
