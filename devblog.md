# Parser
Text parser for text adventure using TDD

## Post 1

### Configuration
Attempted to compile Catch2 using old vanilla makefile - that didn't work

Installed cmake, followed tutorial for basic cmake compilation.

Added test folder with new exe test_main
Added 3rdparty folder for catch.hpp

### TDD to start

I've started by writing a very basic design document for the beginning commands I will support and to get some thoughts down. These will become the basis for the first tests. As we progress, the design document will evolve alongside the tests and the code. (this is in a later commit `b9b486fcea816640b8c04e7a4c96d30a7a855237`)

Started with very simple examples. First command in design doc: exit.
One function, no class `bool parse(string)`
Given - game is running
When - user types exit
Then - game quits

`Commit 4d5c8739d56bd6207115244f86ea6941c9e215f7`

Next test - look at the error conditions. We need to handle the user not typing anything. Simple way to require us to get a response from the parser.
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

## Post 2
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

## Post 3

<!--Insert commit from big PC here.-->

What do we do next - look in the design doc. We could forge ahead and start building the game framework for the text adventure. But our goal is to write a parser. If we look at our design doc we can see that the first step is to build a parser that interprets a sentence with english language and grammar rules.

`Commit 0f1c5a88d826a0a07be653c7ff2262f01d57915a changed direction here`

The next command in the design doc (and the most common thing to do in a text adventure) is just "look". Without any other input, the game would usually return a description of the room. Let's have a think about what "look" should do, write the design, then write the tests.
The design we've written so far is simple (if we want to change it later, we use the tests to help us refactor).
We need the parser to identify the verb, (optional) preposition, (optional) article, and the object.

`look (verb) at (preposition) the (article) donkey (object)`
`look at donkey`
`look donkey`

all should give the same result.

However if we want to also support `look under the donkey`, `look under donkey` is equivalent, but `look donkey` is not.

The parser isn't connected to a game, so we can't do anything with this information, and we don't have the concept of a donkey, much less under the donkey, but the first step is getting it to actually parse. We need to write some tests to get the parser to identify what grammar constructs are present in the sentence, and whether the sentence is constructed correctly. So we'll start by just getting the game to recognise verbs.

```
WHEN("the parser is given a verb")
{
  _parser.parse("look");
  THEN("the parser identifies that this is a validly constructed sentence")
  {
    REQUIRE(_parser.isLastInputValid(), "Input was not a validly constructed sentence");
  }
  AND_THEN("the parser identifies that this sentence contains a verb")
  {
    REQUIRE(_parser.getLastInputVerb() == "look");
  }
}
```

For now, as always, we've just kinda guessed at the interface based on what the test needs to do. We need to check a) was the last input valid, and b) did the parser work out what the verb was in the last sentence.

Obviously these tests don't pass, so we need to write enough code so they do. Start by defining the two test-facing functions.

```
bool isLastInputValid() { return true; }
std::string getLastInputVerb() { return "look"; }
```

This is not just me being intentionally obtuse, we need to write more tests so that these functions don't pass them. /Then/ we can confidently write the real code. If we only code to the positive case, we run the risk of the negative case not working correctly in production code.

`Commit 98c96e316882c01f5fceb680d07ba91e26f94c62`

Write a test for an invalid sentence - note that so far an invalid sentence is just one that does not exactly equal a verb we recognise.

```
AND_WHEN("the parser is not given a valid sentence")
{
  _parser.parse("foo");
  THEN("the parser identifies that this is not a validly constructed sentence")
  {
    REQUIRE(!_parser.isLastInputValid());
  }
}
```

Then make it have to recognise a new verb. That way `getLastInputVerb` can't just return the string 'look'.

```
Scenario: the parser can identify correct grammar
      Given: we have a parser
   And when: the parser is given a different verb
        And: the parser identifies that this sentence contains the correct verb
-------------------------------------------------------------------------------
D:\Code\Cpp\Parser\test\test_main.cpp(76)
...............................................................................

D:\Code\Cpp\Parser\test\test_main.cpp(78): FAILED:
  REQUIRE( _parser.getLastInputVerb() == "take" )
with expansion:
  "look" == "take"
```

Note: later we will make these parameterised tests!

Now we write code to make the tests pass.
Start by making a vector of allowed verbs. This might not be the best data structure, but we know it will make the tests pass. Once the tests pass, if we decide we want to use some other structure here (for speed or space or some other reason), the tests will make sure we refactor correctly. We also only want to do this if we have an identified reason. If we had 1000 verbs, the find call we've added might be a problem, and we might need to look at something else. For three verbs, its probably ok for now.

`Commit 0434657bcc15f4c4949e001d63ea936404d237a6`

## Post 4

Double check the design - if the verb is invalid, return an error. We don't have a test for this.
We're going to double check the design (only focussing on verbs) against the tests and make sure everything is covered.
We update the tests to use `isLastInputValid` to determine correct and incorrect inputs. We also realise one of the tests is now irrelevant! We don't want to just repeat a phrase back to the user. We want "Sorry?" for invalid, and at the moment, we don't care about valid responses, just that we have interpreted the phrase as valid.

`Commit 825bd1da7bc654b03a582ec01b4b9f50c41ef5bd`

Exit is a verb, so add it to the list. The we do a little bit more refactoring to make the code nicer (const correctness, helper functions, const refs etc). We are confident, because we have the tests.

`Commit f3be9ce76d77484d189a43aa1eb4b2b75f7aae2f`

## Post 5

Next step - we're going to want to test every verb our game supports. At the moment we have three tests - exit, look, and take. Let's parameterise the tests to test each verb. Then when we add more, we can just update the parameters.

```
Parser _parser;
WHEN("the parser is given a verb")
{
  auto v = GENERATE("exit", "look", "take");
  _parser.parse(v);
  THEN("the parser identifies that this is a validly constructed sentence")
  {
    REQUIRE(_parser.isLastInputValid());
  }
  AND_THEN("the parser identifies that this sentence contains the correct verb")
  {
    REQUIRE(_parser.getLastInputVerb() == v);
  }
}
```

The design doc says the game is case-insensitive. Let's add in some verbs to the parameters in different cases.

`Commit 


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
