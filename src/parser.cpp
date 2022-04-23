#include "parser.h"

void Parser::parse(std::string input)
{
  if (input == "exit")
  {
    m_shouldQuit = true;
    m_response = "Exiting...";
  }
  else if (input.empty())
  {
    m_response = "Sorry?";
  }
  else if (std::find(verbs.begin(), verbs.end(), input) != verbs.end())
  {
    m_isLastInputValid = true;
    m_lastInputVerb = input;
  }
  else
  {
    m_response = "You said: " + input;
  }
}

bool Parser::isLastInputValid()
{
  return m_isLastInputValid;
}

std::string Parser::getLastInputVerb()
{
  return m_lastInputVerb;
}