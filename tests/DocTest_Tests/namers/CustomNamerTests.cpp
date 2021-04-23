#include "doctest/doctest.h"
#include "ApprovalTests/namers/TemplatedCustomNamer.h"
#include "ApprovalTests/Approvals.h"

using namespace ApprovalTests;

TEST_CASE("Test StringTemplates")
{
    // begin-snippet: templated_custom_namer_example
    TemplatedCustomNamer namer("/my/source/directory/{ApprovedOrReceived}/"
                               "{TestFileName}.{TestCaseName}.{FileExtension}");
    // end-snippet

    CHECK(namer.getApprovedFile(".txt") ==
          "/my/source/directory/approved/CustomNamerTests.Test_StringTemplates.txt");
    CHECK(namer.getReceivedFile(".txt") ==
          "/my/source/directory/received/CustomNamerTests.Test_StringTemplates.txt");
}

TEST_CASE("Test Namer Injection")
{
    // clang-format off
    // begin-snippet: templated_custom_namer_injection
    auto default_namer_disposer = Approvals::useAsDefaultNamer(
        []()
        {
            return std::make_shared<TemplatedCustomNamer>(
                "{TestSourceDirectory}/CustomName.{ApprovedOrReceived}.{FileExtension}");
        });
    // end-snippet
    // clang-format on

    Approvals::verify("Hello");
}

// ---- Miscellaneous
// TODO Move Path impl to .cpp
// TODO Merge branch to master

// ---- Docs
// TODO Revisit our documentation
// TODO Document the details and limitations of each template string
// TODO Document scenarios where this might be useful (when run outside of build dir, e.g. embedded)
// TODO Reporters.md should link to the new How To file
// TODO New "How To" file should link to Reporters.md
// TODO Make documentation example use different filenames for approved and received, for safety
// TODO Add CreateCustomNamer page to doc/README.md
// TODO Add CreateCustomNamer page to doc/sphinx/index.rst

// ---- Tests
// TODO Rename this file to TemplatedCustomNamerTests.cpp

// ---- Features
// TODO Make it easier to register TemplatedCustomNamer as custom namer
// TODO Convert / or \ to native directory separators
// TODO {TestSourceDirectory} is misleading - it does not always match the source directory - it should call ApprovalTestNamer::getTestSourceDirectory()
// TODO Review the template strings, for any missing cases
// TODO How to access ApprovalTestNamer::getRelativePathOfSourceDirectoryFromSourceRootForApproved() via {}
