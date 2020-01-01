#ifndef APPROVALTESTS_CPP_MACHINEBLOCKER_H
#define APPROVALTESTS_CPP_MACHINEBLOCKER_H

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
        MachineBlocker(std::string machineName, bool block)
            : machineName(std::move(machineName)), block(block)
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
            const auto isMachine =
                (SystemUtils::getMachineName() == machineName);
            return isMachine == block;
        }
    };
}

#endif //APPROVALTESTS_CPP_MACHINEBLOCKER_H
