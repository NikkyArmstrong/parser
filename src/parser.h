#include <string>
#include <vector>

class Parser
{
  public:
    void parse(const std::string& input);

    bool quitRequested() const { return m_shouldQuit; }
    std::string getResponse() const { return m_response; }

    bool isLastInputValid() const { return m_isLastInputValid; }
    std::string getLastInputVerb() const { return m_lastInputVerb; }

  private:
    bool isVerb(const std::string& input) const;
    void updateResponse(const std::string& input);

    std::vector<std::string> verbs{ "exit", "look", "take" };

    std::string m_response;
    std::string m_lastInputVerb;
    const std::string INVALID_RESPONSE{ "Sorry?" };

    bool m_shouldQuit{ false };
    bool m_isLastInputValid{ false };
};