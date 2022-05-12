#include "Parser.h"

#include <algorithm>
#include <regex>
#include <sstream>

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

    if (IsTransitionValid(m_currentState, pendingState))
    {
      m_currentState = pendingState;
      m_isLastInputValid = true;
    }
    else
    {
      m_response = INVALID_RESPONSE;
      m_isLastInputValid = false;
      return;
    }
  }

  // Final check
  if (IsTransitionValid(m_currentState, EGrammarState::End))
  {
    m_currentState = EGrammarState::End;
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
