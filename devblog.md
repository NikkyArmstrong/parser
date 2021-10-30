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

`Commit 4d5c8739d56bd6207115244f86ea6941c9e215f7`

Next test
Given - game is running
When - user does not type anything
Then - game tells the user to type something

Now we need access to the output!

Refactor, only enough to pass this test.

Then - we can refactor to make `shouldQuit` a member variable. Tests ensure we did it right.

`Commit `

Then - we can refactor to use getters and provide good encapsulation and access.

`Commit `

Note there is no code in main for any of this!