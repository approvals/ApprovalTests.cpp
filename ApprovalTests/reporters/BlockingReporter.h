#ifndef APPROVALTESTS_CPP_BLOCKINGREPORTER_H
#define APPROVALTESTS_CPP_BLOCKINGREPORTER_H

#include "Reporter.h"
#include "../SystemUtils.h"

class BlockingReporter : public Reporter
{
private:
    std::string machineName;
    bool block;

    BlockingReporter() = delete;

    BlockingReporter( const std::string& machineName, bool block ) : machineName(machineName), block(block)
    {
    }
public:

    static BlockingReporter onMachineNamed( const std::string& machineName )
    {
        return BlockingReporter(machineName, true);
    }

    static BlockingReporter onMachinesNotNamed( const std::string& machineName )
    {
        return BlockingReporter(machineName, false);
    }

    virtual bool report(std::string received, std::string approved) const override
    {
        const auto isMachine = (SystemUtils::getMachineName() == machineName);
        return isMachine == block;
    }
};

#endif //APPROVALTESTS_CPP_BLOCKINGREPORTER_H
