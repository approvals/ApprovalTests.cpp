#include "Catch.hpp"
#include "ApprovalTests/reporters/CIBuildOnlyReporterUtils.h"
#include "ApprovalTests/reporters/QuietReporter.h"

using namespace ApprovalTests;

TEST_CASE("SampleCIReporter")
{
    // begin-snippet: report_quietly_on_ci
    // main.cpp
    auto ciReporterDisposer = CIBuildOnlyReporterUtils::useAsFrontLoadedReporter(
        std::make_shared<QuietReporter>());
    // end-snippet
}
