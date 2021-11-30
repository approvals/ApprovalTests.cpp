#pragma once

#include "ApprovalTests/utilities/Macros.h"
#include "ApprovalTests/utilities/EmptyFileCreatorFactory.h"

namespace ApprovalTests
{
    class APPROVAL_TESTS_NO_DISCARD EmptyFileCreatorDisposer
    {
    private:
        EmptyFileCreator previous_result;

    public:
        explicit EmptyFileCreatorDisposer(EmptyFileCreator creator);
        EmptyFileCreatorDisposer(const EmptyFileCreatorDisposer&) = default;

        ~EmptyFileCreatorDisposer();
    };
}
