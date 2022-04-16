#pragma once

#include <iostream>
#include <string>
#include "src/parser.h"

bool leave = false;
std::string input;

int main(int argc, char* argv[])
{
  Parser p;

  while (!p.quitRequested())
  {
    std::cout << "$ ";
    std::getline(std::cin, input);

    p.parse(input);

    std::cout << p.getResponse() << std::endl;
  }
}