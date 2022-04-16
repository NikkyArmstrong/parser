#include "parser.h"

void Parser::parse(std::string input)
{
  if (input == "exit")
  {
    shouldQuit = true;
    response = "Exiting...";
  }
  else if (input.empty())
  {
    response = "Sorry?";
  }
  else
  {
    response = "You said: " + input;
  }
}