#pragma once

#include "ApprovalTests/namers/DefaultNamerFactory.h"
#include "ApprovalTests/utilities/Macros.h"

namespace ApprovalTests
{
    //! Implementation detail of Approvals::useAsDefaultNamer()
    class APPROVAL_TESTS_NO_DISCARD DefaultNamerDisposer
    {
    private:
        NamerCreator previous_result;

    public:
        explicit DefaultNamerDisposer(NamerCreator namerCreator);
        DefaultNamerDisposer(const DefaultNamerDisposer&) = default;

        ~DefaultNamerDisposer();
    };
}
