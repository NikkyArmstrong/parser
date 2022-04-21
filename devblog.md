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
Given - game is running (this will get more useful later)
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

`Commit 15e438226abe9eb0a485a2d82cc54ed75cd0c031`

<!--Insert commit from big PC here.-->

What do we do next. We could forge ahead and start building the game framework for the text adventure. But our goal is to write a parser. If we look at our design doc <!--TBC!--> we can see that the first step is to build a parser that interprets a sentence with english language and grammar rules.

The most








<!-- Put all this later in the blog -->

We're not sure, so think about what we'd like a text adventure to do, and write some tests.

The first thing we could do, is just get "look" as a string, to return some kind of string, and pass the test that way.

```
_parser.parse("look");
THEN("the game gives a description of the room")
{
  REQUIRE(_parser.getResponse() == "the description of the room");
}
```

But, we've already shown that our parser supports this with other tests, so we can skip this step. This is where the tests will start dictating our architecture. Instead, make the test:

```
SCENARIO("the player can look", "[parser]")
{
  Parser _parser;
  GIVEN("the game has a room")
  {
    Room _room("a nice room");
    WHEN("the player inputs look")
    {
      _parser.parse("look");
      THEN("the game gives a description of the room")
      {
        REQUIRE(_parser.getResponse() == _room.getDescription());
      }
    }
  }
}
```

I purposefully haven't made the test too complicated, this is part of it. I didn't say "the player is in the room" or that the room has anything in it. All we need to pass this test is a room class, that has a description string, with a getter. I've decided that the description will be set in the constructor. We don't need a setter, because the test doesn't call one. I can't think of a test case that would require us to use a setter for the description of the room class, and the design doesn't imply one.

**Nikkynote: This should match a brief design, but show how the tests enhance and refine that design.**

Make a room class:
<insert code>?

`Commit 586afc83168f91297b0a64a2b77d6dbbf334d9a0`

Ok, built the room, and it now compiles. But the test fails still. We finally need to start building the actual game framework.
We can refactor the code, confident because the existing tests will tell us if we've done anything wonky. When the new test passes, we know we've done enough.
That means - we need some kind of game driver, which holds a Parser object and can accept input. The driver also needs to know what room we're currently in.

Try this
```
void processInput(std::string input);
std::string getResponse();
```

All this is is a pass-through for the parser. What we really want is the parser to be able to access the game state.

We need a good architecture to achieve this.

Options:
- Driver owns the parser, pass the driver through to the parser in the parse call
- create the driver inside the parser (parser owns the driver)
- create a system where the parser can ask for the game state from some kind of provider
  - static GetWorld() style function so we can do GetWorld()->GetCurrentRoom()
