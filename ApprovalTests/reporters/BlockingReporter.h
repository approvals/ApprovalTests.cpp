#ifndef APPROVALTESTS_CPP_BLOCKINGREPORTER_H
#define APPROVALTESTS_CPP_BLOCKINGREPORTER_H

#include "ApprovalTests/core/Reporter.h"
#include "../utilities/MachineBlocker.h"

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
        explicit BlockingReporter(std::shared_ptr<Blocker> blocker)
            : blocker(std::move(blocker))
        {
        }

        static std::shared_ptr<BlockingReporter>
        onMachineNamed(const std::string& machineName)
        {
            auto machineBlocker = std::make_shared<MachineBlocker>(
                MachineBlocker::onMachineNamed(machineName));
            return std::make_shared<BlockingReporter>(machineBlocker);
        }

        static std::shared_ptr<BlockingReporter>
        onMachinesNotNamed(const std::string& machineName)
        {
            auto machineBlocker = std::make_shared<MachineBlocker>(
                MachineBlocker::onMachinesNotNamed(machineName));
            return std::make_shared<BlockingReporter>(machineBlocker);
        }

        virtual bool report(std::string /*received*/,
                            std::string /*approved*/) const override
        {
            return blocker->isBlockingOnThisMachine();
        }
    };
}

#endif //APPROVALTESTS_CPP_BLOCKINGREPORTER_H
