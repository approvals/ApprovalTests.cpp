#include "doctest/doctest.h"
#include "ApprovalTests/utilities/Path.h"

using namespace ApprovalTests;

TEST_CASE("Should append to paths")
{
    Path path(".");
    CHECK("." == path.toString("/"));

    path = path / "file.txt";
    CHECK("./file.txt" == path.toString("/"));
    CHECK(".\\file.txt" == path.toString("\\"));

    path = path + ".v1";
    CHECK("./file.txt.v1" == path.toString("/"));
}

TEST_CASE("Can append two Paths")
{
    Path path1("hello");
    Path path2("world");
    CHECK("hello/world" == (path1 / path2).toString("/"));
}

TEST_CASE("Should handle multiple separators")
{
    auto location = "tmp" + SystemUtils::getDirectorySeparator();
    Path path = Path(location);
    path = path / (SystemUtils::getDirectorySeparator() + "subdirectory");
    CHECK("tmp/subdirectory" == path.toString("/"));
    CHECK("tmp\\subdirectory" == path.toString("\\"));
}

TEST_CASE("Path normalises separators in stored string")
{
    Path path = Path("C:\\temp\\/a/b/c");
    CHECK("C:/temp/a/b/c" == path.toString("/"));

    Path path2 = Path("C:\\temp\\") / Path("/a/b/c");
    CHECK("C:/temp/a/b/c" == path2.toString("/"));
}

TEST_CASE("Path condenses slashes")
{
    Path path = Path("a///b.txt");
    CHECK("a/b.txt" == path.toString("/"));
}
