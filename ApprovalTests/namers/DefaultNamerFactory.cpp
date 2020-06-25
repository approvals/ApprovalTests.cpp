#include "ApprovalTests/namers/DefaultNamerFactory.h"
#include "ApprovalTestNamer.h"

namespace ApprovalTests
{
    NamerCreator& DefaultNamerFactory::defaultNamer()
    {
        static NamerCreator namer = []() {
            return std::make_shared<ApprovalTestNamer>();
        };
        return namer;
    }

    NamerCreator DefaultNamerFactory::getDefaultNamer()
    {
        return defaultNamer();
    }

    void DefaultNamerFactory::setDefaultNamer(NamerCreator namer)
    {
        defaultNamer() = std::move(namer);
    }
}
