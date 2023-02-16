# COEN244AdventureGameV1

## Spaces
`ISpace` is the base class that represents a position in the dungeon. It keeps track of neighbouring spaces and has a method to return its neighboring spaces or itself based on a desired movement direction. It is an abstract class and does not have a concrete implementation for the `makeMove` method.

`Floor` represents the spaces the player can walk on and where we might find items.

`Stairs` represent a means to teleport to other levels.

`Wall` represents the actual walls in the dungeon. The should look clearly like walls, definitely not like floors.

`VoidSpace` represents the spaces that aren't really in the map. We include them to simplify the navigation.

`OtherSpace` represents an error while reading the map file. If we didn't recognize the character, we output a message once, and then treat it like a `Floor`

<img src="https://raw.githubusercontent.com/ramou/COEN244AdventureGame/main/COEN244AdventureGameV1/Space.png" />

### ChatGPT Says:

* `ISpace`: This is an interface class that defines the basic behavior of a dungeon space. It has the following pure virtual functions:
  *  `move(origin)`: a function that takes a reference to an `ISpace` object representing the current space and returns the `ISpace` object representing the new space after a move.
  *  `makeMove(m)`: a function that takes a char representing the move to be made (e.g., 'N' for north) and returns the `ISpace` object representing the new space after the move.
  *  `draw()`: a function that prints a character representing the space.

* `Wall`: This is a subclass of `ISpace` that represents a wall in the dungeon. It has the following properties:
  *  `draw()`: a concrete implementation of the `draw()` function that prints a '#' character.
  *  `move(origin)`: a concrete implementation of the `move(origin)` function that always returns the `ISpace` object representing the current space.
  *  `makeMove(m)`: a concrete implementation of the `makeMove(m)` function that always returns the `Wall` object itself.
  *  `WALL`: a static pointer to a `Wall` object that represents a wall space.

* `VoidSpace`: This is a subclass of `Wall` that represents a void space in the dungeon. It has the following properties:
  *  `draw()`: a concrete implementation of the `draw()` function that prints a ' ' (space) character.

* `Floor`: This is a subclass of `ISpace` that represents a walkable space in the dungeon. It has the following properties:
  *  `draw()`: a concrete implementation of the `draw()` function that prints a '.' character.
  *  `move(origin)`: a concrete implementation of the `move(origin)` function that always returns the `Floor` object itself.
  *  `makeMove(m)`: a concrete implementation of the `makeMove(m)` function that takes a char representing the move to be made (e.g., 'n' for north). The function returns a reference to an `ISpace` object representing the neighboring space in the specified direction based on the input move, or a reference to the current Floor object `*this` if the input move is not recognized.
  *  `north`, `south`, `east`, `west`: pointers to `ISpace` objects representing the neighboring spaces. They are initialized to point to the `Wall::WALL` object to avoid null pointer issues.

* `Other`: This is a subclass of Floor that represents a walkable space with an unexpected character in the dungeon. It has the following properties:
  *  `c`: the unexpected character that was encountered.
  *  `draw()`: a concrete implementation of the `draw()` function that prints a '.' character.

* `Stairs`: This is a subclass of Floor that represents a walkable space with a staircase in the dungeon. It has the following properties:
  *  `draw()`: a concrete implementation of the `draw()` function that prints a '<' character.
