#include "Catch.hpp"
#include "ApprovalTests/reporters/CIBuildOnlyReporter.h"
#include "ApprovalTests/reporters/QuietReporter.h"

using namespace ApprovalTests;

TEST_CASE("SampleCIReporter")
{
    auto ciReporterDisposer = CIBuildOnlyReporter::useAsFrontLoadedReporter( std::make_shared<QuietReporter>() );
}
