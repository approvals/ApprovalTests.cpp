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
          "/my/source/directory/approved/"
          "TemplatedCustomNamerTests.Test_StringTemplates.txt");
    CHECK(namer.getReceivedFile(".txt") ==
          "/my/source/directory/received/"
          "TemplatedCustomNamerTests.Test_StringTemplates.txt");
}

TEST_CASE("Test Namer Injection")
{
    // begin-snippet: templated_custom_namer_injection_via_options
    Approvals::verify(
        "Hello",
        Options().withNamer(TemplatedCustomNamer::create(
            "{TestSourceDirectory}/CustomName.{ApprovedOrReceived}.{FileExtension}")));
    // end-snippet

    // begin-snippet: templated_custom_namer_injection
    auto default_namer_disposer = TemplatedCustomNamer::useAsDefaultNamer(
        "{TestSourceDirectory}/CustomName.{ApprovedOrReceived}.{FileExtension}");
    // end-snippet

    Approvals::verify("Hello");
}

// ---- Docs
// TODO Revisit our documentation
// TODO Document ApprovalTestNamer::setCheckBuildConfig(false)
// TODO Document the details and limitations of each template string
// TODO Document Options().withNamer()

// TODO Document scenarios where this might be useful (when run outside of build dir, e.g. embedded)
// TODO Make documentation example use different filenames for approved and received, for safety

// TODO Reporters.md should link to the new How To file
// TODO New "How To" file should link to Reporters.md
// TODO Add CreateCustomNamer page to doc/README.md
// TODO Add CreateCustomNamer page to doc/sphinx/index.rst
