#define APPROVALS_CATCH
#include "ApprovalTests.hpp"

using namespace ApprovalTests;

// This puts "received" and "approved" files in approval_tests/ sub-directory,
// keeping the test source directory tidy:
auto directoryDisposer = Approvals::useApprovalsSubdirectory("approval_tests");
