# Parser
Text parser for text adventure using TDD

## Day 1

### Configuration
Attempted to compile Catch2 using old vanilla makefile - that didn't work

Installed cmake, followed tutorial for basic cmake compilation

Added test folder with new exe test_main
Added 3rdparty folder for catch.hpp

### TDD to start
Started with very simple examples
One function, no class `bool parse(string)`
Given - game is running
When - user types exit
Then - game quits

Next test
Given - game is running
When - user does not type anything
Then - game tells the user to type something

Now we need access to the output!

Refactor, only enough to pass this test.

Then - we can refactor to make `shouldQuit` a member variable. Tests ensure we did it right.

Then - we can refactor to use getters and provide good encapsulation and access.

