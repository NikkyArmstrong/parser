#include "parser.h"

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

  for (int i = 0; i < tokens.size(); ++i)
  {
    const std::string& token = tokens[i];

    if (verbIsValid(i) && isVerb(token))
    {
      m_isLastInputValid = true;
      m_lastInputVerb = token;

      updateResponse(m_lastInputVerb);
    }
    else if (prepIsValid(i) && isPreposition(token))
    {
      m_isLastInputValid = true;
      m_lastInputPreposition = token;
    }
    else if (articleIsValid(i) && isArticle(token))
    {
      m_isLastInputValid = true;
      m_lastInputArticle = token;
    }
    else if (objectIsValid(i) && isObject(token))
    {
      m_isLastInputValid = true;
      m_lastInputObject = token;
    }
    else
    {
      m_isLastInputValid = false;
      m_response = INVALID_RESPONSE;
      return;
    }
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
