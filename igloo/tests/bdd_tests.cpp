
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
using namespace igloo;

namespace igloo_example {
 
  struct Position
  {
  };
  
  inline bool operator==(const Position&, const Position&)
  {
    return true;
  }
  
  
  struct Player
  {
  };
  
  inline bool operator==(const Player&, const Player&)
  {
    return true;
  }
  
  Player PlayerOne;  
  struct Game
  {
    typedef std::vector<Position> PositionCollection;
    
    const PositionCollection& Positions() const
    {
      return positions_;
    }
    
    void Select(const Player&)
    {
    }
    
    const Player& NextPlayer()
    {
      return PlayerOne;
    }
    
    PositionCollection positions_;
  };
  
  Position EmptyPosition;

  
Context(ANewlyStartedGame)
{
  Spec(ShouldHaveAnEmptyBoard)
  {
    Assert::That(game.Positions(), Has().All().EqualTo(EmptyPosition));
  }
  
  Context(PlayerOneIsSelectedToStart)
  {
    void SetUp()
    {
      Parent().game.Select(PlayerOne);
    }
    
    Spec(ItShouldBePlayerOnesTurn)
    {
      Assert::That(Parent().game.NextPlayer(), Equals(PlayerOne));
    }
  };  
  
  Game game;
};
}
