Class header file: [BWAPI/Event.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/Event.h#)

Events correspond to [AIModule](AIModule.md) callbacks and can be obtained by calling [Game::getEvents](Game#getEvents.md).

Methods:

  * [getType](#getType.md)
  * [getPosition](#getPosition.md)
  * [getText](#getText.md)
  * [getUnit](#getUnit.md)
  * [getPlayer](#getPlayer.md)
  * [isWinner](#isWinner.md)

### getType ###
EventType::Enum getType() const;

Returns the type of the Event.

### getPosition ###
Position getPosition() const;

Returns the Position. Used in EventType::NukeDetect.

### getText ###
std::string& getText() const;

Returns the text. Used in EventType::SendText, EventType::ReceiveText, EventType::SaveGame.

### getUnit ###
Unit`*` getUnit() const;

Returns the unit. Used in EventType::UnitDiscover, EventType::UnitEvade, EventType::UnitCreate, EventType::UnitDestroy, EventType::UnitShow, EventType::UnitHide, EventType::UnitMorph, EventType::UnitRenegade, and EventType::UnitComplete.

### getPlayer ###
Player`*` getPlayer() const;

Returns the player. Used in EventType::ReceiveText and EventType::PlayerLeft.

### isWinner ###
bool isWinner() const;

Returns true if the BWAPI-controlled player is the winner. Used in EventType::MatchEnd.

### Events ###

The EventType Enum contains the following values, which have been linked with their corresponding [AIModule](AIModule.md) callbacks for more information:

  * [MatchStart](AIModule#onStart.md)
  * [MatchEnd](AIModule#onEnd.md)
  * [MatchFrame](AIModule#onFrame.md)
  * [SendText](AIModule#onSendText.md)
  * [ReceiveText](AIModule#onReceiveText.md)
  * [PlayerLeft](AIModule#onPlayerLeft.md)
  * [NukeDetect](AIModule#onNukeDetect.md)
  * [UnitDiscover](AIModule#onUnitDiscover.md)
  * [UnitEvade](AIModule#onUnitEvade.md)
  * [UnitShow](AIModule#onUnitShow.md)
  * [UnitHide](AIModule#onUnitHide.md)
  * [UnitCreate](AIModule#onUnitCreate.md)
  * [UnitDestroy](AIModule#onUnitDestroy.md)
  * [UnitMorph](AIModule#onUnitMorph.md)
  * [UnitRenegade](AIModule#onUnitRenegade.md)
  * [UnitComplete](AIModule#onUnitComplete.md)
  * [SaveGame](AIModule#onSaveGame.md)
  * None