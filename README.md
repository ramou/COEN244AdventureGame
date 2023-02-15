# COEN244AdventureGameV1

## Spaces
`ISpace` is the base class that represents a position in the dungeon. It keeps track of neighbouring spaces and has a method to return its neighboring spaces or itself based on a desired movement direction. It is an abstract class and does not have a concrete implementation for the `makeMove` method.

`Floor` represents the spaces the player can walk on and where we might find items.

`Stairs` represent a means to teleport to other levels.

`Wall` represents the actual walls in the dungeon. The should look clearly like walls, definitely not like floors.

`VoidSpace` represents the spaces that aren't really in the map. We include them to simplify the navigation.
