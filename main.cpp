#pragma once

#include <iostream>
#include <string>
#include "ParserConfig.h"
#include "parser.h"

bool leave = false;
std::string input;

int main(int argc, char* argv[])
{
  while (!leave)
  {
    std::cout << "$ ";
    std::cin >> input;

    if (input == "exit")
    {
      leave = true;
    }

    std::cout << input << std::endl;
  }
}