#ifndef APPROVALTESTS_CPP_MACHINEBLOCKER_H
#define APPROVALTESTS_CPP_MACHINEBLOCKER_H

#include "Blocker.h"
#include "../SystemUtils.h"

#include <memory>

namespace ApprovalTests {
class MachineBlocker : public Blocker
{
private:
    std::string machineName;
    bool block;

    MachineBlocker() = delete;

public:
    MachineBlocker( const std::string& machineName, bool block ) : machineName(machineName), block(block)
    {
    }

    static MachineBlocker onMachineNamed( const std::string& machineName )
    {
        return MachineBlocker(machineName, true);
    }

    static MachineBlocker onMachinesNotNamed( const std::string& machineName )
    {
        return MachineBlocker(machineName, false);
    }

    virtual bool isBlockingOnThisMachine() const override
    {
        const auto isMachine = (ApprovalTests::SystemUtils::getMachineName() == machineName);
        return isMachine == block;
    }
};
}

#endif //APPROVALTESTS_CPP_MACHINEBLOCKER_H
