Class header file: [BWAPI/AIModule.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/AIModule.h#)

AIModule is a class that is intended to be implemented or inherited by a custom AI class. The following callbacks available to AIs:

  * [onStart](#onStart.md)
  * [onEnd](#onEnd.md)
  * [onFrame](#onFrame.md)
  * [onSendText](#onSendText.md)
  * [onReceiveText](#onReceiveText.md)
  * [onPlayerLeft](#onPlayerLeft.md)
  * [onNukeDetect](#onNukeDetect.md)
  * [onUnitDiscover](#onUnitDiscover.md)
  * [onUnitEvade](#onUnitEvade.md)
  * [onUnitShow](#onUnitShow.md)
  * [onUnitHide](#onUnitHide.md)
  * [onUnitCreate](#onUnitCreate.md)
  * [onUnitDestroy](#onUnitDestroy.md)
  * [onUnitMorph](#onUnitMorph.md)
  * [onUnitRenegade](#onUnitRenegade.md)
  * [onSaveGame](#onSaveGame.md)

Notes:

Using BWAPI in a different thread than the default one will produce unexpected results and possibly crash the program. Multi-threaded AIs are possible so long as all BWAPI interaction is limited to the default thread (during one of the call-backs).

### onStart ###
void onStart();

BWAPI calls this at the start of a match. Typically an AI will execute set up code in this method (initialize data structures, load build orders, etc).

### onEnd ###
void onEnd(bool isWinner);

BWAPI calls this at the end of the match. isWinner will be true if the AIModule won the game. If the game is a replay, isWinner will always be false.

### onFrame ###
void onFrame();

BWAPI calls this on every logical frame in the game.

### onSendText ###
void onSendText(std::string text);

If [Flag](Misc#Flag.md)::UserInput is enabled, BWAPI will call this each time a user enters a message into the chat. If you want the message to actually show up in chat, you can use [Game::sendText](Game#sendText.md) to send the message to other players (if the game is multiplayer), or use [Game::printf](Game#printf.md) if you want the message to just show up locally.

### onReceiveText ###
bool onReceiveText([Player](Player.md)`*` player, std::string text);

BWAPI calls this each time it receives a message from another player in the chat.

### onPlayerLeft ###
bool onPlayerLeft([Player](Player.md)`*` player);

BWAPI calls this when a player leaves the game.

### onNukeDetect ###
bool onNukeDetect([Position](Misc#Position.md) target);

BWAPI calls this when a nuclear launch has been detected. If the target position is visible, or if Complete Map Information is enabled, the target position will also be provided. If Complete Map Information is disabled and the target position is not visible, target will be set to Positions::Unknown.

### onUnitDiscover ###
void onUnitDiscover([Unit](Unit.md)`*` unit);

BWAPI calls this when a unit becomes accessible. If Complete Map Information is enabled, this will be called at the same time as [AIModule::onUnitCreate](#onUnitCreate.md), otherwise it will be called at the same time as [AIModule::onUnitShow](#onUnitShow.md).

### onUnitEvade ###
void onUnitEvade([Unit](Unit.md)`*` unit);

BWAPI calls this right before a unit becomes inaccessible. If Complete Map Information is enabled, this will be called at the same time as [AIModule::onUnitDestroy](#onUnitDestroy.md), otherwise it will be called at the same time as [AIModule::onUnitHide](#onUnitHide.md).

### onUnitShow ###
void onUnitShow([Unit](Unit.md)`*` unit);

BWAPI calls this when a unit becomes visible. If Complete Map Information is disabled, this also means that the unit has just become accessible.

### onUnitHide ###
void onUnitHide([Unit](Unit.md)`*` unit);

BWAPI calls this right before a unit becomes invisible. If Complete Map Information is disabled, this also means that the unit is about to become inaccessible.

### onUnitCreate ###
void onUnitCreate([Unit](Unit.md)`*` unit);

BWAPI calls this when an accessible unit is created. Note that this is NOT called when a unit changes type (such as larva into egg or egg into drone). Building a refinery/assimilator/extractor will not produce an onUnitCreate call since the vespene geyser changes to the unit type of the refinery/assimilator/extractor. If the unit is not accessible at the time of creation (i.e. if the unit is invisible and Complete Map Information is disabled), then this callback will NOT be called. If the unit is visible at the time of creation, [AIModule::onUnitShow](#onUnitShow.md) will also be called.

### onUnitDestroy ###
void onUnitDestroy([Unit](Unit.md)`*` unit);

BWAPI calls this when a unit dies or otherwise removed from the game (i.e. a mined out mineral patch). When a Zerg drone becomes an extractor, the Vespene geyser changes to the Zerg Extractor type and the drone is destroyed. If the unit is not accessible at the time of destruction, (i.e. if the unit is invisible and Complete Map Information is disabled), then this callback will NOT be called. If the unit was visible at the time of destruction, [AIModule::onUnitHide](#onUnitHide.md) will also be called.

### onUnitMorph ###
void onUnitMorph([Unit](Unit.md)`*` unit);

BWAPI calls this when an accessible unit changes type, such as from a Zerg Drone to a Zerg Hatchery, or from a Terran Siege Tank Tank Mode to Terran Siege Tank Siege Mode. This is not called when the type changes to or from UnitTypes::Unknown (which happens when a unit is transitioning to or from inaccessibility).

### onUnitRenegade ###
void onUnitRenegade([Unit](Unit.md)`*` unit);

BWAPI calls this when an accessible unit changes ownership.

### onSaveGame ###
void onSaveGame(std::string gameName);

BWAPI calls this when the user saves the match. The gameName will be the name that the player entered in the save game screen.