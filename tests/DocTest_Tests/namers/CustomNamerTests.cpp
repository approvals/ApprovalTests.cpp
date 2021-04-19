#include "doctest/doctest.h"
#include "ApprovalTests/core/ApprovalNamer.h"
#include "ApprovalTests/namers/SeparateApprovedAndReceivedDirectoriesNamer.h"
#include "ApprovalTests/namers/NamerFactory.h"
#include "ApprovalTests/namers/TemplatedCustomNamer.h"
#include "ApprovalTests/utilities/Path.h"
#include "ApprovalTests/utilities/SystemUtils.h"

#include <utility>

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

// TODO Better names for methods
// TODO Finish up all the rest of the seams
// TODO Get this to work with received file
// TODO Make CustomNamer with... non-mutating
// TODO Use Doxygen grouping to group related methods together for docs
// TODO Move CustomNamer to .h and .cpp
// TODO Move Path impl to .cpp
// TODO Review usability
// TODO Consider user scenarios
// TODO Try it on an embedded device - or ask someone else to!
// TODO Revisit our documentation
