#define CATCH_CONFIG_MAIN
#include "../3rdparty/catch.hpp"
#include "../src/parser.h"

SCENARIO("the player can quit the game", "[parser]")
{
  GIVEN("The player is playing the game")
  {
    WHEN("the player types the word 'exit'")
    {
      bool shouldQuit = parse("exit");

      THEN("the game exits")
      {
          REQUIRE(shouldQuit);
      }
    }
  }
}