#include "Catch.hpp"
#include "ApprovalTests/reporters/CIBuildOnlyReporter.h"
#include "ApprovalTests/reporters/QuietReporter.h"

using namespace ApprovalTests;

TEST_CASE("SampleCIReporter")
{
    // begin-snippet: report_quietly_on_ci
    // main.cpp
    auto ciReporterDisposer = CIBuildOnlyReporter::useAsFrontLoadedReporter(
        std::make_shared<QuietReporter>());
    // end-snippet
}
