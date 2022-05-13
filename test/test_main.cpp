#define CATCH_CONFIG_MAIN
#include "../3rdparty/catch.hpp"

#include "../src/Parser.h"

SCENARIO("the player can quit the game", "[parser]")
{
  GIVEN("The player is playing the game")
  {
    Parser _parser;
    WHEN("the player types the word 'exit'")
    {
      _parser.parse("exit");

      THEN("the game gives a response")
      {
        REQUIRE(_parser.getResponse() == "Exiting...");
      }
      AND_THEN("the game exits")
      {
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
      const std::string& v = GENERATE("exit", "look");
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
      const std::string& v = GENERATE("Look", "lOoK", "EXIT");
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

SCENARIO("the parser can identify grammatical parts of a sentence", "[parser]")
{
  GIVEN("we have a parser")
  {
    Parser _parser;
    WHEN("the parser is given a sentence with a verb and an object")
    {
      _parser.parse("look donkey");
      THEN("the parser identifies that this is valid")
      {
        REQUIRE(_parser.isLastInputValid());
      }
      AND_THEN("the parser can give us the grammar from the sentence")
      {
        REQUIRE(_parser.getLastInputVerb() == "look");
        REQUIRE(_parser.getLastInputObject() == "donkey");
      }
    }
    AND_WHEN("the parser is given a sentence with a verb, a preposition, and an object")
    {
      _parser.parse("look at tree");
      THEN("the parser identifies that this is valid")
      {
        REQUIRE(_parser.isLastInputValid());
      }
      AND_THEN("the parser can give us the grammar from the sentence")
      {
        REQUIRE(_parser.getLastInputVerb() == "look");
        REQUIRE(_parser.getLastInputPreposition() == "at");
        REQUIRE(_parser.getLastInputObject() == "tree");
      }
    }
    AND_WHEN("the parser is given a sentence with a verb, preposition, definite article, and object")
    {
      _parser.parse("look at the dog");
      THEN("the parser identifies that this is valid")
      {
        REQUIRE(_parser.isLastInputValid());
      }
      AND_THEN("the parser can give us the grammar from the sentence")
      {
        REQUIRE(_parser.getLastInputVerb() == "look");
        REQUIRE(_parser.getLastInputPreposition() == "at");
        REQUIRE(_parser.getLastInputArticle() == "the");
        REQUIRE(_parser.getLastInputObject() == "dog");
      }
    }
    AND_WHEN("the parser is given a sentence with a verb, definite article, and object")
    {
      _parser.parse("take the vase");
      THEN("the parser identifies that this is valid")
      {
        REQUIRE(_parser.isLastInputValid());
      }
      AND_THEN("the parser can give us the grammar from the sentence")
      {
        REQUIRE(_parser.getLastInputVerb() == "take");
        REQUIRE(_parser.getLastInputArticle() == "the");
        REQUIRE(_parser.getLastInputObject() == "vase");
      }
    }
  }
}

SCENARIO("the parser can identify sentences with invalid grammar construction", "[parser]")
{
  GIVEN("we have a parser")
  {
    Parser _parser;
    WHEN("the parser is given an invalidly constructed sentence")
    {
      const std::string& s = GENERATE("at donkey look", "the donkey", "donkey at");
      _parser.parse(s);
      THEN("the parser identifies that this is invalid")
      {
        REQUIRE(!_parser.isLastInputValid());
        REQUIRE(_parser.getResponse() == "Sorry?");
      }
    }
    WHEN("the parser is given an incomplete sentence")
    {
      _parser.parse("look at");
      THEN("the parser identifies that this is invalid")
      {
        REQUIRE(!_parser.isLastInputValid());
      }
      AND_THEN("the parser gives a meaningful response")
      {
        REQUIRE(_parser.getResponse() == "look at what?");
      }
    }
    WHEN("the parser is given a sentence with invalid characters")
    {
      const std::string& s = GENERATE("take the t3st", "look at the $%_RT");
      _parser.parse(s);
      THEN("the parser identifies that this is invalid")
      {
        REQUIRE(!_parser.isLastInputValid());
        REQUIRE(_parser.getResponse() == "Sorry?");
      }
    }
  }
}

SCENARIO("the parser can identify sentences that are validly constructed, but invalid English")
{
  GIVEN("we have a parser")
  {
    Parser _parser;
    WHEN("the parser is given a sentence that is valid grammatically but not valid English")
    {
      _parser.parse("take at the vase");
      THEN("the parser identifies that this is invalid")
      {
        REQUIRE(!_parser.isLastInputValid());
        REQUIRE(_parser.getResponse() == "Sorry?");
      }
    }
    AND_WHEN("the parser is given a sentence missing a bit")
    {
      _parser.parse("look the box");
      {
        REQUIRE(!_parser.isLastInputValid());
        REQUIRE(_parser.getResponse() == "Try looking at something");
      }
    }
  }
}

SCENARIO("the parser can detect which verbs are ok alone")
{
  GIVEN("we have a parser and a list of verbs")
  {
    Parser _parser;
    WHEN("we input invalid lone verbs to the parser")
    {
      const std::string& s = GENERATE("take", "open");
      _parser.parse(s);
      THEN("the parser can identify that these are invalid on their own")
      {
        REQUIRE(!_parser.isLastInputValid());
      }
    }
    AND_WHEN("we input valid lone words to the parser")
    {
      const std::string& s = GENERATE("look", "exit");
      _parser.parse(s);
      THEN("the parser can identify that these are valid on their own")
      {
        REQUIRE(_parser.isLastInputValid());
      }
    }
    AND_WHEN("we input a verb that must be alone")
    {
      _parser.parse("exit at the door");
      THEN("the parser can identify that this is invalid")
      {
        REQUIRE(!_parser.isLastInputValid());
      }
    }
  }
}