#include <string>
#include <vector>

class Parser
{
  public:
    void parse(std::string input);

    bool quitRequested() { return m_shouldQuit; }
    std::string getResponse() { return m_response; }

    bool isLastInputValid();
    std::string getLastInputVerb();

  private:
    std::vector<std::string> verbs{ "look", "take" };

    std::string m_response;
    std::string m_lastInputVerb;

    bool m_shouldQuit{ false };
    bool m_isLastInputValid{ false };
};