#include "ApprovalTests/utilities/MachineBlocker.h"

namespace ApprovalTests
{
    MachineBlocker::MachineBlocker(std::string machineName_, bool block_)
        : machineName(std::move(machineName_)), block(block_)
    {
    }

    MachineBlocker MachineBlocker::onMachineNamed(const std::string& machineName)
    {
        return MachineBlocker(machineName, true);
    }

    MachineBlocker MachineBlocker::onMachinesNotNamed(const std::string& machineName)
    {
        return MachineBlocker(machineName, false);
    }

    bool MachineBlocker::isBlockingOnThisMachine() const
    {
        const auto isMachine = (SystemUtils::getMachineName() == machineName);
        return isMachine == block;
    }
}
