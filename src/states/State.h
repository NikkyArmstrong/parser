#pragma once

#include "ParseStates.h"

class State
{
public:
  virtual bool IsTransitionValid(EGrammarState nextState) = 0;
  virtual std::string GetResponse() const { return m_response; }

protected:
  std::string m_token;
  std::string m_response;
};

class Verb : public State
{
public:
  Verb(std::string token) { m_token = token; }

  virtual bool IsTransitionValid(EGrammarState nextState) override
  {
    if (m_token == "take" || m_token == "open")
    {
      return nextState == EGrammarState::Article || nextState == EGrammarState::Object;
    }
    else if (m_token == "look")
    {
      if (nextState == EGrammarState::Article)
      {
        m_response = "Try looking at something";
      }

      return nextState == EGrammarState::Preposition || nextState == EGrammarState::Object || nextState == EGrammarState::End;
    }
    else if (m_token == "exit")
    {
      return nextState == EGrammarState::End;
    }
    else
    {
      return true;
    }
  }

private:
  const EGrammarState m_type{EGrammarState::Verb};
};

class Preposition : public State
{
public:
  Preposition(std::string token) { m_token = token; }

  virtual bool IsTransitionValid(EGrammarState nextState) override
  {
    return nextState != EGrammarState::Verb && nextState != EGrammarState::End;
  }

private:
  const EGrammarState m_type{EGrammarState::Preposition};
};

class Article : public State
{
public:
  Article(std::string token) { m_token = token; }

  virtual bool IsTransitionValid(EGrammarState nextState) override
  {
    return nextState != EGrammarState::Verb && nextState != EGrammarState::Preposition && nextState != EGrammarState::End;
  }

private:
  const EGrammarState m_type{EGrammarState::Article};
};

class Object : public State
{
public:
  Object(std::string token) { m_token = token; }

  virtual bool IsTransitionValid(EGrammarState nextState) override
  {
    return nextState == EGrammarState::End;
  }

private:
  const EGrammarState m_type{EGrammarState::Object};
};

class Start : public State
{
public:
  Start() { m_token = ""; }

  virtual bool IsTransitionValid(EGrammarState nextState) override
  {
    return nextState == EGrammarState::Verb;
  }

private:
  const EGrammarState m_type{EGrammarState::Start};
};

class End : public State
{
public:
  End() { m_token = ""; }

  virtual bool IsTransitionValid(EGrammarState nextState) override
  {
    return false;
  }

private:
  const EGrammarState m_type{EGrammarState::End};
};
