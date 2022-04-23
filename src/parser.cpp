#include "parser.h"

#include <algorithm>

void Parser::parse(std::string input)
{
  // This intentionally takes a copy so we can manipulate the input to sanitise it.
  std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::tolower(c); });

  if (isVerb(input))
  {
    m_isLastInputValid = true;
    m_lastInputVerb = input;

    updateResponse(input);
  }
  else
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
