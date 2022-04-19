#include <string>

class Room
{
public:
  Room(std::string roomDescription);

  std::string getDescription() { return description }

private:
  std::string description;
};
