#ifndef APPROVALTESTS_CPP_DEFAULTNAMERFACTORY_H
#define APPROVALTESTS_CPP_DEFAULTNAMERFACTORY_H

#include "ApprovalTests/core/ApprovalNamer.h"
#include "ApprovalTestNamer.h"

#include <memory>
#include <utility>

namespace ApprovalTests {

    using NamerCreator = std::function<std::shared_ptr<ApprovalNamer>()>;

//! Implementation detail of Approvals::useAsDefaultNamer()
class DefaultNamerFactory
{
private:
    static NamerCreator& defaultNamer()
    {
        static NamerCreator namer = [](){return std::make_shared<ApprovalTestNamer>();};
        return namer;
    }

public:
    static NamerCreator getDefaultNamer()
    {
        return defaultNamer();
    }
    
    static void setDefaultNamer( NamerCreator namer)
    {
        defaultNamer() = std::move(namer);
    }

};
}

#endif //APPROVALTESTS_CPP_DEFAULTNAMERFACTORY_H
