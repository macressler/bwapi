Class header file: [BWAPI/Force.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/Force.h#)

A "Force" is another name for "Team". See the [FAQ](FAQ#What_is_a_Force?.md) on why this term is used instead.

The Force class is used to get information about each force in the match, such as the name of the force and the set of players in the force. In team-based [GameTypes](GameTypes.md), such as GameTypes::Team\_Melee, each Force object will correspond to a different team. In non team-based matches, though, it is common for all players to be contained in the same Force.

Methods:

  * [getName](#getName.md)
  * [getPlayers](#getPlayers.md)

### getName ###
std::string getName() const;

Returns the name of the force.

### getPlayers ###
std::set< [Player](Player.md)`*` > getPlayers() const;

Returns the set of players in the force. For team-based [GameTypes](GameTypes.md), this will return the set of players on this team.