#include "Parser.h"

#include <algorithm>
#include <regex>
#include <sstream>

Parser::Parser()
{
  m_currentStates.push_back(std::make_unique<Start>());
}

void Parser::Reset()
{
  m_currentStates.clear();
  m_currentStates.push_back(std::make_unique<Start>());
}

void Parser::parse(std::string input)
{
  // reset
  m_response = INVALID_RESPONSE;
  m_isLastInputValid = false;

  // This intentionally takes a copy so we can manipulate the input to sanitise it.
  std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::tolower(c); });

  auto tokens = getTokens(input);

  for (const auto& token : tokens)
  {
    // Get the desired pending state:
    EGrammarState pendingState;
    if (isVerb(token))
    {
      pendingState = EGrammarState::Verb;
    }
    else if (isPreposition(token))
    {
      pendingState = EGrammarState::Preposition;
    }
    else if (isArticle(token))
    {
      pendingState = EGrammarState::Article;
    }
    else if (isObject(token))
    {
      pendingState = EGrammarState::Object;
    }
    else
    {
      // Invalid token
      m_response = INVALID_RESPONSE;
      m_isLastInputValid = false;
      return;
    }

    m_lastError = m_currentStates.back()->IsTransitionValid(pendingState);
    if (m_lastError == EErrorCode::Success)
    {
      m_currentStates.push_back(createState(pendingState, token));
      m_isLastInputValid = true;
    }
    else
    {
      // The verb is likely to give us the most information about the error, so ask there first.
      State* lastVerb = getLastStateOfType(EGrammarState::Verb);
      if (lastVerb)
      {
        m_response = lastVerb->GetResponse(m_lastError);
      }
      else
      {
        m_response = m_currentStates.back()->GetResponse(m_lastError);
      }

      m_isLastInputValid = false;
      return;
    }
  }

  // Final check
  m_lastError = m_currentStates.back()->IsTransitionValid(EGrammarState::End);
  if (m_lastError == EErrorCode::Success)
  {
    m_isLastInputValid = true;

    // Also do any final processing now we know the whole sentence is valid
    State* lastVerb = getLastStateOfType(EGrammarState::Verb);

    if (lastVerb)
    {
      m_response = lastVerb->GetResponse(EErrorCode::Success);
      if (lastVerb->GetToken() == "exit")
      {
        m_shouldQuit = true;
      }
    }
  }
  else
  {
      // The verb is likely to give us the most information about the error, so ask there first.
      State* lastVerb = getLastStateOfType(EGrammarState::Verb);
      if (lastVerb)
      {
        m_response = lastVerb->GetResponse(m_lastError);
      }
      else
      {
        m_response = m_currentStates.back()->GetResponse(m_lastError);
      }

      m_isLastInputValid = false;
      return;
  }
}

bool Parser::isVerb(const std::string& input) const
{
  return std::find(verbs.begin(), verbs.end(), input) != verbs.end();
}

bool Parser::isPreposition(const std::string& input) const
{
  return std::find(prepositions.begin(), prepositions.end(), input) != prepositions.end();
}

bool Parser::isArticle(const std::string& input) const
{
  return std::find(articles.begin(), articles.end(), input) != articles.end();
}

bool Parser::isObject(const std::string& input) const
{
  return !isVerb(input) && !isPreposition(input) && !isArticle(input) &&
         std::regex_match(input, std::regex("[a-zA-Z]*"));
}

void Parser::updateResponse(const std::string& input)
{
  if (input == "exit")
  {
    m_response = "Exiting...";
    m_shouldQuit = true;
  }
}

std::unique_ptr<State> Parser::createState(EGrammarState state, std::string token) const
{
  // std::move is needed here to avoid a copy on return cause the return
  // type differs from the actual object returned cause polymorphism

  switch (state)
  {
    case EGrammarState::Start:
      return std::move(std::make_unique<Start>());
    case EGrammarState::Verb:
      return std::move(std::make_unique<Verb>(token));
    case EGrammarState::Preposition:
      return std::move(std::make_unique<Preposition>(token));
    case EGrammarState::Article:
      return std::move(std::make_unique<Article>(token));
    case EGrammarState::Object:
      return std::move(std::make_unique<Object>(token));
    case EGrammarState::End:
    default:
      return std::move(std::make_unique<End>());
  }
}

std::vector<std::string> Parser::getTokens(const std::string& input) const
{
  // Assume space as the delimiter
  std::istringstream tokens(input);
  std::vector<std::string> result;
  std::string token;

  while(std::getline(tokens, token, ' '))
  {
    result.push_back(token);
  }

  return result;
}

std::string Parser::getLastTokenOfType(EGrammarState type) const
{
  const auto& result = std::find_if(m_currentStates.begin(), m_currentStates.end(),
    [type](auto&& state){ return state->GetType() == type; });

  return result != m_currentStates.end() ? (*result)->GetToken() : "";
}

State* Parser::getLastStateOfType(EGrammarState type) const
{
  const auto& result = std::find_if(m_currentStates.begin(), m_currentStates.end(),
    [type](auto&& state){ return state->GetType() == type; });

  return result != m_currentStates.end() ? (*result).get() : nullptr;
}