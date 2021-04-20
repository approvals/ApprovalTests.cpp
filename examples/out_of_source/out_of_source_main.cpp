#define APPROVALS_DOCTEST
#include "ApprovalTests.hpp"

#include "DocTestReporter.h"

using namespace ApprovalTests;

//auto defaultReporterDisposer =
//    Approvals::useAsDefaultReporter(std::make_shared<TextDiffReporter>());

//auto defaultReporterDisposer =
//    Approvals::useAsDefaultReporter(std::make_shared<DocTestReporter>());

auto default_namer_disposer = Approvals::useAsDefaultNamer(
    []()
    {
        return std::make_shared<TemplatedCustomNamer>(
            "{TestSourceDirectory}/"
            "{TestFileName}.{TestCaseName}.{ApprovedOrReceived}.{FileExtension}");
    });
