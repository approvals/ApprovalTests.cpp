#include <fmt/ranges.h>   // Needs to be included first, for Unity builds
#include "FmtAsDefault.h" // Needs to be before "ApprovalTests.hpp" for Unity builds

#define APPROVALS_DOCTEST
#include "ApprovalTests.hpp"

#include "ApprovalTests/Approvals.h"

auto directoryDisposer =
    ApprovalTests::Approvals::useApprovalsSubdirectory("approval_tests");
