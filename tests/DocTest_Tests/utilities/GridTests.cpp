#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/utilities/Grid.h"

using namespace ApprovalTests;

TEST_CASE("Print Grid")
{
    auto grid = Grid::print(
        6, 8, [](int x, int y, auto& os) { os << ((x % 2 == y % 2) ? "O" : "X"); });
    Approvals::verify(grid);
}
TEST_CASE("Print Simple")
{
    // begin-snippet: grid_simple
    auto grid = Grid::print(4, 2, ".");
    // end-snippet
    Approvals::verify(grid);
}

TEST_CASE("Print Coordinates")
{
    // begin-snippet: grid_lambda
    auto grid = Grid::print(
        4, 3, [](int x, int y, auto& os) { os << "(" << x << "," << y << ") "; });
    // end-snippet
    Approvals::verify(grid);
}
