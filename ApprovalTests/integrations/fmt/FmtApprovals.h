#pragma once
#ifdef FMT_VERSION
#include "FmtToString.h"
#include "ApprovalTests/Approvals.h"
namespace ApprovalTests
{
    using FmtApprovals =
        ApprovalTests::TApprovals<ApprovalTests::ToStringCompileTimeOptions<FmtToString>>;
}
#endif