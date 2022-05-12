#pragma once

enum class EGrammarState
{
  Start = 0,
  Verb,
  Preposition,
  Article,
  Object,
  End
};

static bool IsTransitionValid(EGrammarState currentState, EGrammarState nextState)
{
  switch (currentState)
  {
    case EGrammarState::Start:
      return nextState == EGrammarState::Verb;
    case EGrammarState::Verb:
      return true;
    case EGrammarState::Preposition:
      return nextState != EGrammarState::Verb && nextState != EGrammarState::End;
    case EGrammarState::Article:
      return nextState != EGrammarState::Verb && nextState != EGrammarState::Preposition && nextState != EGrammarState::End;
    case EGrammarState::Object:
      return nextState == EGrammarState::End;
    case EGrammarState::End:
      return false;
  }

  return false;
};