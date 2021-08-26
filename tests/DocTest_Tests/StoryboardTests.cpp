#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"

#include "GameOfLife.h"
#include "Storyboard.h"
#include <vector>

TEST_CASE("Adding Storyboard Frames")
{
    using namespace ApprovalTests;

    {
        GameOfLife game(5, 5, [](int x, int y) { return 1 <= x && x <= 3 && y == 2; });

        Approvals::verify(
            Storyboard().addFrame(game.print(5, 5)).addFrames(5, [&](int /*frame*/) {
                game = game.advance();
                return game.print(5, 5);
            }));
    }

    {
        GameOfLife game(5, 5, [](int x, int y) { return 1 <= x && x <= 3 && y == 2; });

        Storyboard story;

        story.addFrame(game.print(5, 5));
        for (int i = 0; i < 5; ++i)
        {
            game = game.advance();
            story.addFrame(game.print(5, 5));
        }
        Approvals::verify(story);
    }
}

static GameOfLife createBlinker()
{
    GameOfLife game(5, 5, [](int x, int y) { return 1 <= x && x <= 3 && y == 2; });
    return game;
}

TEST_CASE("Storyboard friendly examples")
{
    ApprovalTests::Storyboard story;
    GameOfLife game = createBlinker();

    // begin-snippet: storyboard_friendly_report
    story.addDescriptionWithData("setting alive", game.setAliveCell("*"));
    // end-snippet

    // begin-snippet: storyboard_unfriendly_report
    std::string newValue = "*";
    game.setAliveCell(newValue);
    story.addDescriptionWithData("setting alive", newValue);
    // end-snippet
}

TEST_CASE("Storyboard customization mechanisms")
{
    // begin-snippet: storyboard_complete_example
    // Create a Storyboard to track a series of changes
    ApprovalTests::Storyboard story;

    // Create object to track
    GameOfLife game = createBlinker();

    // Add a title
    story.addDescription("Game of Life");

    // Capture the starting state
    story.addFrame(game.toString());

    // Frame1: with title
    game = game.advance();
    story.addFrame("Start game", game.toString());

    // Frame2: default titling
    game = game.advance();
    story.addFrame(game.toString());

    // Change how it renders and note it in the Storyboard
    story.addDescriptionWithData("setting alive", game.setAliveCell("*"));
    story.addDescriptionWithData("setting dead", game.setDeadCell("_"));

    // 3 more frames
    for (int i = 0; i < 3; ++i)
    {
        game = game.advance();
        story.addFrame(game.toString());
    }

    // verify storyboard
    ApprovalTests::Approvals::verify(story);
    // end-snippet
}
