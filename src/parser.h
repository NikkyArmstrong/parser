#include <string>

class Parser
{
  public:
    void parse(std::string input);

    bool quitRequested() { return shouldQuit; }
    std::string getResponse() { return response; }

    bool isLastInputValid() { return true; }
    std::string getLastInputVerb() { return "look"; }

  private:
    std::string response;
    bool shouldQuit{ false };
};