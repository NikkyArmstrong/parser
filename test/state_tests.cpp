#include "catch.hpp"

#include "State.h"

/** Verbs */
SCENARIO("Look has the correct state transitions", "[state][verb][look]")
{
  GIVEN("we are parsing a sentence with the 'look' verb")
  {
    Verb v("look");
    WHEN("we try to move to a preposition, e.g. look at")
    {
      EErrorCode result = v.IsTransitionValid(EGrammarState::Preposition);
      THEN("the verb returns success")
      {
        REQUIRE(result == EErrorCode::Success);
      }
    }
    AND_WHEN("we try to move to an article, e.g. look the")
    {
      EErrorCode result = v.IsTransitionValid(EGrammarState::Article);
      THEN("the verb returns 'missing preposition'")
      {
        REQUIRE(result == EErrorCode::MissingPreposition);
      }
    }
    AND_WHEN("we try to move to an object, e.g. look tree")
    {
      EErrorCode result = v.IsTransitionValid(EGrammarState::Object);
      THEN("the verb returns success")
      {
        REQUIRE(result == EErrorCode::Success);
      }
    }
    AND_WHEN("we try to move to the end without an object, e.g. look")
    {
      EErrorCode result = v.IsTransitionValid(EGrammarState::End);
      THEN("the verb returns success")
      {
        REQUIRE(result == EErrorCode::Success);
      }
    }
    AND_WHEN("we try to move to the start")
    {
      EErrorCode result = v.IsTransitionValid(EGrammarState::Start);
      THEN("the verb returns a generic 'invalid' code")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to a verb, e.g. look take")
    {
      EErrorCode result = v.IsTransitionValid(EGrammarState::Verb);
      THEN("the verb returns a generic 'invalid' code")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
  }
}

SCENARIO("Take has the correct state transitions", "[state][verb][take]")
{
  GIVEN("we are parsing a sentence with the 'take' verb")
  {
    Verb v("take");
    WHEN("we try to move to a preposition, e.g. take at")
    {
      EErrorCode result = v.IsTransitionValid(EGrammarState::Preposition);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to an article, e.g. take the")
    {
      EErrorCode result = v.IsTransitionValid(EGrammarState::Article);
      THEN("the verb returns success")
      {
        REQUIRE(result == EErrorCode::Success);
      }
    }
    AND_WHEN("we try to move to an object, e.g. take tree")
    {
      EErrorCode result = v.IsTransitionValid(EGrammarState::Object);
      THEN("the verb returns success")
      {
        REQUIRE(result == EErrorCode::Success);
      }
    }
    AND_WHEN("we try to move to the end without an object, e.g. take")
    {
      EErrorCode result = v.IsTransitionValid(EGrammarState::End);
      THEN("the verb returns the error 'missing object'")
      {
        REQUIRE(result == EErrorCode::MissingObject);
      }
    }
    AND_WHEN("we try to move to the start")
    {
      EErrorCode result = v.IsTransitionValid(EGrammarState::Start);
      THEN("the verb returns a generic 'invalid' code")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to a verb, e.g. take take")
    {
      EErrorCode result = v.IsTransitionValid(EGrammarState::Verb);
      THEN("the verb returns a generic 'invalid' code")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
  }
}

SCENARIO("Exit has the correct state transitions", "[state][verb][exit]")
{
  GIVEN("we are parsing a sentence with the 'exit' verb")
  {
    Verb v("exit");
    WHEN("we try to move to a preposition, e.g. exit at")
    {
      EErrorCode result = v.IsTransitionValid(EGrammarState::Preposition);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to an article, e.g. exit the")
    {
      EErrorCode result = v.IsTransitionValid(EGrammarState::Article);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to an object, e.g. exit tree")
    {
      EErrorCode result = v.IsTransitionValid(EGrammarState::Object);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to the end without an object, e.g. exit")
    {
      EErrorCode result = v.IsTransitionValid(EGrammarState::End);
      THEN("the verb returns success")
      {
        REQUIRE(result == EErrorCode::Success);
      }
    }
    AND_WHEN("we try to move to the start")
    {
      EErrorCode result = v.IsTransitionValid(EGrammarState::Start);
      THEN("the verb returns a generic 'invalid' code")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to a verb, e.g. exit take")
    {
      EErrorCode result = v.IsTransitionValid(EGrammarState::Verb);
      THEN("the verb returns a generic 'invalid' code")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
  }
}

/** Prepositions */
SCENARIO("At has the correct state transitions", "[state][preposition][at]")
{
  GIVEN("we are parsing 'at', assuming we have come from a valid verb")
  {
    Preposition p("at");
    WHEN("we try to move to a verb, e.g. at look")
    {
      EErrorCode result = p.IsTransitionValid(EGrammarState::Verb);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to a preposition, e.g. at at")
    {
      EErrorCode result = p.IsTransitionValid(EGrammarState::Preposition);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to an article, e.g. at the")
    {
      EErrorCode result = p.IsTransitionValid(EGrammarState::Article);
      THEN("the verb returns success")
      {
        REQUIRE(result == EErrorCode::Success);
      }
    }
    AND_WHEN("we try to move to an object, e.g. at tree")
    {
      EErrorCode result = p.IsTransitionValid(EGrammarState::Object);
      THEN("the verb returns success")
      {
        REQUIRE(result == EErrorCode::Success);
      }
    }
    AND_WHEN("we try to move to the start")
    {
      EErrorCode result = p.IsTransitionValid(EGrammarState::Start);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to the end")
    {
      EErrorCode result = p.IsTransitionValid(EGrammarState::End);
      THEN("the verb returns the error 'missing object'")
      {
        REQUIRE(result == EErrorCode::MissingObject);
      }
    }
  }
}

/** Articles */
SCENARIO("the has the correct state transitions", "[state][article][the]")
{
  GIVEN("we are parsing 'the', assuming we have come from a valid verb or preposition")
  {
    Article a("the");
    WHEN("we try to move to a verb, e.g. the look")
    {
      EErrorCode result = a.IsTransitionValid(EGrammarState::Verb);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to a preposition, e.g. the at")
    {
      EErrorCode result = a.IsTransitionValid(EGrammarState::Preposition);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to an article, e.g. the the")
    {
      EErrorCode result = a.IsTransitionValid(EGrammarState::Article);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to an object, e.g. the tree")
    {
      EErrorCode result = a.IsTransitionValid(EGrammarState::Object);
      THEN("the verb returns success")
      {
        REQUIRE(result == EErrorCode::Success);
      }
    }
    AND_WHEN("we try to move to the start")
    {
      EErrorCode result = a.IsTransitionValid(EGrammarState::Start);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to the end")
    {
      EErrorCode result = a.IsTransitionValid(EGrammarState::End);
      THEN("the verb returns the error 'missing object'")
      {
        REQUIRE(result == EErrorCode::MissingObject);
      }
    }
  }
}

/** Objects */
SCENARIO("Objects have the correct state transitions", "[state][object]")
{
  GIVEN("we are parsing an object, assuming we have come from a valid state")
  {
    Object o("tree");
    WHEN("we try to move to a verb")
    {
      EErrorCode result = o.IsTransitionValid(EGrammarState::Verb);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to a preposition")
    {
      EErrorCode result = o.IsTransitionValid(EGrammarState::Preposition);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to an article")
    {
      EErrorCode result = o.IsTransitionValid(EGrammarState::Article);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to an object")
    {
      EErrorCode result = o.IsTransitionValid(EGrammarState::Object);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to the start")
    {
      EErrorCode result = o.IsTransitionValid(EGrammarState::Start);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to the end")
    {
      EErrorCode result = o.IsTransitionValid(EGrammarState::End);
      THEN("the verb returns success")
      {
        REQUIRE(result == EErrorCode::Success);
      }
    }
  }
}

/** Start */
SCENARIO("We can only transition to a verb from the start", "[state][start]")
{
  GIVEN("we are parsing the beginning of some input")
  {
    Start s;
    WHEN("we try to move to a verb")
    {
      EErrorCode result = s.IsTransitionValid(EGrammarState::Verb);
      THEN("the verb returns success")
      {
        REQUIRE(result == EErrorCode::Success);
      }
    }
    AND_WHEN("we try to move to a preposition")
    {
      EErrorCode result = s.IsTransitionValid(EGrammarState::Preposition);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to an article")
    {
      EErrorCode result = s.IsTransitionValid(EGrammarState::Article);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to an object")
    {
      EErrorCode result = s.IsTransitionValid(EGrammarState::Object);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to the start")
    {
      EErrorCode result = s.IsTransitionValid(EGrammarState::Start);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to the end")
    {
      EErrorCode result = s.IsTransitionValid(EGrammarState::End);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
  }
}

/** End **/
SCENARIO("We can't transition anywhere from the end", "[state][end]")
{
  GIVEN("we are parsing the end of some input")
  {
    End e;
    WHEN("we try to move to a verb")
    {
      EErrorCode result = e.IsTransitionValid(EGrammarState::Verb);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to a preposition")
    {
      EErrorCode result = e.IsTransitionValid(EGrammarState::Preposition);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to an article")
    {
      EErrorCode result = e.IsTransitionValid(EGrammarState::Article);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to an object")
    {
      EErrorCode result = e.IsTransitionValid(EGrammarState::Object);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to the start")
    {
      EErrorCode result = e.IsTransitionValid(EGrammarState::Start);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
    AND_WHEN("we try to move to the end")
    {
      EErrorCode result = e.IsTransitionValid(EGrammarState::End);
      THEN("the verb returns an error")
      {
        REQUIRE(result == EErrorCode::InvalidTransition);
      }
    }
  }
}