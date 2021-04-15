#include "doctest/doctest.h"
#include "ApprovalTests/utilities/Path.h"

using namespace ApprovalTests;

TEST_CASE("Should create paths")
{
    Path path(".");
    CHECK("." == path.toString("/"));
    path = path / "file.txt";
    CHECK("./file.txt" == path.toString("/"));
    CHECK(".\\file.txt" == path.toString("\\"));
}
