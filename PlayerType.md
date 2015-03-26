Class header file: [BWAPI/PlayerType.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/PlayerType.h#)

List of all [PlayerTypes](PlayerTypes.md).

Methods:

  * [getID](#getID.md)
  * [getName](#getName.md)

Non-member methods in PlayerTypes namespace:

  * [getPlayerType](#getPlayerType.md)
  * [allPlayerTypes](#allPlayerTypes.md)


### getID ###
int getID();

Returns the unique ID for this player type.

### getName ###
std::string getName();

Returns the name of the player type. For example PlayerTypes::Computer.getName() will return an std::string object containing "Computer".

### getPlayerType ###
[PlayerType](PlayerType.md) getPlayerType(std::string name);

Given the name of a player type, this function will return the PlayerType. For example: PlayerTypes::getPlayerType("Player") will return PlayerTypes::Player.

### allPlayerTypes ###
std::set<[PlayerType](PlayerType.md)>& allPlayerTypes();

Returns the set of all the [PlayerTypes](PlayerTypes.md).