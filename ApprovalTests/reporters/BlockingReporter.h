#ifndef APPROVALTESTS_CPP_BLOCKINGREPORTER_H
#define APPROVALTESTS_CPP_BLOCKINGREPORTER_H

#include "Reporter.h"
#include "../SystemUtils.h"
#include "../utilities/MachineBlocker.h"

#include <memory>

class BlockingReporter : public Reporter
{
private:
    MachineBlocker blocker;

    BlockingReporter() = delete;

public:
    BlockingReporter( const MachineBlocker& blocker ) : blocker(blocker)
    {
    }

    static std::shared_ptr<BlockingReporter> onMachineNamed( const std::string& machineName )
    {
        return std::make_shared<BlockingReporter>( MachineBlocker(machineName, true) );
    }

    static std::shared_ptr<BlockingReporter> onMachinesNotNamed( const std::string& machineName )
    {
        return std::make_shared<BlockingReporter>( MachineBlocker(machineName, false) );
    }

    virtual bool report(std::string received, std::string approved) const override
    {
        return blocker.isBlockingOnThisMachine();
    }
};

#endif //APPROVALTESTS_CPP_BLOCKINGREPORTER_H
