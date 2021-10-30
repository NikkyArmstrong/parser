#include "parser.h"

bool Parser::parse(std::string input)
{
  if (input == "exit")
  {
    return true;
  }

  if (input.empty())
  {
    response = "Sorry?";
  }

  return false;
}