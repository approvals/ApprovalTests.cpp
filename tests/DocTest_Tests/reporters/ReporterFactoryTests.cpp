#include "ApprovalTests/reporters/ReporterFactory.h"
#include "ApprovalTests/reporters/ClipboardReporter.h"
#include "ApprovalTests/reporters/LinuxReporters.h"
#include "ApprovalTests/reporters/WindowsReporters.h"

#include "doctest/doctest.h"

using namespace ApprovalTests;

TEST_CASE("ReporterFactory creates a Reporter given a string")
{
    ReporterFactory factory;
    std::unique_ptr<Reporter> reporter = factory.createReporter("ClipboardReporter");
    CHECK(reporter);
    CHECK(dynamic_cast<ClipboardReporter*>(reporter.get()));
}

TEST_CASE("ReporterFactory returns null if reporter is unknown")
{
    ReporterFactory factory;
    std::unique_ptr<Reporter> reporter = factory.createReporter("IDoNotExist");
    CHECK(!reporter);
}

TEST_CASE("ReporterFactory creates a Reporter given Linux::MeldReporter")
{
    ReporterFactory factory;
    std::unique_ptr<Reporter> reporter = factory.createReporter("Linux::MeldReporter");
    CHECK(reporter);
    CHECK(dynamic_cast<Linux::MeldReporter*>(reporter.get()));
}

TEST_CASE("ReporterFactory creates a Reporter given Windows::WinMergeReporter")
{
    ReporterFactory factory;
    std::unique_ptr<Reporter> reporter =
        factory.createReporter("Windows::WinMergeReporter");
    CHECK(reporter);
    CHECK(dynamic_cast<Windows::WinMergeReporter*>(reporter.get()));
}
