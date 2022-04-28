#pragma once

#include <iostream>
#include <string>
#include "src/parser.h"

bool leave = false;
std::string input;

int main(int argc, char* argv[])
{
  Parser p;

  auto res = p.getTokens("test look foo");
  std::cout << res.size() << std::endl;
  for (auto& r : res)
  {
    std::cout << r << std::endl;
  }

  // while (!p.quitRequested())
  // {
  //   std::cout << "$ ";
  //   std::getline(std::cin, input);

  //   p.parse(input);

  //   std::cout << p.getResponse() << std::endl;
  // }
}