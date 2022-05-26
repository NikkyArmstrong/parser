#include <memory>
#include <string>
#include <vector>

#include "ParseStates.h"
#include "State.h"

class Parser
{
  public:
    Parser();

    void parse(std::string input);

    bool quitRequested() const { return m_shouldQuit; }
    std::string getResponse() const { return m_response; }

    bool isLastInputValid() const { return m_isLastInputValid; }

    std::string getLastInputOfType(EGrammarState type) const;

    std::vector<std::string> getTokens(const std::string& input) const;

  private:
    void Reset();

    bool isVerb(const std::string& input) const;
    bool isPreposition(const std::string& input) const;
    bool isArticle(const std::string& input) const;
    bool isObject(const std::string& input) const;

    void updateResponse(const std::string& input);

    std::unique_ptr<State> createState(EGrammarState state, std::string token) const;

    const std::vector<std::string> verbs{ "exit", "look", "take" };
    const std::vector<std::string> prepositions{"at"};
    const std::vector<std::string> articles{"the"};

    std::string m_response;

    const std::string INVALID_RESPONSE{ "Sorry?" };
    bool m_shouldQuit{ false };
    bool m_isLastInputValid{ false };

    std::vector<std::unique_ptr<State>> m_currentStates;
};