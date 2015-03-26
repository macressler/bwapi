Class header file: [BWAPI/GameType.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/GameType.h#)

List of all [GameTypes](GameTypes.md).

Methods:

  * [getID](#getID.md)
  * [getName](#getName.md)

Non-member methods in GameTypes namespace:

  * [getGameType](#getGameType.md)
  * [allGameTypes](#allGameTypes.md)


### getID ###
int getID();

Returns the unique ID for this game type.

### getName ###
std::string getName();

Returns the name of the game type. For example GameTypes::Free\_For\_All.getName() will return an std::string object containing "Free For All".

### getGameType ###
[GameType](GameType.md) getGameType(std::string name);

Given the name of a game type, this function will return the GameType. For example: GameTypes::getGameType("Use Map Settings") will return GameTypes::Use\_Map\_Settings.

### allGameTypes ###
std::set<[GameType](GameType.md)>& allGameTypes();

Returns the set of all the [GameTypes](GameTypes.md).