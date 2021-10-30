#include <string>

class Parser
{
  public:
    void parse(std::string input);

    bool quitRequested() { return shouldQuit; }
    std::string getResponse() { return response; }

  private:
    std::string response;
    bool shouldQuit{ false };
};