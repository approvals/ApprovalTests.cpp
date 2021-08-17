#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"

#include "GameOfLife.h"
#include "Storyboard.h"

#include <ostream>
#include <vector>

using namespace ApprovalTests;

TEST_CASE("Demo 15-step blinker")
{
    int width = 11;
    int height = 18;
    {
        int x = 3;
        int y = 4;
        std::vector<Point> alive = {
            Point(x + 1, y + 1),
            Point(x + 2, y + 1),
            Point(x + 3, y + 1),
            Point(x + 1, y + 2),
            //            Point(x + 2,y + 2),
            Point(x + 3, y + 2),
            Point(x + 1, y + 3),
            Point(x + 2, y + 3),
            Point(x + 3, y + 3),
            Point(x + 1, y + 4),
            Point(x + 2, y + 4),
            Point(x + 3, y + 4),
            Point(x + 1, y + 5),
            Point(x + 2, y + 5),
            Point(x + 3, y + 5),
            Point(x + 1, y + 6),
            Point(x + 2, y + 6),
            Point(x + 3, y + 6),
            Point(x + 1, y + 7),
            //            Point(x + 2,y + 7),
            Point(x + 3, y + 7),
            Point(x + 1, y + 8),
            Point(x + 2, y + 8),
            Point(x + 3, y + 8),
        };
        GameOfLife game(alive);

        Approvals::verify(Storyboard()
                              .addFrame(game.print(width, height))
                              .addFrames(15, [&](int /*frame*/) {
                                  game = game.advance();
                                  return game.print(width, height);
                              }));
    }

    {
        auto alive = R"(
. . . . . . . .
. . . . . . . .
. . . . . . . .
. . . . . . . .
. . . . . . . .
. . . . X X X .
. . . . X . X .
. . . . X X X .
. . . . X X X .
. . . . X X X .
. . . . X X X .
. . . . X . X .
. . . . X X X . )";

        GameOfLife game(alive);

        Approvals::verify(Storyboard()
                              .addFrame(game.print(width, height))
                              .addFrames(15, [&](int /*frame*/) {
                                  game = game.advance();
                                  return game.print(width, height);
                              }));
    }
}
