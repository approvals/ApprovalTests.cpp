#ifndef APPROVALTESTS_CPP_MACHINEBLOCKER_H
#define APPROVALTESTS_CPP_MACHINEBLOCKER_H

#include "../SystemUtils.h"

#include <memory>

class MachineBlocker
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

    bool isBlockingOnThisMachine() const
    {
        const auto isMachine = (SystemUtils::getMachineName() == machineName);
        return isMachine == block;
    }
};


#endif //APPROVALTESTS_CPP_MACHINEBLOCKER_H
