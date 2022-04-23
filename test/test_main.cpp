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

      THEN("the game gives a response, and exits")
      {
          REQUIRE(_parser.isLastInputValid());
          REQUIRE(_parser.getResponse() == "Exiting...");
          REQUIRE(_parser.quitRequested());
      }
    }
  }
}

SCENARIO("the parser can deal with empty input", "[parser]")
{
  GIVEN("The player is playing the game")
  {
    Parser _parser;

    WHEN("the player presses 'enter' without typing anything")
    {
      _parser.parse("");
      THEN("the game prompts the player to type something")
      {
        REQUIRE(!_parser.isLastInputValid());
        REQUIRE(_parser.getResponse() == "Sorry?");
      }
    }
  }
}

SCENARIO("the parser can identify verbs", "[parser]")
{
  GIVEN("we have a parser")
  {
    Parser _parser;
    WHEN("the parser is given a verb")
    {
      const std::string& v = GENERATE("exit", "look", "take");
      _parser.parse(v);
      THEN("the parser identifies that this is a validly constructed sentence")
      {
        REQUIRE(_parser.isLastInputValid());
      }
      AND_THEN("the parser identifies that this sentence contains the correct verb")
      {
        REQUIRE(_parser.getLastInputVerb() == v);
      }
    }
    AND_WHEN("the parser is given a valid verb ignoring case")
    {
      const std::string& v = GENERATE("Look", "TAKE", "lOoK");
      _parser.parse(v);
      THEN("the parser identifies that this is a validly constructed sentence")
      {
        REQUIRE(_parser.isLastInputValid());
      }
      AND_THEN("the parser identifies that this sentence contains the correct verb")
      {
        // case insensitive compare in this test
        REQUIRE(_stricmp(_parser.getLastInputVerb().c_str(), v.c_str()) == 0);
      }
    }
    AND_WHEN("the parser is given an input that isn't a verb")
    {
      _parser.parse("foo");
      THEN("the parser identifies that this is not a validly constructed sentence")
      {
        REQUIRE(!_parser.isLastInputValid());
        REQUIRE(_parser.getResponse() == "Sorry?");
      }
    }
  }
}