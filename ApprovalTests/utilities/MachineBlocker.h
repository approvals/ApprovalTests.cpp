#pragma once

#include "Blocker.h"
#include <utility>
#include "SystemUtils.h"

namespace ApprovalTests
{
    class MachineBlocker : public Blocker
    {
    private:
        std::string machineName;
        bool block;

        MachineBlocker() = delete;

    public:
        MachineBlocker(std::string machineName_, bool block_)
            : machineName(std::move(machineName_)), block(block_)
        {
        }

        static MachineBlocker onMachineNamed(const std::string& machineName)
        {
            return MachineBlocker(machineName, true);
        }

        static MachineBlocker onMachinesNotNamed(const std::string& machineName)
        {
            return MachineBlocker(machineName, false);
        }

        virtual bool isBlockingOnThisMachine() const override
        {
            const auto isMachine = (SystemUtils::getMachineName() == machineName);
            return isMachine == block;
        }
    };
}
