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
        MachineBlocker(std::string machineName_, bool block_);

        static MachineBlocker onMachineNamed(const std::string& machineName);

        static MachineBlocker onMachinesNotNamed(const std::string& machineName);

        virtual bool isBlockingOnThisMachine() const override;
    };
}
