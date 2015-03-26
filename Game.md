Class header file: [BWAPI/Game.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/Game.h#)

The abstract Game class is implemented by BWAPI and offers many methods for retrieving information about the current Broodwar game, including the set of players, units, map information, as well as information about the user, such as mouse position, screen position, and the current selection of units.



# Methods #

## getForces ##
```

std::set< [Force]* >& getForces();```
Returns the set of all forces in the match.

> _See also: [Game::getForce](Game#getForce.md)_

## getPlayers ##
```

std::set< [Player]* >& getPlayers();```
Returns the set of all players in the match. Note that this includes the Neutral player, which owns all the neutral units such as minerals, critters, etc.

## getAllUnits ##
```

std::set< [Unit]* >& getAllUnits();```
Returns all the visible units. If [Flag](Flag.md)::CompleteMapInformation is enabled, the set of all units is returned, not just visible ones. Note that units inside refineries are not included in this set yet.

#### Warning about Multi-Threaded AIs ####
If you are using multiple threads for your AI(s) AND you are using these units outside of a BWAPI event thread, it is not recommended to use this function as of BWAPI4.  Currently you may run into a Heap corruption error if you do related to the destructor of Vectorset.  One possible way around this is:

```
Playerset players = Broodwar->getPlayers();

for (Playerset::iterator it = players.begin();it != players.end();it++)
{
  Player* player = *it;
  Unitset units = player->getUnits();
  
  ... Do whatever you need to do with the units ...
}
```

> _See also: [Player::getUnits](Player#getUnits.md), [Game::getMinerals](Game#getMinerals.md), [Game::getGeysers](Game#getGeysers.md), [Game::getNeutralUnits](Game#getNeutralUnits.md), [Game::getStaticMinerals](Game#getStaticMinerals.md), [Game::getStaticGeysers](Game#getStaticGeysers.md), [Game::getStaticNeutralUnits](Game#getStaticNeutralUnits.md)_

## getMinerals ##
```

std::set< [Unit]* >& getMinerals();```
Returns the set of all accessible (visible) mineral patches.

> _See also: [Game::getGeysers](Game#getGeysers.md), [Game::getNeutralUnits](Game#getNeutralUnits.md), [Game::getStaticMinerals](Game#getStaticMinerals.md), [Game::getStaticGeysers](Game#getStaticGeysers.md), [Game::getStaticNeutralUnits](Game#getStaticNeutralUnits.md)_

## getGeysers ##
```

std::set< [Unit]* >& getGeysers();```
Returns the set of all accessible (visible) vespene geysers.

> _See also: [Game::getMinerals](Game#getMinerals.md), [Game::getNeutralUnits](Game#getNeutralUnits.md), [Game::getStaticMinerals](Game#getStaticMinerals.md), [Game::getStaticGeysers](Game#getStaticGeysers.md), [Game::getStaticNeutralUnits](Game#getStaticNeutralUnits.md)_

## getNeutralUnits ##
```

std::set< [Unit]* >& getNeutralUnits();```
Returns the set of all accessible (visible) neutral units, including mineral fields, vespene geysers, critters, and possibly other units owned by the neutral player.

> _See also: [Game::getMinerals](Game#getMinerals.md), [Game::getGeysers](Game#getGeysers.md), [Game::getStaticMinerals](Game#getStaticMinerals.md), [Game::getStaticGeysers](Game#getStaticGeysers.md), [Game::getStaticNeutralUnits](Game#getStaticNeutralUnits.md)_

## getStaticMinerals ##
```

std::set< [Unit]* >& getStaticMinerals();```
Returns the set of all mineral patches (including mined out and other inaccessible ones).

> _See also: [Game::getMinerals](Game#getMinerals.md), [Game::getGeysers](Game#getGeysers.md), [Game::getNeutralUnits](Game#getNeutralUnits.md), [Game::getStaticGeysers](Game#getStaticGeysers.md), [Game::getStaticNeutralUnits](Game#getStaticNeutralUnits.md)_

## getStaticGeysers ##
```

std::set< [Unit]* >& getStaticGeysers();```
Returns the set of all vespene geysers (including mined out and other inaccessible ones).

> _See also: [Game::getMinerals](Game#getMinerals.md), [Game::getGeysers](Game#getGeysers.md), [Game::getNeutralUnits](Game#getNeutralUnits.md), [Game::getStaticMinerals](Game#getStaticMinerals.md), [Game::getStaticNeutralUnits](Game#getStaticNeutralUnits.md)_

## getStaticNeutralUnits ##
```

std::set< [Unit]* >& getStaticNeutralUnits();```
Returns the set of all neutral units (including mined out and other inaccessible ones).

> _See also: [Game::getMinerals](Game#getMinerals.md), [Game::getGeysers](Game#getGeysers.md), [Game::getNeutralUnits](Game#getNeutralUnits.md), [Game::getStaticMinerals](Game#getStaticMinerals.md), [Game::getStaticGeysers](Game#getStaticGeysers.md)_

## getBullets ##
```

std::set< [Bullet]* >& getBullets();```
Returns the set of all accessible bullets.

## getNukeDots ##
```

std::set< [Misc#Position Position] >& getNukeDots();```
Returns the set of all accessible nuke dots.

## getEvents ##
```

std::list< [Event] >& getEvents();```
Returns the list of events for the current frame. Events correspond to AIModule callbacks, so for example rather than implementing [AIModule::onUnitCreate](AIModule#onUnitCreate.md) you could check the list of events every frame and look for [Event::UnitCreate](Event#UnitCreate.md).

## getForce ##
```

[Force]* getForce(int forceID);```
Returns the [Force](Force.md) with the given ID, or `NULL` if no [Force](Force.md) has the given ID.

> _See also: [Game::getForces](Game#getForces.md)_

## getPlayer ##
```

[Player]* getPlayer(int playerID);```
Returns the [Player](Player.md) with the given ID, or `NULL` if no [Player](Player.md) has the given ID.

## getUnit ##
```

[Unit]* getUnit(int unitID);```
Returns the [Unit](Unit.md) with the given ID, or `NULL` if no [Unit](Unit.md) has the given ID.

## indexToUnit ##
```

[Unit]* indexToUnit(int unitIndex);```
Given an index value between 0 and 1699, this function will return the Unit`*` currently associated with the index value in Starcraft's internal Unit table. Only available when the Complete Map Information flag is enabled.

## getRegion ##
```

[Region]* getRegion(int regionID);```
Returns the [Region](Region.md) with the given ID, or `NULL` if no [Region](Region.md) has the given ID.

## getAllRegions ##
```

const std::set<[Region]*> &getAllRegions() const;```
Returns a set containing all [Region](Region.md)s on the map.

## getRegionAt ##
```

[Region] *getRegionAt(int x, int y) const;
[Region] *getRegionAt([Position] position) const;```
Returns the [Region](Region.md) at a given pixel position.

## getGameType ##
```

[GameType] getGameType();```
Returns the game type of the given match, or GameTypes::None if Starcraft is in a replay.

## getLatency ##
```

Latency::Enum getLatency();```
Returns the amount of latency the current game has.

> _Note: This value may be incorrect. Use [Game::getLatencyFrames](Game#getLatencyFrames.md) to obtain an accurate value._

## getLatencyFrames ##
```

int getLatencyFrames();```
Returns the maximum number of frames required for unit commands to be processed by the game.

> _See also: [Game::getLatencyTime](Game#getLatencyTime.md), [Game::getRemainingLatencyFrames](Game#getRemainingLatencyFrames.md), [Game::getRemainingLatencyTime](Game#getRemainingLatencyTime.md)_

## getLatencyTime ##
```

int getLatencyTime();```
Returns the maximum time in milliseconds required for unit commands to be processed by the game.

> _See also: [Game::getLatencyFrames](Game#getLatencyFrames.md), [Game::getRemainingLatencyFrames](Game#getRemainingLatencyFrames.md), [Game::getRemainingLatencyTime](Game#getRemainingLatencyTime.md)_

## getRemainingLatencyFrames ##
```

int getRemainingLatencyFrames();```
Returns the remaining number of frames before a unit command sent in the current frame can be processed.

> _See also: [Game::getLatencyTime](Game#getLatencyTime.md), [Game::getLatencyFrames](Game#getLatencyFrames.md), [Game::getRemainingLatencyTime](Game#getRemainingLatencyTime.md)_

## getRemainingLatencyTime ##
```

int getRemainingLatencyTime();```
Returns the remaining time in milliseconds before a unit command sent in the current frame can be processed.

> _See also: [Game::getLatencyTime](Game#getLatencyTime.md), [Game::getLatencyFrames](Game#getLatencyFrames.md), [Game::getRemainingLatencyFrames](Game#getRemainingLatencyFrames.md)_

## elapsedTime ##
```

int elapsedTime() const;```
Returns the time in game seconds that the game has been running for. This is equivalent to the staredit trigger condition `ELAPSED TIME`. A game second is not the same as a real second. It is an approximation relative to normal game speed.

> _See also: [Game::getFrameCount](Game#getFrameCount.md)_

## getFrameCount ##
```

int getFrameCount();```
Returns the number of logical frames since the match started. If the game is paused, Game::getFrameCount will not increase however AIModule::onFrame will still be called while paused. On Fastest game speed, one frame is equal to 42 milliseconds.

> _See also: [Game::getReplayFrameCount](Game#getReplayFrameCount.md)_

## getReplayFrameCount ##
```

int getReplayFrameCount();```
Returns the maximum number of frames for a replay. To get the replay progress as a percentage, you can use `getFrameCount()*100/getReplayFrameCount()`.

> _See also: [Game::getFrameCount](Game#getFrameCount.md)_

## getAPM ##
```

double getAPM(bool includeSelects = false);```
Returns the bot's running APM. This function ignores all user actions and uses the same formula as [APMAlert](http://wiki.teamliquid.net/starcraft/APMAlert).

## getFPS ##
```

int getFPS();```
Returns the number of frames per second that the game is running at, based on the number of frames that have passed in the last second.

> _See also: [Game::getAverageFPS](Game#getAverageFPS.md)_

## getAverageFPS ##
```

int getAverageFPS();```
Returns the average number of frames per second that the game is running at.

> _See also: [Game::getFPS](Game#getFPS.md)_

## getLastEventTime ##
```

int getLastEventTime() const;```
Returns the time in milliseconds that the loaded AI module spent processing its last event. This is used by the tournament module to identify how long the loaded module spent processing an event. Calling this in a callback will retrieve the time that the process has spent in the same callback of the AI module. For example: calling this in onUnitDestroy retrieves the time spent in the AI's onUnitDestroy.

## getRevision ##
```

int getRevision();```
Retrieves the revision number for the current BWAPI build.

> _See also: [Game::isDebug](Game#isDebug.md)_

## getInstanceNumber ##
```

int getInstanceNumber();```
Retrieves the number for the current instance of Starcraft/BWAPI. Used to identify which instance an AI module belongs to.

## getMousePosition ##
```

[Misc#Position Position] getMousePosition();```
Returns the position of the mouse on the screen. Returns Positions::Unknown if Flag::UserInput is disabled.

## getMouseState ##
```

bool getMouseState([Input#MouseButton MouseButton] button);
bool getMouseState(int button);```
Returns true if the specified mouse button is pressed. Returns false if Flag::UserInput is disabled.

## getKeyState ##
```

bool getKeyState([Input#Key Key] key);
bool getKeyState(int key);```
Returns true if the specified key is pressed. Returns false if Flag::UserInput is disabled. Unfortunately this does not read the raw keyboard input yet - when you hold down a key, the getKeyState function is true for a frame, then false for a few frames, and then alternates between true and false (as if you were holding down the key in a text box). Hopefully this will be fixed in a later version.

## getScreenPosition ##
```

[Misc#Position Position] getScreenPosition();```
Returns the position of the top left corner of the screen on the map. Returns Positions::Unknown if Flag::UserInput is disabled.

> _See also: [Game::setScreenPosition](Game#setScreenPosition.md)_

## setScreenPosition ##
```

void setScreenPosition(int x, int y);
void setScreenPosition([Misc#Position Position] p);```
Moves the screen to the given position on the map. The position specified where the top left corner of the screen will be.

> _See also: [Game::getScreenPosition](Game#getScreenPosition.md)_

## pingMinimap ##
```

void pingMinimap(int x, int y);
void pingMinimap([Misc#Position Position] p);```
Pings the given position on the minimap.

## isFlagEnabled ##
```

bool isFlagEnabled([Misc#Flag::Enum Flag::Enum] flag);```
Returns true if the given flag has been enabled. Note that flags can only be enabled at the beginning of a match, during the [AIModule](AIModule.md)::onStart callback.

> _See also: [Game::enableFlag](Game#enableFlag.md)_

## enableFlag ##
```

void enableFlag([Misc#Flag::Enum Flag::Enum] flag);```
Enables the specified flag. Note that flags can only be enabled at the beginning of a match, during the [AIModule::onStart](AIModule#onStart.md) callback, or during the [AIModule::onFrame](AIModule#onFrame.md) callback on the first frame (frame 0).

> _See also: [Game::isFlagEnabled](Game#isFlagEnabled.md)_

## setGUI ##
```

void setGUI(bool enabled);```
Disables all drawing functions in BWAPI and uses [Game::setFrameSkip](Game#setFrameSkip.md), specifying the highest frame skip value possible. This prevents the game from leaving its main loop. The game only draws to the screen once it has broken out of its main loop. Note that the game will still leave the loop once every 2 seconds. This alternative approach produces better results than the old setGUI behaviour.

Note: You must call [Game::setLocalSpeed(0)](#setLocalSpeed.md) to first increase the game speed to its limits in order to witness any results.

What's the difference between this and setFrameSkip(999999)? When setGUI is set to false, it will disable all of BWAPI's drawing functionality. If you've made drawing calls then they will be ignored. It also ignores drawing-related code that is used internally in BWAPI's onFrame.

> _See also: [Game::setFrameSkip](Game#setFrameSkip.md), [Game::setLocalSpeed](Game#setLocalSpeed.md)_

## isLatComEnabled ##
```

bool isLatComEnabled();```
Returns true if latency compensation is enabled. It is enabled by default.

## setLatCom ##
```

void setLatCom(bool isEnabled);```
Use to enable or disable latency compensation. It is enabled by default.

## setCommandOptimizationLevel ##
```

void setCommandOptimizationLevel(int level = 2);```
Use to set the command optimization level. This feature reduces APM and the replay size by grouping units performing the same actions.
  * 0: No optimization. (Default)
  * 1: Optimize Attack\_Unit, Morph (units only), Hold\_Position, Stop, Follow, Gather, Return\_Cargo, Repair, Burrow, Unburrow, Cloak, Decloak, Siege, Unsiege, Right\_Click\_Unit, Halt\_Construction, Cancel\_Train (Carrier/Reaver only), Cancel\_Train\_Slot (Carrier/Reaver only), Cancel\_Morph(units only), Use\_Tech, and Use\_Tech\_Unit. Additionally perform the following transformations:
    * Attack\_Unit becomes Right\_Click\_Unit if the target is an enemy.
    * Move becomes Right\_Click\_Position.
    * Gather becomes Right\_Click\_Unit if the target contains resources.
    * Set\_Rally\_Position becomes Right\_Click\_Position for buildings.
    * Set\_Rally\_Unit becomes Right\_Click\_Unit for buildings.
    * Use\_Tech\_Unit for a Zerg Queen using Infestation becomes Right\_Click\_Unit when the target is a Command Center.
  * 2: Optimize all of the above, as well as Attack\_Unit(towers), Train (buildings), Morph (buildings), Set\_Rally\_Unit, Lift, Unload\_All (Bunkers only), Cancel\_Construction, Cancel\_Addon, Cancel\_Train, Cancel\_Train\_Slot, Cancel\_Morph, Cancel\_Research, and Cancel\_Upgrade. This level will flag BWAPI's commands as hacks in a replay analyzer.
  * 3: Optimize all of the above, as well as Attack\_Move, Set\_Rally\_Position, Move, Patrol, Unload\_All\_Position, Right\_Click\_Position, and Use\_Tech\_Position. These optimizations may yield a different movement behaviour than without.
  * 4: Optimize all of the above, but trim positions to be a multiple of 32 so that it may group positions that are near each other. This creates less accurate move positions. In addition, group Templars when they are ordered to merge with another Templar (includes both High and Dark).

## getUnitsOnTile ##
```

std::set< [Unit]* >& getUnitsOnTile(int tileX, int tileY);```
Returns the set of units that are on the given build tile. Only returns accessible units on accessible tiles.

## getUnitsInRectangle ##
```

std::set<[Unit]*>& getUnitsInRectangle(int left, int top, int right, int bottom) const;
std::set<[Unit]*>& getUnitsInRectangle([Misc#Position Position] topLeft, [Misc#Position Position] bottomRight) const;```
Retrieves the set of all accessable units within a rectangle.

> _See also: [Game::getUnitsInRadius](Game#getUnitsInRadius.md)_

## getUnitsInRadius ##
```

std::set<[Unit]*>& getUnitsInRadius([Misc#Position Position] center, int radius) const;```
Retrieves the set of all accessable units within a given radius.

> _See also: [Unit::getUnitsInRectangle](Unit#getUnitsInRectangle.md)_

## getLastError ##
```

[Error] getLastError() const;```
Returns the last error that was set. If you try to order enemy units around, or morph bunkers into lurkers, BWAPI will set error codes, which can be retrieved using this function.

> _See also: [Game::setLastError](Game#setLastError.md)_

## setLastError ##
```

bool setLastError([Error] e);```
Sets the last error for BWAPI. For the sake of minimizing code, it will return true when the error is Errors::None and false otherwise.

> _See also: [Game::getLastError](Game#getLastError.md)_

## mapWidth ##
```

int mapWidth();```
Returns the width of the current map, in build tile units. To get the width of the current map in walk tile units, multiply by 4. To get the width of the current map in [Position](Misc#Position.md) units, multiply by [TILE\_SIZE](Misc#Constants.md) (which is 32).

> _See also: [Game::mapHeight](Game#mapHeight.md)_

## mapHeight ##
```

int mapHeight();```
Returns the height of the current map, in build tile units. To get the height of the current map in walk tile units, multiply by 4. To get the height of the current map in [Position](Misc#Position.md) units, multiply by [TILE\_SIZE](Misc#Constants.md) (which is 32).

> _See also: [Game::mapWidth](Game#mapWidth.md)_

## mapFileName ##
```

std::string mapFileName();```
Returns the file name of the current map.

> _See also: [Game::mapPathName](Game#mapPathName.md), [Game::mapName](Game#mapName.md)_

## mapPathName ##
```

std::string mapFileName();```
Returns the path name of the current map (path + file name).

> _See also: [Game::mapFileName](Game#mapFileName.md), [Game::mapName](Game#mapName.md)_

## mapName ##
```

std::string mapName();```
Returns the name/title of the current map.

> _See also: [Game::mapPathName](Game#mapPathName.md), [Game::mapFileName](Game#mapFileName.md)_

## mapHash ##
```

std::string mapHash();```
Returns the sha1 hash of the map file in an alpha-numeric string.

## isWalkable ##
```

bool isWalkable(int walkX, int walkY);```
Returns true if the specified walk tile is walkable. The values of x and y are in walk tile coordinates (different from build tile coordinates). Note that this just uses the static map data. You will also need to make sure no ground units are on the coresponding build tile to see if its currently walkable. To do this, see [getUnitsOnTile](#getUnitsOnTile.md).

Keep in mind that a "walk tile" is a 8x8 pixel tile, and 16 walk tiles make up a build tile.

> _See also: [Game::isBuildable](Game#isBuildable.md)_

## getGroundHeight ##
```

int getGroundHeight(int tileX, int tileY);
int getGroundHeight([Misc#TilePosition TilePosition] position);```
Returns the ground height of the given build tile.
```
0 = low
1 = low doodads
2 = high
3 = high doodads
4 = very high
5 = very high doodads
```

For information about attacking a unit from a lower to higher ground, see the [Chance to Hit Guide](http://code.google.com/p/bwapi/wiki/StarcraftGuide#Chance_to_Hit_Guide).

## isBuildable ##
```

bool isBuildable(int tileX, int tileY, bool includeBuildings = false);
bool isBuildable([Misc#TilePosition TilePosition] position, bool includeBuildings = false);```
Returns true if the specified build tile is buildable. Note that this just uses the static map data. You will also need to make sure no ground units on the tile to see if its currently buildable. To do this, see [getUnitsOnTile](#getUnitsOnTile.md).

This function was updated later to include a boolean that includes all visible buildings. By default it is set to false to maintain the original function's behaviour.

> _See also: [Game::isWalkable](Game#isWalkable.md), [Game::canBuildHere](Game#canBuildHere.md)_

## isVisible ##
```

bool isVisible(int tileX, int tileY);
bool isVisible([Misc#TilePosition TilePosition] position);```
Returns true if the specified build tile is visible. If the tile is concealed by fog of war, the function will return false.

> _See also: [Game::isExplored](Game#isExplored.md)_

## isExplored ##
```

bool isExplored(int tileX, int tileY);
bool isExplored([Misc#TilePosition TilePosition] position);```
Returns true if the specified build tile has been explored (i.e. was visible at some point in the match).

> _See also: [Game::isVisible](Game#isVisible.md)_

## hasCreep ##
```

bool hasCreep(int tileX, int tileY);
bool hasCreep([Misc#TilePosition TilePosition] position);```
Returns true if the specified build tile has zerg creep on it. If the tile is concealed by fog of war, the function will return false.

> _See also: [Game::hasPower](Game#hasPower.md)_

## hasPower ##
```

bool hasPower(int tileX, int tileY, UnitType unitType = UnitTypes::None) const;
bool hasPower([Misc#TilePosition TilePosition], UnitType unitType = UnitTypes::None) const;
bool hasPower(int tileX, int tileY, int tileWidth, int tileHeight, UnitType unitType = UnitTypes::None) const;
bool hasPower([Misc#TilePosition TilePosition] position, int tileWidth, int tileHeight, UnitType unitType = UnitTypes::None) const;```
Returns true if the given build location is powered by a nearby friendly pylon. If the unitType is specified, it will include the unit's properties in the calculation, so if the type does not require a pylon, it will return true for anywhere. Using the constructors that only take a tile position and unit type, it will use the unit type's width and height for calculation.

> _See also: [Game::hasCreep](Game#hasCreep.md), [Game::hasPowerPrecise](Game#hasPowerPrecise.md)_

## hasPowerPrecise ##
```

bool hasPowerPrecise(int x, int y, UnitType unitType = UnitTypes::None ) const;
bool hasPowerPrecise([Misc#Position Position] position, UnitType unitType = UnitTypes::None) const;```
Returns true if the given pixel coordinate is powered by a nearby friendly pylon. If the unitType is specified, it will include the unit's properties in the calculation, so if the type does not require a pylon, it will return true for anywhere. The power calculation does not consider the width and height of the unit, as it's not required.

> _See also: [Game::hasPower](Game#hasPower.md)_

## hasPath ##
```

bool hasPath([Misc#Position Position] source, [Misc#Position Position] destination) const;```
Returns true if the source position is in the same body of land as the destination position, and false otherwise. In other words, it returns true if a unit at the source position is able to walk all the way to the destination position. This does not include buildings and units blocking the path. It only looks at static map data.

> _See also: [Unit::hasPath](Unit#hasPath.md)_

## canBuildHere ##
```

bool canBuildHere([Unit]* builder, [Misc#TilePosition TilePosition] position, [UnitType] type, bool checkExplored = false);```
Returns true if the given unit type can be built at the given build tile position. Note the tile position specifies the top left tile of the building. If builder is not `NULL`, the unit will be discarded when determining whether or not any ground units are blocking the build location. If checkExplored is specified, then canBuildHere will also verify that the area has been explored first.

## canMake ##
```

bool canMake([Unit]* builder, [UnitType] type);```
Returns true if the AI player has enough resources, supply, tech, and required units in order to make the given unit type. If builder is not `NULL`, canMake will return true only if the builder unit can build the given unit type.

> _See also: [Game::canBuildHere](Game#canBuildHere.md)_

## canResearch ##
```

bool canResearch([Unit]* unit, [TechType] type);```
Returns true if the AI player has enough resources required to research the given tech type. If unit is not `NULL`, canResearch will return true only if the given unit can research the given tech type.

> _See also: [Game::canUpgrade](Game#canUpgrade.md)_

## canUpgrade ##
```

bool canUpgrade([Unit]* unit, [UpgradeType] type);```
Returns true if the AI player has enough resources required to upgrade the given upgrade type. If unit is not `NULL`, canUpgrade will return true only if the given unit can upgrade the given upgrade type.

> _See also: [Game::canResearch](Game#canResearch.md)_

## getStartLocations ##
```

std::set< [Misc#TilePosition TilePosition] >& getStartLocations();```
Returns the set of starting locations for the given map. To determine the starting location for the players in the current match, see [Player](Player.md)::[getStartLocation](Player#getStartLocation.md).

## printf ##
```

void printf(const char *format, ...);```
Prints text on the screen. Text is not sent to other players in multiplayer games.

> _See also: [Game::sendText](Game#sendText.md), [Game::drawText](Game#drawText.md)_

## sendText ##
```

void sendText(const char *format, ...);
void sendTextEx(bool toAllies, const char *format, ...);```
Sends text to other players - as if it were entered in chat. In single player games and replays, this will just print the text on the screen. If the game is a single player match and not a replay, then this function can be used to execute cheat codes, i.e. Broodwar->sendText("show me the money").

> _See also: [Game::printf](Game#printf.md), [Game::drawText](Game#drawText.md)_

## changeRace ##
```

void changeRace([Race] race);```
Used to change the race while in a lobby. Note that there is no onLobbyEnter callback yet, so this function cannot be used at this time.

## isInGame ##
```

bool isInGame();```
Returns true if Broodwar is in a match (single player match, replay, or multiplayer match). Returns false if the Broodwar is in a menu screen.

## isMultiplayer ##
```

bool isMultiplayer();```
Returns true if Broodwar is in a multiplayer game. Returns false for single player games and replays.

> _See also: [Game::isBattleNet](Game#isBattleNet.md), [Game::isReplay](Game#isReplay.md)_

## isBattleNet ##
```

bool isBattleNet();```
Returns true if Broodwar is in an online game on BattleNet or similar server (like ICCup).

> _See also: [Game::isMultiPlayer](Game#isMultiplayer.md), [Game::isReplay](Game#isReplay.md)_

## isPaused ##
```

bool isPaused();```
Returns true if Broodwar is paused. If the game is paused, Game::getFrameCount will not increase however AIModule::onFrame will still be called while paused.

## isReplay ##
```

bool isReplay();```
Returns true if Broodwar is in a replay.

> _See also: [Game::isMultiPlayer](Game#isMultiplayer.md), [Game::isBattleNet](Game#isBattleNet.md)_

## isDebug ##
```

bool isDebug();```
Returns true if the current build is DEBUG, and false if the current build is RELEASE.

> _See also: [Game::getRevision](Game#getRevision.md)_

## startGame ##
```

void startGame();```
Used to start the game while in a lobby. Note that there is no onLobbyEnter callback yet, so this function cannot be used at this time.

## pauseGame ##
```

void pauseGame();```
Pauses the game. If the game is paused, Game::getFrameCount will not increase however AIModule::onFrame will still be called while paused.

> _See also: [Game::resumeGame](Game#resumeGame.md)_

## resumeGame ##
```

void resumeGame();```
Resumes the game.

> _See also: [Game::pauseGame](Game#pauseGame.md)_

## leaveGame ##
```

void leaveGame();```
Leaves the current match and goes to the after-game stats screen.

## setMap ##
```

bool setMap(const char *mapFileName);```
Changes the map file to the one specified. Changes will take effect when the game is [restarted](Game#restartGame.md). Returns true if successful. If this function fails, it returns false and sets the last error to [Errors::Invalid\_Parameter](Error#Invalid_Parameter.md) or [Errors::File\_Not\_Found](Error#File_Not_Found.md).

## restartGame ##
```

void restartGame();```
Restarts the match. Works the same way as if you restarted the match from the menu screen. Only available in single player mode.

## setAlliance ##
```

bool setAlliance([Player] *player, bool allied = true, bool alliedVictory = true);```
Sets the BWAPI player's alliance with the specified player, whether they're allied and allied victory is set. The alliedVictory field is ignored if allied is set to false.

> _See also: [Game::setVision](Game#setVision.md)_

## setVision ##
```

bool setVision([Player] *player, bool enabled = true);```
Sets the BWAPI player's vision with the specified player. Commonly used when setting another player to ally or enemy. Returns false if the function failed.

> _See also: [Game::setAlliance](Game#setAlliance.md)_

## setReplayVision ##
```

bool setReplayVision([Player] *player, bool enabled = true);```
Sets the visibility of a player when watching a replay. Returns false if the function failed, specifically if it is not a replay.

> _See also: [Game::setVision](Game#setVision.md)_

## setRevealAll ##
```

bool setRevealAll(bool reveal = true);```
Toggles the fog of war when watching a replay. Returns false if the game is not a replay.

## setLocalSpeed ##
```

void setLocalSpeed(int speed = -1);```
Sets the speed of the game to the given number. Lower numbers are faster. 0 is the fastest speed Starcraft can handle (which is about as fast as the fastest speed you can view a replay at). Any negative value will reset the speed to the starcraft default.

> _See also: [Game::setGUI](Game#setGUI.md), [Game::setFrameSkip](Game#setFrameSkip.md)_


## setFrameSkip ##
```

void setFrameSkip(int frameSkip = 1);```
Alters Starcraft's built-in frame skipping. This value is normally only changed during replays on 16x speed. The default value is 1.

> _See also: [Game::setGUI](Game#setGUI.md), [Game::setLocalSpeed](Game#setLocalSpeed.md)_

## issueCommand ##
```

bool issueCommand(const std::set<[Unit]*>& units, [UnitCommand] command);```
Issues a command to a set of units. Returns true if at least one unit was able to execute the command. This will select the units specified in groups of 12 and order them all at once without wasting additional commands.

## getSelectedUnits ##
```

std::set<[Unit]*>& getSelectedUnits();```
Returns the set of units currently selected by the user in the GUI. If [Flag](Flag.md)::UserInput was not enabled during the [AIModule](AIModule.md)::[onStart](AIModule#onStart.md) callback, this function will always return an empty set.

## self ##
```

[Player]* self();```
Returns a pointer to the player that BWAPI controls. In replays this will return `NULL`.

> _See also: [Game::allies](Game#allies.md), [Game::enemies](Game#enemies.md), [Game::enemy](Game#enemy.md), [Game::neutral](Game#neutral.md)_

## enemy ##
```

[Player]* enemy();```
Returns a pointer to the enemy player. If there is more than one enemy, use [enemies()](#enemies.md) to get the set of all enemy players that have not left or been defeated. In replays this will return `NULL`.

> _See also: [Game::allies](Game#allies.md), [Game::enemies](Game#enemies.md), [Game::neutral](Game#neutral.md), [Game::self](Game#self.md)_

## neutral ##
```

[Player]* neutral();```
Returns a pointer to the neutral player.

> _See also: [Game::allies](Game#allies.md), [Game::enemies](Game#enemies.md), [Game::enemy](Game#enemy.md), [Game::self](Game#self.md)_

## allies ##
```

std::set<[Player]*>& allies();```
Returns a reference to the set of ally players that have not left or been defeated.

> _See also: [Game::enemies](Game#enemies.md), [Game::enemy](Game#enemy.md), [Game::neutral](Game#neutral.md), [Game::self](Game#self.md)_

## enemies ##
```

std::set<[Player]*>& enemies();```
Returns a reference to the set of enemy players that have not left or been defeated.

> _See also: [Game::allies](Game#allies.md), [Game::enemy](Game#enemy.md), [Game::neutral](Game#neutral.md), [Game::self](Game#self.md)_

## observers ##
```

std::set<[Player]*>& observers();```
Returns a reference to the set of observer players that have not left the game.

> _See also: [Game::allies](Game#allies.md), [Game::enemies](Game#enemies.md)_

## setTextSize ##
```

void setTextSize(int size);```
Sets the size at which text using [drawText](#drawText.md) will be drawn at. The values are as follows:
```
0 = Smallest
1 = Small (default)
2 = Large
3 = Largest
```

> _See also: [Game::drawText](Game#drawText.md)_

## drawText ##
```

void drawText(CoordinateType::Enum ctype, int x, int y, const char *format, ...);
void drawTextMap(int x, int y, const char *format, ...);
void drawTextMouse(int x, int y, const char *format, ...);
void drawTextScreen(int x, int y, const char *format, ...);```
Draws text on the screen at the given position. Text can be drawn in different colors by using the following control characters:

![http://bwapi.googlecode.com/svn/wiki/pDizc.png](http://bwapi.googlecode.com/svn/wiki/pDizc.png)

> _See also: [Game::setTextSize](Game#setTextSize.md), [Game::sendText](Game#sendText.md), [Game::printf](Game#printf.md)_

## drawBox ##
```

void drawBox(CoordinateType::Enum ctype, int left, int top, int right, int bottom, Color color = Color(Colors::Green), bool isSolid = false);
void drawBoxMap(int left, int top, int right, int bottom, Color color = Color(Colors::Green), bool isSolid = false);
void drawBoxMouse(int left, int top, int right, int bottom, Color color = Color(Colors::Green), bool isSolid = false);
void drawBoxScreen(int left, int top, int right, int bottom, Color color = Color(Colors::Green), bool isSolid = false);```
Draws a box on the screen, with the given color. If isSolid is true, the entire box will be rendered, otherwise just the outline will be drawn.

> _See also: [Game::drawTriangle](Game#drawTriangle.md), [Game::drawLine](Game#drawLine.md), [Game::drawDot](Game#drawDot.md), [Game::drawEllipse](Game#drawEllipse.md), [Game::drawCircle](Game#drawCircle.md)_

## drawCircle ##
```

void drawCircle(CoordinateType::Enum ctype, int x, int y, int radius, Color color = Color(Colors::Green), bool isSolid = false);
void drawCircleMap(int x, int y, int radius, Color color = Color(Colors::Green), bool isSolid = false);
void drawCircleMouse(int x, int y, int radius, Color color = Color(Colors::Green), bool isSolid = false);
void drawCircleScreen(int x, int y, int radius, Color color = Color(Colors::Green), bool isSolid = false);```
Draws a circle on the screen, with the given color. If isSolid is true, a solid circle is drawn, otherwise just the outline of a circle will be drawn.

> _See also: [Game::drawTriangle](Game#drawTriangle.md), [Game::drawLine](Game#drawLine.md), [Game::drawDot](Game#drawDot.md), [Game::drawEllipse](Game#drawEllipse.md), [Game::drawBox](Game#drawBox.md)_

## drawEllipse ##
```

void drawEllipse(CoordinateType::Enum ctype, int x, int y, int xrad, int yrad, Color color = Color(Colors::Green), bool isSolid = false);
void drawEllipseMap(int x, int y, int xrad, int yrad, Color color = Color(Colors::Green), bool isSolid = false);
void drawEllipseMouse(int x, int y, int xrad, int yrad, Color color = Color(Colors::Green), bool isSolid = false);
void drawEllipseScreen(int x, int y, int xrad, int yrad, Color color = Color(Colors::Green), bool isSolid = false);```
Draws an ellipse on the screen, with the given color. If isSolid is true, a solid ellipse is drawn, otherwise just the outline of an ellipse will be drawn.

> _See also: [Game::drawTriangle](Game#drawTriangle.md), [Game::drawLine](Game#drawLine.md), [Game::drawDot](Game#drawDot.md), [Game::drawCircle](Game#drawCircle.md), [Game::drawBox](Game#drawBox.md)_

## drawDot ##
```

void drawDot(CoordinateType::Enum ctype, int x, int y, Color color = Color(Colors::Green));
void drawDotMap(int x, int y, Color color = Color(Colors::Green));
void drawDotMouse(int x, int y, Color color = Color(Colors::Green));
void drawDotScreen(int x, int y, Color color = Color(Colors::Green));```
Draws a dot on the screen at the given position with the given color.

> _See also: [Game::drawTriangle](Game#drawTriangle.md), [Game::drawLine](Game#drawLine.md), [Game::drawEllipse](Game#drawEllipse.md), [Game::drawCircle](Game#drawCircle.md), [Game::drawBox](Game#drawBox.md)_

## drawLine ##
```

void drawLine(CoordinateType::Enum ctype, int x1, int y1, int x2, int y2, Color color = Color(Colors::Green));
void drawLineMap(int x1, int y1, int x2, int y2, Color color = Color(Colors::Green));
void drawLineMouse(int x1, int y1, int x2, int y2, Color color = Color(Colors::Green));
void drawLineScreen(int x1, int y1, int x2, int y2, Color color = Color(Colors::Green));```
Draws a line on the screen from (x1,y1) to (x2,y2) with the given color.

> _See also: [Game::drawTriangle](Game#drawTriangle.md), [Game::drawDot](Game#drawDot.md), [Game::drawEllipse](Game#drawEllipse.md), [Game::drawCircle](Game#drawCircle.md), [Game::drawBox](Game#drawBox.md)_

## drawTriangle ##
```

void drawTriangle(CoordinateType::Enum ctype, int ax, int ay, int bx, int by, int cx, int cy, Color color = Color(Colors::Green), bool isSolid = false);
void drawTriangleMap(int ax, int ay, int bx, int by, int cx, int cy, Color color = Color(Colors::Green), bool isSolid = false);
void drawTriangleMouse(int ax, int ay, int bx, int by, int cx, int cy, Color color = Color(Colors::Green), bool isSolid = false);
void drawTriangleScreen(int ax, int ay, int bx, int by, int cx, int cy, Color color = Color(Colors::Green), bool isSolid = false);```
Draws a triangle on the screen. If isSolid is true, a solid triangle is drawn, otherwise just the outline of the triangle will be drawn.

> _See also: [Game::drawLine](Game#drawLine.md), [Game::drawDot](Game#drawDot.md), [Game::drawEllipse](Game#drawEllipse.md), [Game::drawCircle](Game#drawCircle.md), [Game::drawBox](Game#drawBox.md)_