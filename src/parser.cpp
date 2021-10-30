#include "parser.h"

void Parser::parse(std::string input)
{
  if (input == "exit")
  {
    shouldQuit = true;
  }

  if (input.empty())
  {
    response = "Sorry?";
  }
}