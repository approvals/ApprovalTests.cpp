#include "doctest/doctest.h"
#include "ApprovalTests/reporters/CIBuildOnlyReporterUtils.h"
#include "ApprovalTests/reporters/QuietReporter.h"

TEST_CASE("SampleCIReporter")
{
    // begin-snippet: report_quietly_on_ci
    // main.cpp
    auto ciReporterDisposer =
        ApprovalTests::CIBuildOnlyReporterUtils::useAsFrontLoadedReporter(
            std::make_shared<ApprovalTests::QuietReporter>());
    // end-snippet
}
