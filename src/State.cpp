#include "State.h"

Verb::Verb(std::string token)
 : State(token, EGrammarState::Verb)
{
}

EErrorCode Verb::IsTransitionValid(EGrammarState nextState)
{
  if (m_token == "take" || m_token == "open")
  {
    switch (nextState)
    {
      case EGrammarState::Article:
      case EGrammarState::Object:
      {
        return EErrorCode::Success;
      }
      case EGrammarState::End:
      {
        return EErrorCode::MissingObject;
      }
      case EGrammarState::Preposition:
      case EGrammarState::Start:
      case EGrammarState::Verb:
      default:
      {
        return EErrorCode::InvalidTransition;
      }
    }
  }
  else if (m_token == "look")
  {
    switch (nextState)
    {
      case EGrammarState::Article:
      {
        return EErrorCode::MissingPreposition;
      }
      case EGrammarState::Preposition:
      case EGrammarState::Object:
      case EGrammarState::End:
      {
        return EErrorCode::Success;
      }
      case EGrammarState::Start:
      case EGrammarState::Verb:
      default:
      {
        return EErrorCode::InvalidTransition;
      }
    }
  }
  else if (m_token == "exit")
  {
    if (nextState == EGrammarState::End)
    {
      return EErrorCode::Success;
    }
    else
    {
      return EErrorCode::InvalidTransition;
    }
  }
  else
  {
    return EErrorCode::Success;
  }
}

std::string Verb::GetResponse(EErrorCode error) const
{
  switch (error)
  {
    case EErrorCode::MissingObject:
      return "Look at what?";
    case EErrorCode::MissingPreposition:
      return "Try looking at something";
    case EErrorCode::Success:
      if (m_token == "exit")
      {
        return "Exiting...";
      }
      else
      {
        return m_response;
      }
    case EErrorCode::InvalidTransition:
    default:
      return "Sorry?";
  }
}

Preposition::Preposition(std::string token)
 : State(token, EGrammarState::Preposition)
 {}

EErrorCode Preposition::IsTransitionValid(EGrammarState nextState)
{
  switch (nextState)
  {
    case EGrammarState::End:
      return EErrorCode::MissingObject;
    case EGrammarState::Article:
    case EGrammarState::Object:
      return EErrorCode::Success;
    case EGrammarState::Start:
    case EGrammarState::Verb:
    case EGrammarState::Preposition:
    default:
      return EErrorCode::InvalidTransition;
  }
}

Article::Article(std::string token)
 : State(token, EGrammarState::Article)
{}

EErrorCode Article::IsTransitionValid(EGrammarState nextState)
{
  if (nextState == EGrammarState::Object)
  {
    return EErrorCode::Success;
  }
  else if (nextState == EGrammarState::End)
  {
    return EErrorCode::MissingObject;
  }
  else
  {
    return EErrorCode::InvalidTransition;
  }
}

Object::Object(std::string token)
 : State(token, EGrammarState::Object)
{}

EErrorCode Object::IsTransitionValid(EGrammarState nextState)
{
  return nextState == EGrammarState::End ? EErrorCode::Success : EErrorCode::InvalidTransition;
}

Start::Start()
 : State("", EGrammarState::Start)
{}

EErrorCode Start::IsTransitionValid(EGrammarState nextState)
{
  return nextState == EGrammarState::Verb ? EErrorCode::Success : EErrorCode::InvalidTransition;
}

End::End()
 : State("", EGrammarState::End)
{}

EErrorCode End::IsTransitionValid(EGrammarState nextState)
{
  return EErrorCode::InvalidTransition;
}


