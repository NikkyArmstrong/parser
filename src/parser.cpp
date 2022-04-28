#include "parser.h"

#include <algorithm>
#include <sstream>

void Parser::parse(std::string input)
{
  // This intentionally takes a copy so we can manipulate the input to sanitise it.
  std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::tolower(c); });

  auto tokens = getTokens(input);

  for (std::string token : tokens)
  {
    if (isVerb(token))
    {
      m_isLastInputValid = true;
      m_lastInputVerb = input;

      updateResponse(input);
    }
    // else if (isPreposition(token))
    // {
    //   m_isLastInputValid = true;
    //   m_lastInputPreposition = token;
    // }
    // else if (isArticle(token))
    // {
    //   m_isLastInputValid = true;
    //   m_lastInputArticle = token;
    // }
    // else if (isObject(token))
    // {
    //   m_isLastInputValid = true;
    //   m_lastInputObject = token;
    // }
    else
    {
      m_isLastInputValid = false;
      m_response = INVALID_RESPONSE;
      break;
    }
  }

  if (!m_isLastInputValid)
  {
    m_response = INVALID_RESPONSE;
  }
}

bool Parser::isVerb(const std::string& input) const
{
  return std::find(verbs.begin(), verbs.end(), input) != verbs.end();
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
