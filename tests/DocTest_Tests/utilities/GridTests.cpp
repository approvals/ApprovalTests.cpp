#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/utilities/Grid.h"

TEST_CASE("Print Grid")
{
    auto grid = ApprovalTests::Grid::print(
        6, 8, [](int x, int y, auto& os) { os << ((x % 2 == y % 2) ? "O" : "X"); });
    ApprovalTests::Approvals::verify(grid);
}
TEST_CASE("Print Simple")
{
    // begin-snippet: grid_simple
    auto grid = ApprovalTests::Grid::print(4, 2, ".");
    // end-snippet
    ApprovalTests::Approvals::verify(grid);
}

TEST_CASE("Print Coordinates")
{
    // begin-snippet: grid_lambda
    auto grid = ApprovalTests::Grid::print(
        4, 3, [](int x, int y, auto& os) { os << "(" << x << "," << y << ") "; });
    // end-snippet
    ApprovalTests::Approvals::verify(grid);
}
