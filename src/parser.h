#include <string>

class Parser
{
  public:
    std::string response;
    bool shouldQuit{ false };

    void parse(std::string input);
};