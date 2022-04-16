# Parser
Text parser for text adventure using TDD

## Day 1

### Configuration
Attempted to compile Catch2 using old vanilla makefile - that didn't work

Installed cmake, followed tutorial for basic cmake compilation.

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

`Commit c84e9024431bcd91a535ce4907accaa81dccb24f`

Then - we can refactor to make `shouldQuit` a member variable. Tests ensure we did it right.

`Commit 3ed9e2fc99156af22820bd955f036aa95a1086f4`

Then - we can refactor to use getters and provide good encapsulation and access.

`Commit 95009014b537476de1f2666576ef27c5a309f49a`

Note there is no code in main for any of this!

## Returned to this after some time
How the heck do you compile?

cmake needs to configure the project first, then build it

per esemple

Create a build directory. In the directory call build with the path to the source.
`cd build`
`cmake ../`
`cmake --build .`

This also lets you load it up in VS

Tried to update main to use the parser instead of separate code. Realised that typing "exit" does not give a response.
Wrote a test to check that exit gives a response - check that response is not empty. This fails, because the response is empty.
Technically to pass this test we can make it return anything - we know this, so we can skip to the next step. Update the test to check the phrase we want.

Now we aren't getting the output in main we expect. We should be getting "Sorry?" if the input is empty. The test for this passes, but main isn't doing what we want.

`Commit 49347e879e2184ebaadf4acd690b38def0f745f8`

We'll write a new test to cover the other case - if the player writes anything else, return the same sentence.
Write the test to check for this. It fails!

`Commit ee97923d53756570ec1bcb3f3f5a96302884742f`

This meant we needed a little refactor to use if/else. All tests pass.

Now re-look at main. Exit is working. You said: "" is working. Empty input isn't working.
Maybe this is because stdin doesn't accept just a return.
Debugging in VS shows that I'm right about this - it doesn't return from the cin if there is no input.

We need to use `std::getline`



