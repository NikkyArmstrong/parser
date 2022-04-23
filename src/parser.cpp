#include "parser.h"

void Parser::parse(const std::string& input)
{
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
