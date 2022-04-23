# Parser for a Text Adventure

Create a parser that can interpret an english language sentence structure and perform an action, give a response.

# Parser Design

## Commands

Each command must be a properly constructed English sentence. These sentences are in SVO form (Subject-Verb-Object), as in "Sam looks at the tree".

The game is case-insensitive.

### Subject
The subject is not expected to be provided ("I" is always implied, the player will be doing all of the actions).

If the player does provide the subject, the game will return an error message. (TBA)

### Verbs
A verb must be provided in each sentence. If no verb is recognised, the game will return an error message.

* **Exit** : exits the game.
* **Look** : On its own, implies look at the current room. Returns the description of the current room and any items.
* **Look (object)**: Returns a description of the object.
* **Take**: (take object) - if takeable, puts the object into the player's inventory, and returns "You took the (object)". If not takeable returns a phrase e.g. "You cannot take the (object)". Some objects may have custom phrases when they are taken (or can't be taken).

### Prepositions
Supported prepositions are listed below (TBA).
Prepositions are optional. If the verb expects a preposition and it is not provided, the most likely will be assumed.
For example, "look box" will be interpreted the same as "look at the tree". "look in the box" would need specifying exactly.

* **at**: With **look**. Look (at) (the) object.

### Article
If a qualifying article is not supplied, "the" will be assumed. "look at tree" and "look at the tree" are interpreted the same.

* **the** optional, players may construct a more correct sentence using the definite article

## Error conditions
If the player provides no input, the game will respond appropriately, e.g. "Sorry?"


# For later
* **to**: With **talk**.
* **all** Look all, take all
* **a, an**: indefinite article, for more than one object
**on, under, in, by**

# Text Adventure Design

## Rooms

## Objects

## Puzzles

## Story