#define CATCH_CONFIG_MAIN
#include "../3rdparty/catch.hpp"
#include "../src/parser.h"

SCENARIO("the player can quit the game", "[parser]")
{
  GIVEN("The player is playing the game")
  {
    Parser _parser;
    WHEN("the player types the word 'exit'")
    {
      _parser.parse("exit");

      THEN("the game exits")
      {
          REQUIRE(_parser.shouldQuit);
      }
    }
  }
}

SCENARIO("the player is prompted for input", "[parser]")
{
  GIVEN("The player is playing the game")
  {
    Parser _parser;

    WHEN("the player presses 'enter' without typing anything")
    {
      _parser.parse("");
      THEN("the game prompts the user to type something")
      {
        REQUIRE(!_parser.shouldQuit);
        REQUIRE(_parser.response == "Sorry?");
      }
    }
  }
}