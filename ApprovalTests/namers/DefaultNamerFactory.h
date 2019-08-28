#ifndef APPROVALTESTS_CPP_DEFAULTNAMERFACTORY_H
#define APPROVALTESTS_CPP_DEFAULTNAMERFACTORY_H

#include "ApprovalNamer.h"
#include "ApprovalTestNamer.h"
#include "ApprovalTests/utilities/Macros.h"

#include <memory>
#include <vector>

namespace ApprovalTests {

typedef std::function<std::shared_ptr<ApprovalNamer>()> NamerCreator;

//! Implementation detail of Approvals::useAsDefaultNamer()
class DefaultNamerFactory
{
private:
    using NamerContainer = std::vector< NamerCreator >;
    APPROVAL_TESTS_MACROS_STATIC(NamerContainer, defaultNamerContainer, DefaultNamerFactory::createNamerContainer())
    
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
        defaultNamerContainer().at(0) = namer;
    }

};
}

#endif //APPROVALTESTS_CPP_DEFAULTNAMERFACTORY_H
