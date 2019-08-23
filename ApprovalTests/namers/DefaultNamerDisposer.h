#ifndef APPROVALTESTS_CPP_DEFAULTNAMERDISPOSER_H
#define APPROVALTESTS_CPP_DEFAULTNAMERDISPOSER_H

#include "DefaultNamerFactory.h"
#include "../Macros.h"

//! Implementation detail of Approvals::useAsDefaultNamer()
class APPROVAL_TESTS_NO_DISCARD DefaultNamerDisposer
{
private:
    NamerCreator previous_result;
public:
    explicit DefaultNamerDisposer(NamerCreator namerCreator)
    {
        previous_result = DefaultNamerFactory::getDefaultNamer();
        DefaultNamerFactory::setDefaultNamer(namerCreator);
    }

    ~DefaultNamerDisposer()
    {
        DefaultNamerFactory::setDefaultNamer(previous_result);
    }
};

#endif //APPROVALTESTS_CPP_DEFAULTNAMERDISPOSER_H
