// These are tests to ensure that we are maintaining the old
// version macros

#include "DeprecationDefines.h" // must come first

#include "doctest/doctest.h"
#include "ApprovalTests/ApprovalTestsVersion.h"

#include <iostream>

TEST_CASE("compilation check for deprecated version info")
{
    std::cout << APPROVALTESTS_VERSION << " " << APPROVALTESTS_VERSION_MAJOR << " "
              << APPROVALTESTS_VERSION_MINOR << " " << APPROVALTESTS_VERSION_PATCH << " "
              << APPROVALTESTS_VERSION_STR << '\n';
}
