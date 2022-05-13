#include "Parser.h"

#include <algorithm>
#include <regex>
#include <sstream>

Parser::Parser()
  : m_currentState(std::make_unique<Start>())
{
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
      m_lastInputVerb = token;
    }
    else if (isPreposition(token))
    {
      pendingState = EGrammarState::Preposition;
      m_lastInputPreposition = token;
    }
    else if (isArticle(token))
    {
      pendingState = EGrammarState::Article;
      m_lastInputArticle = token;
    }
    else if (isObject(token))
    {
      pendingState = EGrammarState::Object;
      m_lastInputObject = token;
    }
    else
    {
      // Invalid token
      m_response = INVALID_RESPONSE;
      m_isLastInputValid = false;
      return;
    }

    if (m_currentState->IsTransitionValid(pendingState))
    {
      m_currentState = createState(pendingState, token);
      m_isLastInputValid = true;
    }
    else
    {
      m_response = m_currentState->GetResponse() == "" ? INVALID_RESPONSE : m_currentState->GetResponse();
      m_isLastInputValid = false;
      return;
    }
  }

  // Final check
  if (m_currentState->IsTransitionValid(EGrammarState::End))
  {
    m_currentState = std::make_unique<End>();
    m_isLastInputValid = true;

    // Also do any final processing now we know the whole sentence is valid
    updateResponse(m_lastInputVerb);
  }
  else
  {
    m_response = INVALID_RESPONSE;
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
