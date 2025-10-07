= Ubiquitous Language

== Game Loop Bounded Context

- Game Loop := procedure that controlls the flow of the game
- Player := character controlled by a human player
- Enemy := character controlled by ai that acts as opponents for the player
- Items :=Something that can be picked up by players that provides some sort of benefit for the player
- Map := game world with items, players and enemies

== Player Bounded Context

- Player := human being that is playing the game
- Character := representation of the Player in the virtual environment
- Stats := attributes of the character
- Actions := something the character can do (i.e. attack, defend, move) refered to individually as Action\<Action\> i.e. ActionMove

== Items Bounded Context

- Item := object the player can pick up that will provide the player with some sort of benefit
- Stats := attributes of the item (will be attributed additively to tyhe player)

== World Bounded Context

- World := virtual environemnt where the game is happening
- Entity := something that is existing in the virtual environment (i.e. Player, Enemy or Item)
- Map := grid of tiles
- Tile := smallest unit of location. Can be walkable, restricted or blocked
- Position := pair of coordinates $(x, y)$ that represents a exact position in the world

== Combat Bounded Context

- Combat := encounter between the player and one or more enemies in the virtual world
- Action := something a participant of the combat (either player or enemy)
- Attack := a participant is making a move to damage another participant that is in the combat
