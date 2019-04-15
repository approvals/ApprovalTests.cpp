// startcode googletest_existing_main
// main.cpp:

// 1. Add these two lines to your main:
#define APPROVALS_GOOGLETEST_EXISTING_MAIN
#include "ApprovalTests.hpp"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    
    // 2. Add this line to your main:
    initializeApprovalTestsForGoogleTests();

    return RUN_ALL_TESTS();
}
// endcode

// startcode do_not_report_on_ci
// main.cpp
auto frontLoadedReportDisposer = Approvals::useAsFrontLoadedReporter(
    BlockingReporter::onMachineNamed("MyCIMachineName") );
// endcode
