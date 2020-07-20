#include "ApprovalTests/namers/DefaultNamerDisposer.h"

namespace ApprovalTests
{
    DefaultNamerDisposer::DefaultNamerDisposer(NamerCreator namerCreator)
    {
        previous_result = DefaultNamerFactory::getDefaultNamer();
        DefaultNamerFactory::setDefaultNamer(std::move(namerCreator));
    }

    DefaultNamerDisposer::~DefaultNamerDisposer()
    {
        DefaultNamerFactory::setDefaultNamer(previous_result);
    }
}
