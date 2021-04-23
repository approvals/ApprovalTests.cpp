#pragma once

#include "ApprovalTestNamer.h"
#include "../Approvals.h"
#include "TemplatedCustomNamer.h"

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
