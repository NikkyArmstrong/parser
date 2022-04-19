#define CATCH_CONFIG_MAIN
#include "../3rdparty/catch.hpp"

#include "../src/parser.h"
#include "../src/Room.h"

SCENARIO("the player can quit the game", "[parser]")
{
  GIVEN("The player is playing the game")
  {
    Parser _parser;
    WHEN("the player types the word 'exit'")
    {
      _parser.parse("exit");

      THEN("the game gives a response, and exits")
      {
          REQUIRE(_parser.getResponse() == "Exiting...");
          REQUIRE(_parser.quitRequested());
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
      THEN("the game prompts the player to type something")
      {
        REQUIRE(!_parser.quitRequested());
        REQUIRE(_parser.getResponse() == "Sorry?");
      }
    }
    WHEN("the player types a phrase")
    {
      std::string phraseInput = "any phrase";
      _parser.parse(phraseInput);
      THEN("the game prints that phrase back to the player")
      {
        REQUIRE(!_parser.quitRequested());
        REQUIRE(_parser.getResponse() == "You said: " + phraseInput);
      }
    }
  }
}

SCENARIO("the player can look", "[parser]")
{
  Parser _parser;
  GIVEN("the game has a room")
  {
    Room _room("a nice room");
    WHEN("the player inputs look")
    {
      _parser.parse("look");
      THEN("the game gives a description of the room")
      {
        REQUIRE(_parser.getResponse() == _room.getDescription());
      }
    }
  }
}