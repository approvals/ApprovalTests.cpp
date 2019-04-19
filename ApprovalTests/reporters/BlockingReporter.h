#ifndef APPROVALTESTS_CPP_BLOCKINGREPORTER_H
#define APPROVALTESTS_CPP_BLOCKINGREPORTER_H

#include "Reporter.h"
#include "../SystemUtils.h"
#include "../utilities/MachineBlocker.h"

#include <memory>

class BlockingReporter : public Reporter
{
private:
    std::shared_ptr<Blocker> blocker;

    BlockingReporter() = delete;

public:
    BlockingReporter( std::shared_ptr<Blocker> blocker ) : blocker(blocker)
    {
    }

    static std::shared_ptr<BlockingReporter> onMachineNamed( const std::string& machineName )
    {
        auto machineBlocker = std::make_shared<MachineBlocker>( MachineBlocker::onMachineNamed(machineName) );
        return std::make_shared<BlockingReporter>(machineBlocker);
    }

    static std::shared_ptr<BlockingReporter> onMachinesNotNamed( const std::string& machineName )
    {
        auto machineBlocker = std::make_shared<MachineBlocker>( MachineBlocker::onMachinesNotNamed(machineName) );
        return std::make_shared<BlockingReporter>(machineBlocker);
    }

    virtual bool report(std::string /*received*/, std::string /*approved*/) const override
    {
        return blocker->isBlockingOnThisMachine();
    }
};

#endif //APPROVALTESTS_CPP_BLOCKINGREPORTER_H
