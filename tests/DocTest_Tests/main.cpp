// begin-snippet: doctest_main
// main.cpp:
#define APPROVALS_DOCTEST // This tells Approval Tests to provide a main() - only do this in one cpp file
#include "ApprovalTests.hpp"
// end-snippet

using namespace ApprovalTests;

#include "core/Reporter.h"
#include "utilities/FileUtils.h"
#include "reporters/TextDiffReporter.h"

#include <iostream>

auto ciReporterDisposer = CIBuildOnlyReporterUtils::useAsFrontLoadedReporter(
    std::make_shared<TextDiffReporter>());

auto directory = Approvals::useApprovalsSubdirectory("approval_tests");
