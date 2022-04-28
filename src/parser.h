#include <string>
#include <vector>

class Parser
{
  public:
    void parse(std::string input);

    bool quitRequested() const { return m_shouldQuit; }
    std::string getResponse() const { return m_response; }

    bool isLastInputValid() const { return m_isLastInputValid; }

    std::string getLastInputVerb() const { return m_lastInputVerb; }
    std::string getLastInputPreposition() const { return m_lastInputPreposition; }
    std::string getLastInputArticle() const { return m_lastInputArticle; }
    std::string getLastInputObject() const { return m_lastInputObject; }

std::vector<std::string> getTokens(const std::string& input) const;

  private:
    bool isVerb(const std::string& input) const;
    void updateResponse(const std::string& input);



    const std::vector<std::string> verbs{ "exit", "look", "take" };

    std::string m_response;

    std::string m_lastInputVerb;
    std::string m_lastInputPreposition;
    std::string m_lastInputArticle;
    std::string m_lastInputObject;

    const std::string INVALID_RESPONSE{ "Sorry?" };

    bool m_shouldQuit{ false };
    bool m_isLastInputValid{ false };
};