#pragma once

#include "ApprovalTests/core/Reporter.h"
#include "ApprovalTests/utilities/MachineBlocker.h"

#include <memory>
#include <utility>

namespace ApprovalTests
{
    class BlockingReporter : public Reporter
    {
    private:
        std::shared_ptr<Blocker> blocker;

        BlockingReporter() = delete;

    public:
        explicit BlockingReporter(std::shared_ptr<Blocker> blocker_);

        static std::shared_ptr<BlockingReporter>
        onMachineNamed(const std::string& machineName);

        static std::shared_ptr<BlockingReporter>
        onMachinesNotNamed(const std::string& machineName);

        virtual bool report(std::string /*received*/,
                            std::string /*approved*/) const override;
    };
}
