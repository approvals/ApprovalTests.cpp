// begin-snippet: doctest_existing_main
// Add these two lines to the top of your main.cpp file:
#define APPROVALS_DOCTEST_EXISTING_MAIN
#include "ApprovalTests.hpp"
// end-snippet

#include "ApprovalTests/Approvals.h"

int main(int argc, char** argv)
{
    auto directoryDisposer =
        ApprovalTests::Approvals::useApprovalsSubdirectory("approval_tests");
    return doctest::Context(argc, argv).run();
}
