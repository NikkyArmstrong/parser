#pragma once

#include <string>

#include "ParseStates.h"

class State
{
public:
  State(std::string token, EGrammarState type)
  : m_type(type)
  , m_token(token) {}

  virtual EErrorCode IsTransitionValid(EGrammarState nextState) = 0;

  virtual std::string GetResponse(EErrorCode error) const { return m_response; }
  std::string GetToken() const { return m_token; }

  EGrammarState GetType() const { return m_type; }

protected:
  const EGrammarState m_type;
  const std::string m_token;
  std::string m_response;
};

class Verb : public State
{
public:
  Verb(std::string token);

  virtual EErrorCode IsTransitionValid(EGrammarState nextState) override;
  virtual std::string GetResponse(EErrorCode error) const override;
};

class Preposition : public State
{
public:
  Preposition(std::string token);

  virtual EErrorCode IsTransitionValid(EGrammarState nextState) override;
};

class Article : public State
{
public:
  Article(std::string token);

  virtual EErrorCode IsTransitionValid(EGrammarState nextState) override;
};

class Object : public State
{
public:
  Object(std::string token);

  virtual EErrorCode IsTransitionValid(EGrammarState nextState) override;
};

class Start : public State
{
public:
  Start();

  virtual EErrorCode IsTransitionValid(EGrammarState nextState) override;
};

class End : public State
{
public:
  End();

  virtual EErrorCode IsTransitionValid(EGrammarState nextState) override;
};
