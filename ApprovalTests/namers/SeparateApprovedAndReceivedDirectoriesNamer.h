#pragma once

#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/namers/TemplatedCustomNamer.h"

namespace ApprovalTests
{
    class SeparateApprovedAndReceivedDirectoriesNamer : public TemplatedCustomNamer
    {
    public:
        SeparateApprovedAndReceivedDirectoriesNamer();

        virtual ~SeparateApprovedAndReceivedDirectoriesNamer() override = default;

        static DefaultNamerDisposer useAsDefaultNamer();
    };
}
