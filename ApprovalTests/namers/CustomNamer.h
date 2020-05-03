#pragma once

#include "ApprovalTestNamer.h"
#include "../Approvals.h"

#include <functional>
#include <memory>

namespace ApprovalTests
{
    class CustomNamer : public ApprovalTestNamer
    {
    public:
        template <typename ReceivedNameFn, typename ApprovedNameFn>
        CustomNamer(ReceivedNameFn&& receivedNameFn, ApprovedNameFn&& approvedNameFn)
            : receivedNameFn(std::forward<ReceivedNameFn>(receivedNameFn))
            , approvedNameFn(std::forward<ApprovedNameFn>(approvedNameFn))
        {
        }

        virtual std::string getApprovedFile(std::string extensionWithDot) const override
        {
            return approvedNameFn(ApprovalTestNamer::getCurrentTest(), extensionWithDot);
        }

        virtual std::string getReceivedFile(std::string extensionWithDot) const override
        {
            return receivedNameFn(ApprovalTestNamer::getCurrentTest(), extensionWithDot);
        }

        template <typename ReceivedNameFn, typename ApprovedNameFn>
        static ApprovalTests::DefaultNamerDisposer
        useAsDefaultNamer(ReceivedNameFn receivedNameFn, ApprovedNameFn approvedNameFn)
        {
            return ApprovalTests::Approvals::useAsDefaultNamer(
                [receivedNameFn, approvedNameFn]() {
                    return std::make_shared<CustomNamer>(receivedNameFn, approvedNameFn);
                });
        }

    private:
        std::function<std::string(TestName, std::string)> receivedNameFn;
        std::function<std::string(TestName, std::string)> approvedNameFn;
    };

    template <typename ReceivedNameFn, typename ApprovedNameFn>
    inline auto makeCustomNamer(ReceivedNameFn&& receivedNameFn,
                                ApprovedNameFn&& approvedNameFn)
        -> std::shared_ptr<CustomNamer>
    {
        return std::make_shared<CustomNamer>(
            std::forward<ReceivedNameFn>(receivedNameFn),
            std::forward<ApprovedNameFn>(approvedNameFn));
    }
}
