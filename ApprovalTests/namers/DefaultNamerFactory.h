#ifndef APPROVALTESTS_CPP_DEFAULTNAMERFACTORY_H
#define APPROVALTESTS_CPP_DEFAULTNAMERFACTORY_H

#include "ApprovalTests/core/ApprovalNamer.h"
#include "ApprovalTestNamer.h"

#include <memory>
#include <utility>
#include <vector>

namespace ApprovalTests {

    using NamerCreator = std::function<std::shared_ptr<ApprovalNamer>()>;

//! Implementation detail of Approvals::useAsDefaultNamer()
class DefaultNamerFactory
{
private:
    using NamerContainer = std::vector< NamerCreator >;
    static NamerContainer& defaultNamerContainer()
    {
        static NamerContainer namers = *createNamerContainer();
        return namers;
    }

    static NamerContainer* createNamerContainer()
    {
        auto container = new NamerContainer; 
        container->push_back( [](){return std::make_shared<ApprovalTestNamer>();} );
        return container;
    }

public:
    static NamerCreator getDefaultNamer()
    {
        return defaultNamerContainer().at(0);
    }
    
    static void setDefaultNamer( NamerCreator namer)
    {
        defaultNamerContainer().at(0) = std::move(namer);
    }

};
}

#endif //APPROVALTESTS_CPP_DEFAULTNAMERFACTORY_H
