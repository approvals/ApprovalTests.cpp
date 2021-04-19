#include "doctest/doctest.h"
#include "ApprovalTests/namers/TemplatedCustomNamer.h"

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

// TODO Move Path impl to .cpp
// TODO Try it on an embedded device - or ask someone else to!
// TODO Revisit our documentation
