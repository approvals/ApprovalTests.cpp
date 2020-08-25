#include "ApprovalTests/reporters/ReporterFactory.h"
#include "ApprovalTests/reporters/ClipboardReporter.h"

#include "doctest/doctest.h"

using namespace ApprovalTests;

TEST_CASE("ReporterFactory creates a Reporter given a string")
{
    ReporterFactory factory;
    std::unique_ptr<Reporter> reporter = factory.createReporter("ClipboardReporter");
    CHECK(reporter);
    CHECK(dynamic_cast<ClipboardReporter*>(reporter.get()));
}
