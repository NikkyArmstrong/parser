#pragma once

enum class EGrammarState
{
  Start = 0,
  Verb,
  Preposition,
  Article,
  Object,
  End,
  None
};

enum class EErrorCode {
  Success = 0,
  MissingPreposition,
  MissingObject,
  InvalidTransition
};