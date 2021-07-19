#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"

#include "GameOfLife.h"
#include "Storyboard.h"

#include <ostream>
#include <vector>

using namespace ApprovalTests;

TEST_CASE("Adding Storyboard Frames")
{
    {
        GameOfLife game(5, 5, [](int x, int y)
                        { return 1 <= x && x <= 3 && y == 2; });

        Approvals::verify(StoryBoard()
                              .addFrame(game.print(5, 5))
                              .addFrames(5,
                                         [&](int /*frame*/)
                                         {
                                             game = game.advance();
                                             return game.print(5, 5);
                                         }));
    }

    {
        GameOfLife game(5, 5, [](int x, int y)
                        { return 1 <= x && x <= 3 && y == 2; });

        StoryBoard story;

        story.addFrame(game.print(5, 5));
        for (int i = 0; i < 5; ++i)
        {
            game = game.advance();
            story.addFrame(game.print(5, 5));
        }
        Approvals::verify(story);
    }
}

TEST_CASE("Storyboard customization mechanisms")
{
    GameOfLife game(5, 5, [](int x, int y) { return 1 <= x && x <= 3 && y == 2; });

    StoryBoard story;
    story.addDescription("Game of Life");
    story.addFrame(game.print(5, 5));

    game = game.advance();
    story.addFrame("Start game", game.print(5, 5));

    game = game.advance();
    story.addFrame(game.print(5, 5));

    story.addDescriptionWithData("setting alive", game.setAliveCell("*"));
    story.addDescriptionWithData("setting dead", game.setDeadCell("_"));
    game = game.advance();
    story.addFrame(game.print(5, 5));

    game = game.advance();
    story.addFrame(game.print(5, 5));

    game = game.advance();
    story.addFrame(game.print(5, 5));

    Approvals::verify(story);
}
