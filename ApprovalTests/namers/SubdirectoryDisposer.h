#pragma once

#include "ApprovalTests/utilities/Macros.h"

#include <string>

namespace ApprovalTests
{
    //! Implementation detail of Approvals::useApprovalsSubdirectory()
    class APPROVAL_TESTS_NO_DISCARD SubdirectoryDisposer
    {
    private:
        std::string previous_result;

    public:
        explicit SubdirectoryDisposer(std::string subdirectory);
        SubdirectoryDisposer(const SubdirectoryDisposer&) = default;

        ~SubdirectoryDisposer();
    };
}
