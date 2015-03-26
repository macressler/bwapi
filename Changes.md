## Changes from BWAPI 4.0.0 Beta ([r4350](https://code.google.com/p/bwapi/source/detail?r=4350)) to BWAPI 4.0.1 Beta ([r4453](https://code.google.com/p/bwapi/source/detail?r=4453)) ##
Changes:
  * All interface pointers are now hidden. Instead of `Unit*` you will now just use `Unit`. This will require a "Replace in Files" operation to convert existing sources.
  * The installer now prompts the user to locate the Starcraft installation directory if it is not found.
  * Game::setTextSize now takes a BWAPI::Text::Size::Enum parameter instead of an integer.
  * All instances of IsUnpowered were renamed to IsPowered.
  * The AI module in the configuration now accepts absolute paths (Ex: C:/stuff).

Bug Fixes:
  * Fixed a regression that prevented auto-menu from functioning.
  * Fixed an issue that caused Type::getType to be case sensitive.
  * Fixed a regression where addons and the engineering bay returned incorrect tile sizes.
  * Fixed a regression that prevented the construction of structures on the right and bottom edges of the map.
  * Fixed a regression that prevented the example projects from building out-of-the-box.
  * Fixed a bug where auto\_menu caused a second multi-instance client to redownload a map that already existed.
  * Fixed a bug where auto\_menu attempted to start a game before map downloads could be processed.
  * Fixed a regression that prevented the client/server setup from communicating.


## Changes from BWAPI 3.7.4 ([r4160](https://code.google.com/p/bwapi/source/detail?r=4160)) to BWAPI 4.0.0 Beta ([r4350](https://code.google.com/p/bwapi/source/detail?r=4350)) ##
  * All BWAPI projects have been upgraded to use Microsoft Visual C++ 2010 Express.
  * BWAPI now uses the available C++11 features, such as move semantics, std::function, lambdas, and nullptr.
  * The location of BWAPI.dll has been moved to the bwapi-data folder.
  * Several performance improvements have been made for BWAPI.
  * The save\_replay configuration option has been altered for more flexibility on date/time stamps.
  * The documentation has been extensively reworked and is now included as offline HTML files. Not all documentation has been updated but will continue to be worked on.
  * A proper installer is now distributed for BWAPI.

## Necessary Regressions ##
  * BWAPI no longer supports loading older revisions of itself.
  * The holiday lights have been removed.
  * BWTA is no longer compatible with BWAPI.

### AI/Tournament Module ###
  * Type data is no longer initialized by the module, and can now be retrieved properly at any time.
  * The gameInit function is now exported to initialize the Broodwar pointer.
  * The original newAIModule function now takes 0 arguments.
  * Removed the Tournament enum restartGame.

### Sets and Vectors ###
> Using a custom new class template known as a Vectorset, BWAPI and AI modules can perform significantly better (faster and less memory). This replaces the use of STL containers, but is used the same way (with Vectorset::iterator, stl algorithms, etc).

> It can be treated like a vector or a set, and the user has the option of treating it as a vector for some cases and a set for others.

> Additional convenience members have been added, such as .rand(), which returns the value of a random element of the set.

### Positions ###
  * Position, TilePosition, and the new WalkPosition now all share the same class template: Point. This maintains consistency between member functions to be used by any Position type, and provides conversions between each type, including custom ones.
  * Positions now have several operators that make arithmetic easier. For example, Position(8,8)/2 will give Position(4,4) and Position(30,20) - Position(15,5) will give Position(15,15).
  * There is also Position::set, derived from the Vectorset that will handle sets of Positions.
  * The x and y members are now public, and the x() and y() member functions have been removed.
  * Added the constants Positions::Origin, TilePositions::Origin, etc. which represent (0,0).

### Interface ###
  * Each interface class will have its own derived set with several enhancements, and brings in some functionality similar to that of BWSAL. The new sets are as follows: Unitset, Playerset, Regionset, Bulletset, Forceset
  * Interface overhead has been reduced by making some member functions with alternative parameters non-virtual. Keep in mind some function parameters have been re-arranged so that default parameters can be used.
  * getClientInfo/setClientInfo are now available to all Interface classes, and also take an optional parameter that acts as a key.
  * User-defined events have been added, and can be utilized through registerEvent.

### Types ###
  * Types have also received their own set, the Type::set (Example: UnitType::set).
  * The behavior of type creation has been changed, and now all types with an id between 0 and Unknown will be considered valid, even if data for the type has not been defined in BWAPI. This drastically simplifies the type's constructors.
  * Most type data is now made constant and no longer requires an initialization to be made. This gives users more flexibility for when they want to access type information.
  * Added a Type::isValid function.
  * All types' enumerations are now available (for switch case usage) and are accessed by Types::Enum (Example: `UnitTypes::Enum::Terran_Marine`).
  * TechType::energyUsed has been renamed to energyCost.
  * All types now overload std::ostream operator<< (including Color).
  * UnitTypes::getUnit, Races::getRace, etc. have now been replaced with static Type::getType. (Example: Races::getRace doesn't exist, use Race::getType)
  * Added UnitType::width, UnitType::height, and UnitType::isCritter.

### Game ###
  * Draw functions now take Position parameters as an alternative to individual x and y.
  * The parameters for canBuildHere, canMake, canResearch, and canUpgrade have been rearranged.
  * `getUnits_` functions now return a Unitset copy instead of a reference, and also now takes a function predicate.
  * Added getClosestUnit, getBestUnit, getClosestUnitInRectangle, vPrintf, vSendText, vSendTextEx, vDrawText, isGUIEnabled, getBuildLocation, getDamageFrom, and getDamageTo.
  * Removed getScreenBuffer, setReplayVision(use setVision for replays too), changeRace, and startGame.
  * Instead of using Game::printf, you may use BWAPI::Broodwar like you would std::cout, using operator <<.
  * Using Special\_Start\_Location in canBuildHere will ignore units that are occupying the space while still checking for resource distance.
  * Some functions now take an Enum type instead of an int.

### Unit Filters ###
  * UnitFilter is a new powerful function composition object and function predicate for use with `getUnits_` functions throughout the interface. It can generally be combined with any other functional object (including lambdas) using operators && and `||`, as well as ! for the inverse. (Example: `!(IsFlyer || IsLifted)` )
  * CompareFilter is a sister function composition object that compares the values returned from the call to the object, and can be combined using operators ==, <, <=, >, >=, and !=. (Example: `GetType == UnitTypes::Terran_SCV && HP_Percent < 100`)
  * Filters can be found in the BWAPI::Filter namespace.

### Player ###
  * groundWeaponMaxRange and airWeaponMaxRange have been removed. Use weaponMaxRange instead.
  * getTextColor now returns a char instead of an int so that it is printed correctly when used with ostream operator <<.
  * Added damage(WeaponType)
  * Unit count functions now take a default parameter of AllUnits.
  * Rename groundWeaponDamageCooldown to weaponDamageCooldown.

### Unit ###
  * The parameters for build have been rearranged.
  * `getUnits_` functions now return a Unitset copy instead of a reference, and also now takes a function predicate.
  * Added getClosestUnit, getUnitsInRadius, getSpaceRemaining, and isTargetable.
  * Removed getUpgradeLevel.
  * Several functions for testing command validity were added.
  * Unit commands are now more strict.
  * getResources now returns the last-known resource amount when the unit becomes inaccessible.

### Region ###
  * Added a getUnits function.
  * Renamed isWalkable to isAccessible

### Bug Fixes ###
  * Fixed a bug where Unit::getRemainingBuildTime failed to work correctly for some units (such as siege tanks).
  * Fixed a bug where Spider Mines were not correctly identified for Jim Raynor (Vulture).
  * Fixed a bug where key enum values were incorrectly mapped for Game::getKeyState.
  * Fixed a bug that allowed multiple instances of the BWAPI DLL to be injected into Broodwar, which could cause compatibility issues.

## Changes from BWAPI 3.7.3 ([r4111](https://code.google.com/p/bwapi/source/detail?r=4111)) to BWAPI 3.7.4 ([r4160](https://code.google.com/p/bwapi/source/detail?r=4160)) ##

Changes/Additions:
  * The Random race feature has been corrected and re-enabled. Players who chose Random will have their race displayed as Unknown until they are scouted.
  * MPQDraft and Chaoslauncher with its plugins are now included in the release.
  * The exception filter now writes to Starcraft/Errors/.
  * An Install script is now included. Simply run Install.exe to automatically copy the folders to their desired locations.

Bug Fixes:
  * Fixed a regression that involved save\_replay not working correctly.
  * Fixed a bug where `getUnitsIn_` functions were unable to properly retrieve unit data on the edge of the map.
  * Fixed several minor buffer overflows.
  * Fixed a bug that caused some replays to save with 0 frame time (causing a division by 0 exception on loading).
  * Fixed a bug that prevented auto-menu "join game by name" from functioning.


## Changes from BWAPI 3.7.2 ([r4025](https://code.google.com/p/bwapi/source/detail?r=4025)) to BWAPI 3.7.3 ([r4111](https://code.google.com/p/bwapi/source/detail?r=4111)) ##

Bug Fixes:
  * Fixed a bug where UnitTypes::maxUnitHeight was returning the max unit width instead.
  * Fixed a regression where getUnitsIn functions did not function for non-client AI.
  * Fixed the client's Game::getForces which included the null force.
  * Fixed a client bug where Force::getName could return an invalid string.
  * Fixed an auto\_menu bug which prevented Zerg from being selected as a race.
  * Fixed a bug where BWAPI's version checking was too strict.
  * Fixed a bug that allowed bots to tell if an opponent had constructed a structure in the fog of war using Game::canBuildHere and Game::isBuildable.
  * Fixed a bug where drawText with a string over 255 characters could cause an overflow.
  * Fixed a bug involving some uninitialized game data causing an inconsistency during the first game.
  * Fixed an issue where shared memory would require high level permissions such as administrator. The permission requirement should now be reduced.


## Changes from BWAPI 3.7.1 ([r4000](https://code.google.com/p/bwapi/source/detail?r=4000)) to BWAPI 3.7.2 ([r4025](https://code.google.com/p/bwapi/source/detail?r=4025)) ##

Changes:
  * The exception filter now informs of NULL Broodwar pointers when the game crashes, making it more informative.
  * The exception filter now destroys the direct draw window (if the game crashes in full screen) to make debugging easier.
  * BWAPI will drop players from the game when the countdown timer reaches 0.
  * **The random race implementation was disabled because it was not working correctly.**

Additions:
  * Added an onPlayerDropped event which is currently only called for the tournament module.

Bug Fixes:
  * Fixed a bug that caused a crash in a map where extended players were being used.
  * Fixed an issue where BWAPI would allocate a huge amount of unused shared memory.


## Changes from BWAPI 3.7 ([r3969](https://code.google.com/p/bwapi/source/detail?r=3969)) to BWAPI 3.7.1 ([r4000](https://code.google.com/p/bwapi/source/detail?r=4000)) ##

Changes:
  * Complete map information is now available when the game ends, so that bots may view post-game information.
  * The single unload unit command now optimizes a select only when the command optimizer level is at least level 2 (prevents mistakes generated by replay analyzers).
  * If the game is minimized in single player with windowed mode enabled, it will now automatically increase the speed of the gameplay.
  * Windowed mode now uses less CPU.
  * BWAPI will now hide the race of players that chose Random until one of their units have been spotted.

Bug Fixes:
  * Fixed a bug that caused saving replays to fail, when attempting to save them manually.
  * Fixed a regression that caused the Command Optimizer to go into an infinite loop.
  * Fixed an issue where [Player::getForce](Player#getForce.md) would return NULL when a player was not in a force (specifically in melee).
  * Fixed a bug where non-existent client bullets were not handled properly.


## Changes from BWAPI 3.6.1 ([r3769](https://code.google.com/p/bwapi/source/detail?r=3769)) to BWAPI 3.7 ([r3969](https://code.google.com/p/bwapi/source/detail?r=3969)) ##

Changes:
  * Unload, Unload\_All, and Unload\_All\_Position now return false when the location specified is unwalkable.
  * Renamed Player::cumulativeMinerals to [Player::gatheredMinerals](Player#gatheredMinerals.md).
  * Renamed Player::cumulativeGas to [Player::gatheredGas](Player#gatheredGas.md).
  * Users are now restricted from deleting interface classes.
  * The performance of BWAPI has been vastly improved in several places.
  * Multiple instances now display the instance number in the window title.
  * BWAPI Client-Server setup is now compatible with multiple instances.
  * BWAPI now contains a top level exception filter, which will log more detailed information about a crash.

Additions:
  * Added [Unit::getReplayID](Unit#getReplayID.md).
  * Added the onUnitComplete callback (UnitComplete event).
  * Added [Player::refundedMinerals](Player#refundedMinerals.md) - returns the cumulative amount of minerals refunded from canceled units, canceled upgrades, and canceled research.
  * Added [Player::refundedGas](Player#refundedGas.md) - returns the cumulative amount of gas refunded from canceled units, canceled upgrades, and canceled research.
  * Added [Player::repairedMinerals](Player#repairedMinerals.md) - returns the cumulative amount of minerals spent on repairs.
  * Added [Player::repairedGas](Player#repairedGas.md) - returns the cumulative amount of gas spent on repairs.
  * Added [Player::spentMinerals](Player#spentMinerals.md) - returns the cumulative amount of minerals spent, not including repairs.
  * Added [Player::spentGas](Player#spentGas.md) - returns the cumulative amount of gas spent, not including repairs.
  * Added [Player::isUnitAvailable](Player#isUnitAvailable.md). (for Use Map Settings)
  * Added [Player::isResearchAvailable](Player#isResearchAvailable.md). (for Use Map Settings)
  * Added [Player::getMaxUpgradeLevel](Player#getMaxUpgradeLevel.md). (for Use Map Settings)
  * Added [Game::getCountdownTimer](Game#getCountdownTimer.md). (for a few game modes)
  * Gave all types a `<type>::c_str()` member to reduce the redundancy of retrieving names (such as `type.getName().c_str()`, which can now be `type.c_str()`).
  * Added the [Region](Region.md) class with several member functions.
  * Added [Game::getRegion](Game#getRegion.md), [Game::getAllRegions](Game#getAllRegions.md), and [Game::getRegionAt](Game#getRegionAt.md).
  * Added encapsulation to [Event](Event.md).
  * Added [Game::getLastEventTime](Game#getLastEventTime.md) for tournaments.
  * Added [BulletTypes::Ensnare](BulletTypes#ensnare.md).
  * Added [Unit::getRegion](Unit#getRegion.md).
  * Added the configuration option `show_warnings` under config to disable BWAPI launch warnings.
  * Added [UnitTypes::maxUnitWidth](UnitType#maxUnitWidth.md) and [UnitTypes::maxUnitHeight](UnitType#maxUnitHeight.md).
  * Added [Unit::getLeft](Unit#getLeft.md), [Unit::getTop](Unit#getTop.md), [Unit::getRight](Unit#getRight.md), and [Unit::getBottom](Unit#getBottom.md).
  * Added [UnitType::canBuildAddon](UnitType#canBuildAddon.md).
  * Added [Game::setReplayVision](Game#setReplayVision.md) and [Game::setRevealAll](Game#setRevealAll.md).
  * There is now /record and /stoprecord [Commands](Commands.md) that perform native video recording. It is not fully supported and does not record sound.
  * BWAPI now has the ability to join a LAN game by name, specified by the `game` parameter in the configuration file, under `auto_menu`.
  * Added a new configuration option called `shared_memory` under `config`, which can disable BWAPI's Server functionality.

Bug Fixes:
  * Fixed several memory leaks in BWAPI.
  * Fixed a bug where some Zerg upgrades would return false when a Hatchery or Spire was morphing.
  * Fixed a bug where cheat codes were treated as case sensitive.
  * Fixed a regression where [Game::hasCreep](Game#hasCreep.md) returned false incorrectly for some locations.
  * Fixed a regression where [Nuclear Strike](TechTypes#Nuclear_Strike.md) did not execute correctly.
  * Fixed an issue where the frame counter and isPaused would be incorrect or could stop working completely.
  * Fixed a regression where `auto_menu` could not set the bot's race in multiplayer.
  * Fixed a bug where `auto_menu` could not correctly set the bot's race if it was not specifically in slot 0 or slot 1.
  * Fixed a bug where getUnitsIn functions could not find large units in a small location.
  * Fixed an issue where Position and TilePosition's isValid member always returned false if the Broodwar pointer was not initialized.
  * Fixed an issue where the Zerg's [Spore Colony](UnitTypes#Zerg_Spore_Colony.md) and [Sunken Colony](UnitTypes#Zerg_Sunken_Colony.md) unit types did not contain the correct requirements.
  * BWAPI should no longer crash when the Starcraft version is incorrect. Instead it will display a message box and attempt to remain functional.
  * Partially restored WINE compatibility through a workaround that disables BWAPI's Server functionality using the new config option `shared_memory`.

## Changes from BWAPI 3.6 ([r3745](https://code.google.com/p/bwapi/source/detail?r=3745)) to BWAPI 3.6.1 ([r3769](https://code.google.com/p/bwapi/source/detail?r=3769)) ##

Changes:
  * The command optimizer now groups some Use\_Tech commands correctly.
  * Command optimizer level 4 will now group Archon Warp and Dark Archon Meld.

Additions:
  * Added [Orders::NukePaint](Orders#NukePaint.md).
  * Added [TechType::getOrder](TechType#getOrder.md).
  * [Position](Position.md) and [TilePosition](TilePosition.md) can now be treated as a boolean value and will automatically call isValid(). This is an effort to make cleaner-looking code.

Bug Fixes:
  * Fixed an issue where every module using the BWAPILIB library would take some loading time when initializing color information. Instead it will only initialize the information on the first call to the Color(r, g, b) constructor.
  * Fixed various minor potential buffer overflows/underflows.
  * Correctly initialize some Player values.
  * Fixed a bug where non-existent players' Start Locations were excluded from the Start Location group in a **Use Map Settings** (revealing only opponent Start Locations).
  * Fixed a regression where [Archon Warp](TechTypes#Archon_Warp.md) and [Dark Archon Meld](TechTypes#Dark_Archon_Meld.md) always returned an error.


## Changes from BWAPI 3.5.4 ([r3597](https://code.google.com/p/bwapi/source/detail?r=3597)) to BWAPI 3.6 ([r3745](https://code.google.com/p/bwapi/source/detail?r=3745)) ##

Changes:
  * Starcraft now always uses the saved speed setting in Single Player instead of using Normal speed. This means that Single Player games will always start on fastest if that was your last setting in multi-player.
  * Some tileset-reserved palette entries were removed.
  * The constructor for Color(r,g,b) has been optimized for speed.
  * Players that are observing, as well as Start Locations for possible Observer players are excluded from the list of enemies and start locations.
  * The Unload Unit command now uses less actions by performing the command with no matching select unit.
  * Several [TechType::targetsUnit](TechType#targetsUnit.md) and [TechType::targetsPosition](TechType#targetsPosition.md) flags have been altered to be consistent with the tech's capabilities.
  * Logging and the logging\_str config option in BWAPI have been removed. Attach the debugger instead.

Additions:
  * Added [Game::hasPath](Game#hasPath.md).
  * Added [Position::hasPath](Misc#Position.md).
  * Added configuration option "pause\_dbg" which pauses the auto-menu until you attach a debugger (only in DEBUG mode).
  * Added [TilePosition::hasPath](Misc#TilePosition.md).
  * Added [Game::setAlliance](Game#setAlliance.md).
  * Added [Game::setVision](Game#setVision.md).
  * Added more options and variants to [Game::hasPower](Game#hasPower.md).
  * Added a new function [Game::hasPowerPrecise](Game#hasPowerPrecise.md) which takes a pixel coordinate instead of a tile position.
  * Added some Use Map Settings [UnitTypes](UnitTypes.md) that were missing, such as [Map Revealer](UnitTypes#Special_Map_Revealer.md), [Start Location](UnitTypes#Special_Start_Location.md), [Doors](UnitTypes#Doors.md), and [Traps](UnitTypes#Traps.md).
  * Added a new config entry called `mapiteration` which allows you to specify if wildcard maps will be chosen randomly or in a sequence.
  * Added [Unit::getOrderTarget](Unit#getOrderTarget.md).
  * Added [Game::observers](Game#observers.md) which returns the list of observing players in a Use Map Settings.
  * Added [Player::isObserver](Player#isObserver.md).
  * Added the auto\_menu config options `wait_for_min_players`, `wait_for_max_players`, and `wait_for_time` which change the way BWAPI behaves when hosting a network game.
  * BWAPI now supports a tournament module to control the flow of tournaments.
  * Added [Game::elapsedTime](Game#elapsedTime.md).
  * Added [Game::setCommandOptimizationLevel](Game#setCommandOptimizationLevel.md) which allows BWAPI to automatically optimize commands to lower APM.

Bug Fixes:
  * Fixed a bug in [Unit::isInWeaponRange](Unit#isInWeaponRange.md) where the minimum range of 0 would be included in the computation.
  * Fixed an issue where BWAPI and its loaders did not attempt to first find the Starcraft install path in HKEY\_CURRENT\_USER and instead only looked in HKEY\_LOCAL\_MACHINE.
  * Fixed a bug where the bot's APM counter did not reset between matches.
  * Fixed an issue where BWAPI's Windowed Mode (set in config) would initially start the application in Fullscreen before switching back.
  * Increased compatibility with other hacks, depending on their behaviour.
  * Fixed an issue where [Game::hasPower](Game#hasPower.md) could return incorrect results.
  * Fixed some cases where bad calls could cause a buffer overflow.
  * Fixed an issue where users without administrative privileges were unable to use BWAPI. Limited users will now be able to use BWAPI and an AI DLL, but will not be able to use the Client/Server setup.
  * Fixed an issue where [Healing](TechTypes#Healing.md)(for HealMove) and [Maelstrom](TechTypes#Maelstrom.md) could not be used in [Unit::useTechPosition](Unit#useTechPosition.md).
  * Fixed a bug/regression where [Game::mapFileName](Game#mapFileName.md) would return with the full path after using auto-menu.
  * Fixed a bug/regression where Battle.net Recent Maps would save a map with its path attached after using auto-menu.
  * Fixed an issue where auto\_menu did not start multi-player games on its own.
  * Fixed a bug where a unit position returned an incorrect value when it was intended to be Unknown.
  * Fixed a bug where a unit's clientInfo was not reset to NULL in a new game.


## Changes from BWAPI 3.5.3 ([r3589](https://code.google.com/p/bwapi/source/detail?r=3589)) to BWAPI 3.5.4 ([r3597](https://code.google.com/p/bwapi/source/detail?r=3597)) ##

Bug Fixes:
  * Fixed a crash on game end involving extended ascii characters in the map name.
  * Fixed an auto-menu issue/regression where the map's registered path was assumed to be in the `maps\BroodWar` folder
  * Fixed an issue where restartGame switched to a different map in auto-menu mode.
  * Fixed a crash involving a rare occurance that causes a unit's hit box to be partially outside of the playable map area.
  * Fixed an issue where text sent by the player near the end of the match (specifically when BWAPI was defeated) would be carried over to the next game.

## Changes from BWAPI 3.5.2 ([r3586](https://code.google.com/p/bwapi/source/detail?r=3586)) to BWAPI 3.5.3 ([r3589](https://code.google.com/p/bwapi/source/detail?r=3589)) ##

Bug Fixes:
  * Fixed an issue/regression where auto-menu would spawn or hide units in replays depending on the selected auto-menu game type.

## Changes from BWAPI 3.5.1 ([r3584](https://code.google.com/p/bwapi/source/detail?r=3584)) to BWAPI 3.5.2 ([r3586](https://code.google.com/p/bwapi/source/detail?r=3586)) ##

Bug Fixes:
  * Fixed an issue/regression where auto-menu failed to work for replays.

## Changes from BWAPI 3.5 ([r3577](https://code.google.com/p/bwapi/source/detail?r=3577)) to BWAPI 3.5.1 ([r3584](https://code.google.com/p/bwapi/source/detail?r=3584)) ##

Bug Fixes:
  * Fixed an issue where screenshots were disabled while in Windowed mode.
  * Fixed a bug/regression that caused replays to crash.


## Changes from BWAPI Beta 3.4 ([r3347](https://code.google.com/p/bwapi/source/detail?r=3347)) to BWAPI 3.5 ([r3577](https://code.google.com/p/bwapi/source/detail?r=3577)) ##

Changes:
  * The return values for [Game::getGroundHeight](Game#getGroundHeight.md) have been altered. This allows the inclusion of doodads in terrain height computation (For example: Units behind a tree).
  * The DEBUG version now checks for memory leaks.
  * [Game::isBuildable](Game#isBuildable.md) now includes a boolean to specify whether to check if a visible building is blocking the way. It is false by default.
  * [Game::canBuildHere](Game#canBuildHere.md) has slightly increased performance.
  * [Game::drawLine](Game#drawLine.md) has greatly increased performance.
  * The config values "`ai_dll`" and "`ai_dll_dbg`" have been replaced with "`ai`" and "`ai_dbg`", the revision and multi-instance entries ("`ai_dll_rev`", "`ai_dll_#`", etc.) have been removed. More information in the updated bwapi.ini config file.
  * Some distance functions now use integers instead of doubles.
  * The config option "[save\_replay](MenuAutomation#save_replay.md)" under "`auto_menu`" now accepts environment variables as well as our user defined variables. It also creates the directory if it does not exist, and creates the file directly instead of copying `LastReplay.rep` (`LastReplay.rep` will not be created).
  * Most BWAPILIB objects now have an "operator int() const" as a replacement for all other comparison operators. This allows more flexibility, specifically for the developers of BWAPI, so that a call to ".getID()" does not need to be made.
  * Resizing the window in Windowed Mode will now stretch the game screen.
  * Holding ALT in Windowed Mode will now prevent the cursor from leaving the window (same as W-Mode functionality).
  * The auto-menu map selection no longer loops back and forth with the previous menu in order to select the correct map.
  * The `map` entry under `auto_menu` in the config now accepts wildcards, and chooses a random map from the pool when starting the game.
  * **BWAPI's custom network module has been marked deprecated and replaced by [BWDI](http://bwdi.googlecode.com)'s module. (SNP file)**
  * Unit::attackMove and Unit::attackUnit have been renamed to [Unit::attack](Unit#attack.md) to conform with the other functions. Current users can perform a Find&Replace in all files(a function provided by Visual Studio and Notepad++), or use a #define.
  * Ordering an [Infested Terran](UnitTypes#Zerg_Infested_Terran.md) to Attack a location (Attack Move) will now cause it to explode at that location. (Also known as "Sap Location")
  * Renamed UpgradeType::mineralPriceBase to [UpgradeType::mineralPriceBase](UpgradeType#mineralPrice.md), UpgradeType::gasPriceBase to [UpgradeType::gasPrice](UpgradeType#gasPrice.md), and UpgradeType::upgradeTimeBase to [UpgradeType::upgradeTime](UpgradeType#upgradeTime.md), as well as added the parameter that specifies the level. These functions now include the cost factors in calculations. To obtain the base value, use 1 as the parameter.
  * There is a new menu hack that causes menus to load immediately instead of the old one which quickly played the swish-in and swish-out animations.
  * BWAPI's windowed mode can now be resized smaller than the game's resolution. The window will snap to the original dimensions when they are close enough.
  * Holding the CTRL key while resizing the windowed mode window will now maintain a 4:3 aspect ratio.

Additions:
  * Added [Game::getAPM](Game#getAPM.md) which retrieves the bot's running actions per minute and ignores user actions.
  * Added the errors [Errors::File\_Not\_Found](Error#File_Not_Found.md) and [Errors::Invalid\_Parameter](Error#Invalid_Parameter.md).
  * Added [Game::setMap](Game#setMap.md) which changes the map for when you next restart the game.
  * Added [Unit::isUnderAttack](Unit#isUnderAttack.md) which identifies units that have been recently attacked.
  * Added [Unit::getLastAttackingPlayer](Unit#getLastAttackingPlayer.md) which identifies the player that last attacked this unit.
  * Added [Game::getUnitsInRectangle](Game#getUnitsInRectangle.md).
  * Added [Game::getUnitsInRadius](Game#getUnitsInRadius.md).
  * Added [Unit::getUnitsInRadius](Unit#getUnitsInRadius.md).
  * Added [Unit::getUnitsInWeaponRange](Unit#getUnitsInWeaponRange.md).
  * Added the configuration option "holiday" which allows disabling the once-secret holiday modifications that were activated at the appropriate time.
  * Added [Game::setFrameSkip](Game#setFrameSkip.md) which alters Starcraft's built-in frame skipping value.
  * Added some more [UnitTypes](UnitTypes.md) that are specific to Use Map Settings games, as well as the [WeaponTypes](WeaponTypes.md) to go with them.
  * Added a new configuration option "screenshots" under "Starcraft" which allows you to specify the format Starcraft saves screenshots in. Defaults to "GIF".
  * Added [UnitType::isMineralField](UnitType#isMineralField.md) which just returns true if the unit is Mineral Field Type 1, 2, and 3. BWAPI currently converts all Mineral Fields to Type 1 for its own purpose, so you don't need to worry too much about it.
  * Added [Unit::isUnderDarkSwarm](Unit#isUnderDarkSwarm.md).
  * Added [Unit::isUnderDisruptionWeb](Unit#isUnderDisruptionWeb.md).
  * Added [UpgradeType::whatsRequired](UpgradeType#whatsRequired.md), which returns the building required to accompany the upgrade at a certain level.
  * Added [Player::weaponMaxRange](Player#weaponMaxRange.md) which takes a WeaponType instead of a UnitType.
  * Added several configuration options for BWAPI's windowed mode.
  * Added the ability to queue commands like you can in Starcraft. Many command constructors have this addition built-in. Re-read the documentation on them for more information.
  * Added [UnitCommand::isQueued](UnitCommand#isQueued.md).

Bug Fixes:
  * Corrected the return values for [Game::getLatencyFrames](Game#getLatencyFrames.md), [Game::getLatencyTime](Game#getLatencyTime.md), [Game::getRemainingLatencyFrames](Game#getRemainingLatencyFrames.md), and [Game::getRemainingLatencyTime](Game#getRemainingLatencyTime.md).
  * Fixed a crash involving the use of the extended ASCII character set in the drawText functions.
  * **Fixed a memory leak that was unique to Starcraft: Broodwar.**
  * Corrected [WeaponTypes::normalWeaponTypes](WeaponType#normalWeaponTypes.md) and [WeaponTypes::specialWeaponTypes](WeaponType#specialWeaponTypes.md) which were returning the wrong sets.
  * Fixed a bug where [Game::canBuildHere](Game#canBuildHere.md) would fail in some cases where buildings can overlap. See [issue 302](https://code.google.com/p/bwapi/issues/detail?id=302) for more information.
  * Fixed a bug that would cause the game to freeze for several seconds when invalid positions were passed to [Game::drawLineMap](Game#drawLineMap.md).
  * Fixed a bug that prevented the usage of known /commands on a Battle.net server.
  * Fixed an issue where [Overmind With Shell](UnitTypes#Special_Overmind_With_Shell.md), [Overmind](UnitTypes#Special_Overmind.md), [Cerebrate](UnitTypes#Special_Cerebrate.md), [Cerebrate Daggoth](UnitTypes#Special_Cerebrate_Daggoth.md), and [Overmind Cocoon](UnitTypes#Special_Overmind_Cocoon.md) would return false for isDetector(). They now correctly return true.
  * Fixed a bug in Windowed Mode where the System Cursor was displayed instead of the game cursor.
  * [Game::restartGame](Game#restartGame.md) no longer freezes/crashes the game when called during multi-player. Instead it silently returns an error.
  * Fixed an infinite loop involving auto-menu attempting to find the correct map.
  * The new network mode now displays lobby slots correctly.
  * Fixed a bug where [Player::getKillScore](Player#getKillScore.md) returned the unit score instead of the kill score.
  * Fixed an issue where ordering a [Protoss Photon Cannon](UnitTypes#Protoss_Photon_Cannon.md), [Terran Missile Turret](UnitTypes#Terran_Missile_Turret.md), [Zerg Sunken Colony](UnitTypes#Zerg_Sunken_Colony.md), or [Zerg Spore Colony](UnitTypes#Zerg_Spore_Colony.md) to attack would perform no action.
  * Fixed a bug where Game::canUpgrade returned false positives when a required building was not present.
  * Fixed an issue where some bullet types such as the [Subterranean Spines](BulletTypes#Subterranean_Spines.md) were inaccessible with CompleteMapInformation disabled.
  * Fixed an issue where area abilities such as EMP Shockwave could not be used on a unit target (Use\_Tech\_Unit).
  * Fixed a bug where two or more instances could conflict and crash when saving LastReplay.

## Changes from BWAPI Beta 3.3 ([r3163](https://code.google.com/p/bwapi/source/detail?r=3163)) to BWAPI Beta 3.4 ([r3347](https://code.google.com/p/bwapi/source/detail?r=3347)) ##

Changes:

  * [Position](http://code.google.com/p/bwapi/wiki/Misc#Position)::getApproxDistance now returns an integer and more accurately resembles the internal Starcraft function.
  * [Player::allUnitCount](Player#allUnitCount.md) now returns the number of accessible units of the given type for the given player. If complete map information is disabled, this will be equivalent to [Player::visibleUnitCount](Player#visibleUnitCount.md).
  * [Player::getUpgradeLevel](Player#getUpgradeLevel.md) now also returns information for enemy players when the Complete Map Information flag is disabled if at least one completed unit owned by that player that uses that upgrade type is accessible.
  * There has been a regression involving the optimization of issuing commands to multiple units at the same time (Stop, Hold, Cloak/Decloak, Burrow/Unburrow, Siege/Unsiege). This will not impact the behaviour of the game or the AI. It will however increase the APM of the AI.
  * Renamed Unit::getLastOrderFrame to [Unit::getLastCommandFrame](Unit#getLastCommandFrame.md) to make it consistent with [Unit::getLastCommand](Unit#getLastCommand.md), [Unit::issueCommand](Unit#issueCommand.md), and [Unit::canIssueCommand](Unit#canIssueCommand.md).

Additions:
  * Added [Unit::isInWeaponRange](Unit#isInWeaponRange.md) which returns true if the specified target unit is in the immediate weapon range of the callee.
  * Added [Player::visibleUnitCount](Player#visibleUnitCount.md) which returns the number of visible units of the given type owned by the player.
  * Added [Game::neutral](Game#neutral.md) - returns a pointer to the neutral player.
  * Added [Game::allies](Game#allies.md) - returns a reference to the set of ally players that have not left or been defeated.
  * Added [Game::enemies](Game#enemies.md) - returns a reference to the set of enemy players that have not left or been defeated.
  * BWAPI will attempt to compare its revision/build with the AI revision/build and load the correct BWAPI module for the AI. Note: For the moment this only applies when attaching BWAPI to Starcraft and not when the module is loaded.
  * Added the following [Player](Player.md) functions to retrieve player score: [Player::getUnitScore](Player#getUnitScore.md), [Player::getKillScore](Player#getKillScore.md), [Player::getBuildingScore](Player#getBuildingScore.md), [Player::getRazingScore](Player#getRazingScore.md), [Player::getCustomScore](Player#getCustomScore.md).
  * Added the following UnitTypes which can be used as a macro: [UnitTypes::AllUnits](UnitTypes#All_Units.md), [UnitTypes::Men](UnitTypes#Men.md), [UnitTypes::Buildings](UnitTypes#Buildings.md), [UnitTypes::Factories](UnitTypes#Factories.md).
  * Added [UnitTypes::allMacroTypes](UnitType#allMacroTypes.md) for the introduced macros.
  * Added [Unit::placeCOP](Unit#placeCOP.md) which allows you to relocate Flag Beacons in Use Map Settings or Capture the Flag game types.
  * Added [Unit::isAttackFrame](Unit#isAttackFrame.md) - returns true if the unit is performing an attack animation or starting an attack.
  * **Added the LPIP network mode known as "Local PC (Pipes)". This mode is compatible with Windows XP and previous revisions of BWAPI.** However it has the same issue as the other custom network mode. Instructions are the same, copy the SNP file to the Starcraft directory.
  * Added [Unit::getAcidSporeCount](Unit#getAcidSporeCount.md).
  * Added [Unit::isInvincible](Unit#isInvincible.md).
  * Added [Unit::getLastCommand](Unit#getLastCommand.md) - returns the last successful command that BWAPI issued to the unit.
  * Added [UnitCommand::getUnit](UnitCommand#getUnit.md) - returns the unit the command is for.
  * Added [UnitCommand::getTarget](UnitCommand#getTarget.md) - returns the target unit of the command, or null if there is no target unit.
  * Added [UnitCommand::getTargetPosition](UnitCommand#getTargetPosition.md) - returns the target position of the command, or Positions::None if there is no target position.
  * Added [UnitCommand::getTargetTilePosition](UnitCommand#getTargetTilePosition.md) - returns the target tile position of the command, or Positions::None if there is no target tile position.
  * Added [UnitCommand::getUnitType](UnitCommand#getUnitType.md) - returns the unit type of the command, or UnitTypes::None if the command is not of type Build, Build\_Addon, Train, or Morph.
  * Added [UnitCommand::getTechType](UnitCommand#getTechType.md) - returns the tech type of the command, or TechTypes::None if the command is not of type Research, Use\_Tech, Use\_Tech\_Position, or Use\_Tech\_Unit.
  * Added [UnitCommand::getUpgradeType](UnitCommand#getUpgradeType.md) - returns the upgrade type of the command, or UpgradeTypes::None if the command is not of type Upgrade.
  * Added [UnitCommand::getSlot](UnitCommand#getSlot.md) - returns the slot of the command, or -1 if the command is not of type Cancel\_Train\_Slot.
  * Applied a hack that now looks for files relative to the Starcraft directory first before checking the MPQ. Modifications to Starcraft can now be done without the need for MPQ management.

Bug Fixes:
  * Fixed a bug where [Game::canBuildHere](Game#canBuildHere.md) would do collision checks with flying and lifted units.
  * Fixed a bug where [Game::enemy](Game#enemy.md) would return NULL if the enemy player left the game.
  * Fixed a bug where [Unit::getUpgradeLevel](Unit#getUpgradeLevel.md) would always return 0 in client programs when complete map information was disabled.
  * Fixed a bug where [Game::printf](Game#printf.md) and [Game::sendText](Game#sendText.md) could cause a crash when called from the BWAPI Client using a formatting character "%" as part of the desired message.
  * Fixed a regression that prevented the use of Nuclear Missiles.
  * Corrected a mistake where [Colors](Color#Colors.md)::Purple would appear Orange.
  * Fixed a crash involving a buffer overflow with text formatting for [Game::printf](Game#printf.md), [Game::sendText](Game#sendText.md), and [Game::drawText](Game#drawText.md).
  * Fixed a bug where [Unit::getLastOrderFrame](Unit#getLastOrderFrame.md) would not reset to 0 at the start of a new match.
  * Fixed a bug where Starcraft would hang when attempting to connect a BWAPI Client to the BWAPI Server during a match.
  * Fixed a bug where some units were mistakenly considered selected.
  * Fixed a bug that prevented the placement of Infested Command Centers and Zerg Flag Beacons off the creep.
  * Fixed an issue where loaded units could be given orders.
  * Fixed an issue where Overlords would accept orders to load units when the Ventral Sacs upgrade was not researched.
  * Fixed an issue where completed transports would accept orders to load incomplete units and vice-versa.
  * Fixed an issue where heroes could not use abilities until the technology was researched.
  * Fixed an issue where Infested Kerrigan could not use all of her abilities.
  * Fixed an issue where our custom network modes would bring users back to the main menu instead of the game select menu.
  * Fixed a BWAPI Client crash that involved passing a NULL parameter to [Player::isAlly](Player#isAlly.md) and [Player::isEnemy](Player#isEnemy.md).

## Changes from BWAPI Beta 3.2 ([r2917](https://code.google.com/p/bwapi/source/detail?r=2917)) to BWAPI Beta 3.3 ([r3163](https://code.google.com/p/bwapi/source/detail?r=3163)) ##

Changes:

  * [Game::canBuildHere](Game#canBuildHere.md) now has an additional boolean value that allows the user to specify if the function should consider checking if they have first explored the area.
  * Tile position variables in [Game](Game.md) functions have been clarified.
  * Game::getMouseX and Game::getMouseY have been removed due to deprecation. Use [Game::getMousePosition](Game#getMousePosition.md) instead.
  * Game::getScreenX and Game::getScreenY have been removed due to deprecation. Use [Game::getScreenPosition](Game#getScreenPosition.md) instead.
  * Renamed Unit::setRallyPosition and Unit::setRallyUnit to [Unit::setRallyPoint](Unit#setRallyPoint.md) so that it conforms with the other commands.
  * `[`Config`]` Auto-menu options in the configuration file have been moved to the `[`auto\_menu`]` group.
  * `[`Config`]` Renamed the auto\_menu option _`LAN_UDP`_ to _`LAN`_.
  * Removed UnitType::getSublabel, as it didn't appear to be significant.

New Functions:
  * Added [UnitType::cloakingTech](UnitType#cloakingTech.md) - returns the tech used to cloak the unit, or TechTypes::None if the unit cannot cloak or is permanently cloaked
  * Added [Unit::getPowerUp](Unit#getPowerUp.md) - returns the power up the unit is holding, or NULL if the unit is not holding a power up
  * Added [Unit::isInterruptible](Unit#isInterruptible.md) - returns true if the unit can be interrupted without issuing a stop or one of the cancel commands.
  * Added [Unit::isStuck](Unit#isStuck.md) - Returns true if the unit is "stuck" on other units.
  * Made [Game::setLastError](Game#setLastError.md) available.
  * Added several UnitType functions: [UnitType::isHero](UnitType#isHero.md), [UnitType::isPowerup](UnitType#isPowerup.md), [UnitType::isBeacon](UnitType#isBeacon.md), [UnitType::isFlagBeacon](UnitType#isFlagBeacon.md), [UnitType::isSpecialBuilding](UnitType#isSpecialBuilding.md), and [UnitType::isSpell](UnitType#isSpell.md).
  * Added [Game::getInstanceNumber](Game#getInstanceNumber.md) to identify which instance an AI module belongs to.
  * Added several [Player](Player.md) functions for obtaining upgraded unit type stats, including [Player::topSpeed](Player#topSpeed.md), [Player::groundWeaponMaxRange](Player#groundWeaponMaxRange.md), [Player::airWeaponMaxRange](Player#airWeaponMaxRange.md), [Player::sightRange](Player#sightRange.md), [Player::groundWeaponDamageCooldown](Player#groundWeaponDamageCooldown.md), and [Player::armor](Player#armor.md).
  * Added [TechType::targetsUnit](TechType#targetsUnit.md) - returns true if the tech type requires a unit to target.
  * Added [TechType::targetsPosition](TechType#targetsPosition.md) - returns true if the tech type requires a position to target.
  * Added [Game::getNukeDots](Game#getNukeDots.md) - returns the set of accessible nuke dots on the map.
  * Added [Unit::canIssueCommand](Unit#canIssueCommand.md) - use to see if you can issue a command to the given unit, without actually executing it.
  * Added [Game::issueCommand](Game#issueCommand.md) - issues a command to a set of units.

New Config Features:
  * `[`Config`]` Added the ability to load different revisions of BWAPI for different modules using the config options _`ai_dll_rev`_ and _`ai_dll_#_rev`_.
  * `[`Config`]` Added auto-menu race options RandomTP, RandomTZ, and RandomPZ which allows you to randomly choose one of two races.
  * `[`Config`]` Added the auto-menu option _`lan_mode`_ which allows you to choose between the different multiplayer network modes.
  * `[`Config`]` For auto-menu, added the ability to choose a race for specific enemy players using _`enemy_race_#`_.

Other New Features:

  * `[`W-Mode`]` The position of the window in the config now changes when a new multiple-instance compatible client is launched.
  * **BWAPI can now play networked games between multiple instances using the BWAPI network module (BWAPI\_SNPModule.snp) which currently supports winsock UDP on localhost.** Bad news: Windows XP users may experience failure. Good news: It can be used with older BWAPI revisions.
  * Added Heroes, Beacons, and Standard Powerups to UnitTypes. This gives you more flexibility for _**Capture The Flag**_ and _**Use Map Settings**_ (including _**Campaigns**_).
  * Added hero weapons to WeaponTypes.
  * **BWAPI now supports a native Windowed mode.** Pressing ALT+Enter or typing /wmode will toggle between fullscreen and windowed mode. (Note that this windowed mode is not compatible with Battle.net)
  * Added [Errors::Invalid\_Tile\_Position](Error#Invalid_Tile_Position.md) - returned when you try to build something at an invalid tile position.

Bug Fixes:

  * Fixed a bug where [Unit::hasPath](Unit#hasPath.md) would not work correctly in BWAPI Client programs.
  * Fixed a bug where [Unit::getResourceGroup](Unit#getResourceGroup.md) would not work correctly in BWAPI Client programs.
  * Fix several issues for commands that were being sent repetitively and for actions that couldn't actually be performed.
  * Several functions in the BWAPI Client have been updated to match behaviours and fix issues that were once in the BWAPI server.
  * Fixed some unlikely crashes, possibly related to the compatibility with other hacks.
  * Fixed a bug where unit command error codes wouldn't be generated correctly in BWAPI Client.
  * Fixed a bug where networked games involving auto\_menu would desynchronize.
  * Fixed a bug where calling [Game::restartGame](Game#restartGame.md) would not work correctly during [AIModule::onEnd](AIModule#onEnd.md).
  * Fixed a bug where restarting the game wouldn't work correctly for BWAPI client programs.

## Changes from BWAPI Beta 3.1.1 ([r2864](https://code.google.com/p/bwapi/source/detail?r=2864)) to BWAPI Beta 3.2 ([r2917](https://code.google.com/p/bwapi/source/detail?r=2917)) ##

Changes:
  * A Debug build now loads the AI specified by ai`_`dll`_`dbg (ai`_`dll`_`#`_`dbg for multiple instances) in bwapi.ini.
  * When the user selects a unit, the command is not processed unless it is given an order. (Decrease action count)
  * [Position](Misc#Position.md) and [TilePosition](Misc#TilePosition.md) conversions are now explicit.
  * Issuing Stop, Hold Position, Siege, Unsiege, Cloak, Decloak, Burrow, or Unburrow for multiple units in the same frame will perform the commands in groups instead of individually. (Decrease APM).
  * canUpgrade and canResearch with a Unit`*` specified will now fail if the unit is busy.

New Features:
  * Added [auto\_restart](http://code.google.com/p/bwapi/wiki/MenuAutomation#auto_restart) option to bwapi.ini.
  * Added [Game::getReplayFrameCount](Game#getReplayFrameCount.md) - Retrieves the maximum number of frames in a replay.
  * Added a [save\_replay](http://code.google.com/p/bwapi/wiki/MenuAutomation#save_replay) option to bwapi.ini which copies LastReplay.rep to the destination specified.
  * Added a [sound](http://code.google.com/p/bwapi/wiki/MenuAutomation#sound) option to bwapi.ini which allows you to disable all Starcraft sound functionality to increase performance.
  * Added [Game::setGUI](Game#setGUI.md) which allows you to disable all rendering within the game for a huge performance increase.

Bug Fixes:
  * Fix a bug where canMake would fail to work correctly when units of a different race are owned.
  * Fix an issue where ChaosLauncherInjector and MPQDraftInjector were using a non-standard registry call.
  * Fix an issue where an MPQDraft executable failed to find the bwapi-folder when launched from a different directory.
  * Fix an issue that prevented Player::getUpgradeLevel() from working correctly.
  * Fix an issue that performed auto-menu key presses outside of Starcraft.
  * Fix an issue where the neutral player was not being processed correctly.


## Changes from BWAPI Beta 3.1 ([r2796](https://code.google.com/p/bwapi/source/detail?r=2796)) to BWAPI Beta 3.1.1 ([r2864](https://code.google.com/p/bwapi/source/detail?r=2864)) ##

Changes:

  * bwapi-errors are now written to the logs folder with a time and date stamp.
  * Using train or morph(unit) on a hatchery, lair, or hive will automatically issue the order to a larva.
  * Ordering a Nydus Canal to build a Nydus Canal will allow you to place the Nydus exit.
  * Changed the palette index for some [Colors](Color#Colors.md) and updated the colors for sendText in Single Player.
  * The Config button in ChaosLauncherInjector and MPQDraftInjector will now load the BWAPI config file from the Starcraft path obtained by the registry.
  * Incomplete units being trained now 'exist' according to BWAPI, and thus can generate UnitCreate, UnitShow, and UnitDiscover events when the unit begins training rather than when the unit actually pops out of the factory/barracks/etc. Internal enemy units are still not accessible when Complete Map Info is disabled.

New features:

  * Added [Unit::getResourceGroup](Unit#getResourceGroup.md) - Returns a group index for a resource to identify which base it belongs to.
  * Implemented the Nydus Canal. You can now tell a Nydus Canal to build an exit.
  * Added [Unit::hasPath](Unit#hasPath.md)(Unit `*`target), a macro function that calls hasPath for the target unit.
  * Added the following Color constants: Colors::Brown and Colors::Teal.
  * Added [Player::getColor](Player#getColor.md) and [Player::getTextColor](Player#getTextColor.md) to retrieve a player's color for drawing and control character for text messages.

Bug fixes:

  * Fixed a desynch caused by a large number of commands being processed.
  * Fixed restartGame which was broken in a previous release.
  * Fixed a crash when passing a NULL target to Unit::getDistance().
  * Fixed an issue where Map::getMapHash() failed on campaign maps.
  * Fixed a bug that prevented sending text when no module is loaded.
  * Fixed a bug involving duplicate cheat codes.
  * Fixed a bug where onMorph would sometimes be called when a building finished morphing, rather than when it began morphing.
  * Fixed a canBuildHere issue involving the message "Couldn't reach building site".
  * Fix an issue where hasPath failed at cliff edges.

## Changes from BWAPI Beta 3.0.3 ([r2639](https://code.google.com/p/bwapi/source/detail?r=2639)) to BWAPI Beta 3.1 ([r2796](https://code.google.com/p/bwapi/source/detail?r=2796)) ##

The following features have been altered:

  * Player::isAlly, Player::isEnemy, and Game::enemy no longer include players that don't start with any supply (used or available).
  * Using a hacked executable, ChaosLauncher can now run multiple instances of Starcraft. Each instance of BWAPI can load a different AI module specified in the configuration(bwapi.ini) file. There are plans for inter-process communication as a network module.

The following functions have been added:

  * [Game::getLatencyFrames](Game#getLatencyFrames.md) - returns the maximum number of frames for a command to be processed.
  * [Game::getLatencyTime](Game#getLatencyTime.md) - returns the maximum time for a command to be processed (milliseconds).
  * [Game::getRemainingLatencyFrames](Game#getRemainingLatencyFrames.md) - returns the remaining number of frames for a command to be processed, according to the current frame.
  * [Game::getRemainingLatencyTime](Game#getRemainingLatencyTime.md) - returns the remaining time for a command to be processed (milliseconds), according to the current tick count.
  * [Game::getRevision](Game#getRevision.md) - returns the current BWAPI revision number
  * [Game::isDebug](Game#isDebug.md) - returns whether the current build is debug mode or not
  * [Game::sendTextEx](Game#sendTextEx.md) - allows the AI to send a text message to allies only
  * [Unit::hasPath](Unit#hasPath.md) - checks if the unit and target specified are on the same island
  * [Game::isLatComEnabled](Game#isLatComEnabled.md) - returns true if latency compensation is enabled
  * [Game::setLatCom](Game#setLatCom.md) - use to enable or disable latency compensation; Default: Enabled
  * [Unit::getLastOrderFrame](Unit#getLastOrderFrame.md) - Returns the frame of the last successful order issued.
  * [Unit::setClientInfo](Unit#setClientInfo.md) - Sets the unit's custom client info. The client is responsible for deallocation. In other words, this allows the user to associate data with the unit.
  * [Unit::getClientInfo](Unit#getClientInfo.md) - Returns the unit's custom client info. The client is responsible for deallocation.


Bug fixes:

  * Fixed a bug where multiple onEnd events would be produced.
  * Fixed a bug where onFrame was called after onEnd.
  * Fixed a bug where neutral buildings were not included in getStaticNeutralUnits when called from the client process.
  * Fixed a bug that caused Starcraft to randomly pause for 100ms every couple of seconds.
  * Fixed a bug that caused Starcraft to crash while retrieving force names.
  * Fixed an off-by-one issue when retrieving force names.
  * Fixed a compatibility issue with auto-menu and a non-english locale.
  * Fixed a user bug when attempting to recall(hotkey) a group of units.
  * Fixed a bug involving the inability to retrieve enemy upgrades via Unit::getUpgradeLevel(UpgradeType).
  * Fixed an issue with canBuildHere failing when units are at a valid position on the same tile.
  * Fixed an issue with hasPower failing for 4x3 buildings at the top-most position of the power range.
  * Fixed a bug where canMake will fail for Mutalisks when a Greater Spire is owned.
  * Fixed an issue with an unhandled canBuildHere requirements that produces the message "You must explore there first.".
  * Fixed an auto-menu bug that would pause at the end of a Replay in Single Player.
  * Fixed an issue that would reselect the user's unit every time BWAPI performed an action. Reduces APM by 1/3.

## Changes from BWAPI Beta 3.0.2 ([r2630](https://code.google.com/p/bwapi/source/detail?r=2630)) to BWAPI Beta 3.0.3 ([r2639](https://code.google.com/p/bwapi/source/detail?r=2639)) ##

Fixed a bug with BWAPI's frame 0 accessibility where BWTA would not identify base locations when run on the client.

## Changes from BWAPI Beta 3.0.1 ([r2630](https://code.google.com/p/bwapi/source/detail?r=2630)) to BWAPI Beta 3.0.2 ([r2635](https://code.google.com/p/bwapi/source/detail?r=2635)) ##

Fixed order of UnitDiscover/UnitEvade events.

## Changes from BWAPI Beta 3.0 ([r2627](https://code.google.com/p/bwapi/source/detail?r=2627)) to BWAPI Beta 3.0.1 ([r2630](https://code.google.com/p/bwapi/source/detail?r=2630)) ##

Fixed order of events/callbacks.

## Changes from BWAPI Beta 2.8 ([r2422](https://code.google.com/p/bwapi/source/detail?r=2422)) to BWAPI Beta 3.0 ([r2627](https://code.google.com/p/bwapi/source/detail?r=2627)) ##

The internal implementation of the Unit class has been refactored to optimize performance for the client-server architecture.

Unit IDs now increment from 0, rather than just casting the unit address as an int.

Menu automation has increased speed and several more dialogs are automated.

The following callbacks have been added:
  * [AIModule::onUnitDiscover](AIModule#onUnitDiscover.md) - called when a unit becomes accessible
  * [AIModule::onUnitEvade](AIModule#onUnitEvade.md) - called right before a unit becomes inaccessible

The following Events have been added:
  * [Event::UnitDiscover](Event#UnitDiscover.md) - corresponds with [AIModule::onUnitDiscover](AIModule#onUnitDiscover.md)
  * [Event::UnitEvade](Event#UnitEvade.md) - corresponds with [AIModule::onUnitEvade](AIModule#onUnitEvade.md)

The following functions have been added:

  * [Game::getGroundHeight](Game#getGroundHeight.md)(TilePosition position) - works same way as Game::getGroundHeight(int x, int y)
  * [Game::getFPS](Game#getFPS.md) - returns the frames per second the game is running at.
  * [Game::getAverageFPS ](Game#getAverageFPS.md) - returns the exponential moving average frames per second.
  * [Game::setTextSize](Game#setTextSize.md) - sets the text size for drawText commands.
  * [Game::mapPathName](Game#mapPathName.md) - returns the path and file name of the map.
  * [Game::getForce](Game#getForce.md) - returns the Force object with the given force ID, or NULL if no force has the given ID.
  * [Game::getPlayer](Game#getPlayer.md) - returns the Player object with the given player ID, or NULL if no player has the given ID.
  * [Game::getUnit](Game#getUnit.md) - returns the Unit object with the given unit ID, or NULL if no unit has the given ID.

  * [Unit::getCarrier](Unit#getCarrier.md) - returns the carrier that this unit belongs to, or NULL if this unit is not an Interceptor or if its carrier has recently been destroyed.
  * [Unit::getInterceptors](Unit#getInterceptors.md) - Returns the set of interceptors owned by this carrier. The interceptors inside the carrier can be obtained via getLoadedUnits, while the interceptors outside of the carrier is the difference of these two sets.
  * [Unit::getNydusExit](Unit#getNydusExit.md) - Returns the Nydus Canal unit that is connected to this Nydus Canal, or NULL if the unit doesn't have a connecting Nydus Canal.
  * [Unit::hasNuke](Unit#hasNuke.md) - returns true for nuclear missile silos that have a nuke ready.
  * [Unit::isDetected](Unit#isDetected.md) - returns true if the unit is visible and detected/targetable. If this is false and [Unit::isVisible](Unit#isVisible.md) is true, then the unit is only partially visible, and won't be targetable until a science vessel, overlord, or some other detection unit comes in range and detects the unit.
  * [Unit::isHoldingPosition](Unit#isHoldingPosition.md) - returns true if the unit is holding position.
  * [Unit::gather](Unit#gather.md) - orders the unit to gather the specified mineral patch or refinery/extractor/assimilator
  * [Unit::move](Unit#move.md) - orders the unit to move to the specified position

  * [TechType::researchTime](TechType#researchTime.md) - returns the number of frames needed to research the given tech type.

  * [Position::isValid](Misc#Position.md) - returns true if the position is on the map.
  * [Position::makeValid](Misc#Position.md) - modifies the position so that it becomes valid (on the map), moving it at little as possible
  * [TilePosition::makeValid](Misc#TilePosition.md) - modifies the tile position so that it becomes valid (on the map), moving it at little as possible

The following functions have been renamed:
  * Game::mapFilename has been renamed to [Game::mapFileName](Game#mapFileName.md).
  * Game::getMapHash has been renamed to [Game::mapHash](Game#mapHash.md) and it now returns the sha1 hash of the map file as a std::string.

The following error codes have been added:
  * [Error::Currently\_Researching](Error#Currently_Researching.md) - generated when you try to tell a unit to research a TechType that is already being researched (at that unit or another unit).
  * [Error::Currently\_Upgrading](Error#Currently_Upgrading.md) - generated when you try to tell a unit to upgrade an UpgradeType that is already being upgraded (at that unit or another unit).

The following UpgradeTypes have been renamed:
  * Protoss\_Armor -> Protoss\_Ground\_Armor
  * Protoss\_Plating -> Protoss\_Air\_Armor
  * Charon\_Booster -> Charon\_Boosters

Renamed UnitCommandType::Attack\_Position to [UnitCommandType::Attack\_Move](UnitCommandTypes.md).

The following [Orders](Orders.md) have been renamed/merged:

  * SiegeMode -> Sieging
  * TankMode  -> Unsieging
  * Burrow    -> Burrowing
  * Unburrow  -> Unburrowing
  * StrafeUnit1 -> InterceptorAttack
  * StrafeUnit2 -> ScarabAttack
  * Return      -> InterceptorReturn
  * Rightclickaction -> RightClickAction
  * ReaverStop  -> Stop
  * CarrierStop -> Stop
  * Attack1          -> AttackUnit
  * Attack2          -> AttackUnit
  * CarrierAttack1   -> AttackUnit
  * CarrierAttack2   -> AttackUnit
  * CarrierFight     -> AttackUnit
  * ReaverAttack1    -> AttackUnit
  * ReaverAttack2    -> AttackUnit
  * ReaverFight      -> AttackUnit
  * StayinRange      -> AttackUnit
  * SapUnit          -> AttackUnit
  * WatchTarget      -> AttackUnit
  * TowerAttack      -> AttackUnit
  * TurretAttack     -> AttackUnit
  * AttackFixedRange -> AttackUnit
  * CarrierHoldPosition -> HoldPosition
  * QueenHoldPosition   -> HoldPosition
  * SuicideHoldPosition -> HoldPosition
  * MedicHoldPosition   -> HoldPosition
  * ReaverHoldPosition  -> HoldPosition
  * BuildTerran     -> PlaceBuilding
  * BuildProtoss1   -> PlaceBuilding
  * DroneStartBuild -> PlaceBuilding
  * DroneLand       -> PlaceBuilding
  * SapLocation -> AttackMove
  * Repair1 -> Repair
  * Repair2 -> Repair
  * FireYamatoGun1 -> FireYamatoGun
  * FireYamatoGun2 -> FireYamatoGun
  * InfestMine1 -> InfestedCommandCenter
  * InfestMine2 -> CastInfestation
  * InfestMine3 -> CastInfestation
  * InfestMine4 -> InfestingCommandCenter
  * TerranBuildSelf  -> IncompleteBuilding
  * ProtossBuildSelf -> IncompleteBuilding
  * DroneBuild       -> IncompleteBuilding
  * ZergBuildSelf    -> IncompleteBuilding
  * WarpingArchon     -> ArchonWarp
  * WarpingDarkArchon -> DarkArchonMeld
  * MagnaPulse       -> CastLockdown
  * DarkSwarm        -> CastDarkSwarm
  * SummonBroodlings -> CastSpawnBroodlings
  * EmpShockwave     -> CastEMPShockwave
  * NukePaint        -> CastNuclearStrike
  * NukeGround       -> CastNuclearStrike
  * PlaceScanner     -> CastScannerSweep
  * DefensiveMatrix  -> CastDefensiveMatrix
  * PsiStorm         -> CastPsionicStorm
  * Irradiate        -> CastIrradiate
  * Plague           -> CastPlague
  * Consume          -> CastConsume
  * Ensnare          -> CastEnsnare
  * StasisField      -> CastStasisField
  * Hallucination1   -> CastHallucination
  * Restoration      -> CastRestoration
  * ResetCollision1  -> ResetCollision
  * ResetCollision2  -> ResetCollision
  * InitPsiProvider  -> Nothing
  * InitArbiter      -> PlayerGuard
  * Teleport         -> CastRecall

The following functions have changed in functionality:
  * [Game::getGroundHeight](Game#getGroundHeight.md) now accepts build tile coordinates rather than walk tile coordinates.
  * [Unit::getLoadedUnits](Unit#getLoadedUnits.md) now returns a set rather than a list.
  * [AIModule::onSendText](AIModule#onSendText.md) now has a void return type, rather than bool. Instead of returning true you can use [Game::printf](Game#printf.md) or [Game::sendText](Game#sendText.md) to send the message.

Bug fixes:
  * Fixed a bug where [Game::getGroundHeight](Game#getGroundHeight.md) would always return 0 for tiles until Zerg Creep.
  * Fixed a bug where [Unit::isConstructing](Unit#isConstructing.md) would not return true for Terran buildings that are constructing add-ons
  * Fixed a bug where [Unit::isIdle](Unit#isIdle.md) would sometimes return true when the unit is Constructing
  * Fixed a bug where [Unit::getBuildType](Unit#getBuildType.md) would not work for Terran buildings that are constructing add-ons
  * Fixed a bug where [Unit::isConstructing](Unit#isConstructing.md) would not return true for incomplete Terran add-ons that are being constructed.
  * Fixed a bug where [Unit::getBuildUnit](Unit#getBuildUnit.md) would return NULL for incomplete Terran add-ons that are being constructed.
  * Fixed a bug where [Unit::isTraining](Unit#isTraining.md) would not return true for Reavers or Carriers.
  * Fixed a bug where [Unit::getRemainingTrainTime](Unit#getRemainingTrainTime.md) would incorrectly return 0 on some frames due to latency.
  * Fixed a bug where [Unit::getType](Unit#getType.md) would not immediately switch to Egg/Lurker Egg/Cocoon after issuing a morph command to a unit
  * Fixed a bug where [Unit::isBeingConstructed](Unit#isBeingConstructed.md) would return false for morphing Zerg units
  * Fixed a bug where [Unit::isConstructing](Unit#isConstructing.md) would return false morphing Zerg units
  * Fixed a bug where [Unit::isIdle](Unit#isIdle.md) would return true morphing Zerg units
  * Fixed a bug where [Unit::getBuildType](Unit#getBuildType.md) would sometimes return UnitTypes::None for morphing Zerg units
  * Fixed a bug where [Unit::getRemainingBuildTime](Unit#getRemainingBuildTime.md) would sometimes return incorrect values for morphing Zerg units
  * Fixed a bug where [Unit::getRemainingResearchTime](Unit#getRemainingResearchTime.md) would sometimes return 0 due to latency.
  * Fixed a bug where [Unit::getRemainingUpgradeTime](Unit#getRemainingUpgradeTime.md) would sometimes return 0 due to latency.
  * Fixed a bug where [Game::canResearch](Game#canResearch.md) would return true while another unit was researching the same TechType.
  * Fixed a bug where [Game::canUpgrade](Game#canUpgrade.md) would return true while another unit was upgrading the same UpgradeType.
  * Fixed a bug with UpgradeType::Apial\_Sensors.whatResearches() so that it now correctly returns UnitTypes::Protoss\_Fleet\_Beacon.
  * Fixed a bug with [Unit::getTransport](Unit#getTransport.md) so that it works for Protoss Interceptors
  * Fixed a bug with [Unit::isLoaded](Unit#isLoaded.md) so that it returns true if and only if [Unit::getTransport](Unit#getTransport.md)!=NULL.
  * Fixed a bug with [Unit::getLoadedUnits](Unit#getLoadedUnits.md) so that it also returns the Interceptors currently loaded inside a Protoss Carrier.
  * Fixed a bug where [Unit::getPosition](Unit#getPosition.md) and [Unit::getTilePosition](Unit#getTilePosition.md) would return incorrect positions for loaded units.
  * Fixed a bug where [Unit::useTech](Unit#useTech.md) would not cast Maelstroms.
  * Fixed a bug where [Unit::useTech](Unit#useTech.md) would not work for Nuclear Missiles.
  * Fixed a bug where Siege Tanks, Goliaths, Reavers, and Carriers would not attack when given an attackUnit command.
  * Fixed a bug where Starcraft would crash when an AI issued a stop command to a Reaver or Carrier.
  * Fixed a bug where [Game::unitsOnTile](Game#unitsOnTile.md) would incorrectly include Terran Add-ons for tiles that did not contain a Terran Add-on.
  * Fixed a bug where [Unit::isBeingHealed](Unit#isBeingHealed.md) wouldn't work. Now returns true for Terran units that are being healed or repaired.

## Changes from BWAPI Beta 2.7.2 ([r2239](https://code.google.com/p/bwapi/source/detail?r=2239)) to BWAPI Beta 2.8 ([r2422](https://code.google.com/p/bwapi/source/detail?r=2422)) ##

Added [menu automation](MenuAutomation.md) - you can now automatically start replays and games with no manual user interaction.

New classes:
  * Added class [GameType](GameType.md).
  * Added class [Bullet](Bullet.md).

The following functions have been added:
  * Added [AIModule::onReceiveText](AIModule#onReceiveText.md) - called when messages are received from other players.
  * Added [Game::isBattleNet](Game#isBattleNet.md) - returns true during games being played on BattleNet.
  * Added [Game::getBullets](Game#getBullets.md) - returns the set of accessible bullets.
  * Added [Game::getGameType](Game#getGameType.md) - returns the game type of the current match.
  * Added [Player::maxEnergy](Player#maxEnergy.md) - returns the max energy for the unit type, taking into account the player's upgrades.

The following functions have changed in functionality:
  * [Unit::getHitPoints](Unit#getHitPoints.md) now rounds up to nearest integer rather than down.
  * [Unit::getShields](Unit#getShields.md) now rounds up to nearest integer rather than down.
  * [Unit::getEnergy](Unit#getEnergy.md) now rounds up to nearest integer rather than down.
  * [Game::enableFlag](Game#enableFlag.md) can now also be called in AIModule::onFrame() during frame 0.
All neutral units are accessible in AIModule::onFrame() during frame 0.

The AttackType class has been renamed to [BulletType](BulletType.md).

The following functions are now case-insensitive for the strings they accept:
  * [BulletTypes::getBulletType](BulletType#getBulletType.md)
  * [DamageTypes::getDamageType](DamageType#getDamageType.md)
  * [Errors::getError](Error#getError.md)
  * [ExplosionTypes::getExplosionType](ExplosionType#getExplosionType.md)
  * [GameTypes::getGameType](GameType#getGameType.md)
  * [Orders::getOrder](Order#getOrder.md)
  * [PlayerTypes::getPlayerType](PlayerType#getPlayerType.md)
  * [Races::getRace](Race#getRace.md)
  * [TechTypes::getTechType](TechType#getTechType.md)
  * [UnitCommandTypes::getUnitCommandType](UnitCommandType#getUnitCommandType.md)
  * [UnitSizeTypes::getUnitSizeType](UnitSizeType#getUnitSizeType.md)
  * [UnitTypes::getUnitType](UnitType#getUnitType.md)
  * [UpgradeTypes::getUpgradeType](UpgradeType#getUpgradeType.md)
  * [WeaponTypes::getWeaponType](WeaponType#getWeaponType.md)

Player::playerType has been renamed to [Player::getType](Player#getType.md).

The following PlayerTypes have been renamed:
  * NotUsed -> None
  * Human -> Player
  * Rescuable -> RescuePassive
  * Unknown0 -> Unknown4
  * ComputerSlot -> EitherPreferComputer
  * OpenSlot -> EitherPreferHuman
  * ClosedSlot -> Closed
  * Unknown1 -> Observer
  * HumanDefeated -> PlayerLeft
  * ComputerDefeated -> ComputerLeft

Bug Fixes:
  * Fixed a bug where [Game::getLatency](Game#getLatency.md) would return incorrect values for games played on BattleNet.
  * Fixed a bug where [Unit::getGroundWeaponCooldown](Unit#getGroundWeaponCooldown.md) would always return 0 and [Unit::isStartingAttack](Unit#isStartingAttack.md) would always return false and for Protoss Reavers.
  * Fixed a bug with [AIModule::onSendText](AIModule#onSendText.md).
  * Fixed a bug where [AIModule::onUnitDestroy](AIModule#onUnitDestroy.md) was being called for invisible units with complete map info disabled.
  * Fixed a bug where both cheat flags would automatically be enabled when running the AI as a client process.
  * Fixed a bug where [Game::enableFlag](Game#enableFlag.md) would not work when called from a client process.



## Changes from BWAPI Beta 2.7.1 ([r2224](https://code.google.com/p/bwapi/source/detail?r=2224)) to BWAPI Beta 2.7.2 ([r2239](https://code.google.com/p/bwapi/source/detail?r=2239)) ##

Fixed a bug in GameImpl::spriteToUnit which caused the game to crash every once in a while.

## Changes from BWAPI Beta 2.6.1 ([r1914](https://code.google.com/p/bwapi/source/detail?r=1914)) to BWAPI Beta 2.7.1 ([r2224](https://code.google.com/p/bwapi/source/detail?r=2224)) ##

AIs can now connect from another process using BWAPIClient.lib.

New enums:
  * Added enum [EventType](EventType.md)

New classes:
  * Added class [Event](Event.md)
  * Added class [UnitCommand](UnitCommand.md)
  * Added class [UnitCommandType](UnitCommandType.md)

The following functions have been added:
  * Added [AIModule::onSaveGame](AIModule#onSaveGame.md) - called when the user saves the single player match. Currently is triggered twice.
  * Added [Game::getEvents](Game#getEvents.md) - returns the set of events for the frame
  * Added [Game::indexToUnit](Game#indexToUnit.md) - returns the Unit currently at the given index in Starcraft's internal Unit table. Only available when the Complete Map Information flag is enabled.
  * Added [Game::isInGame](Game#isInGame.md) - returns true if Broodwar is currently in a match
  * Added [Unit::isAttacking](Unit#isAttacking.md) - returns true if the unit is attacking. Does not yet work for siege tanks or goliaths.
  * Added [Unit::isVisible(Player\* player)](Unit#isVisible.md) - returns true if the given player can see the given unit. Only available in replays or if the complete map information flag has been enabled.
  * Added [Unit::issueCommand](Unit#issueCommand.md) - general purpose function to issue any valid unit command.

All member functions of Race, TechType, UnitType, UpgradeType, WeaponType now return other objects by value instead of by pointer. For example [TechType::whatResearches](TechType#whatResearches.md) returns a UnitType object rather than a const pointer to a UnitType object.

The following [Orders](Orders.md) have been renamed:
  * Nothing1 -> UnusedNothing
  * Powerup1 -> UnusedPowerup
  * Nothing2 -> Nothing
  * RallyPoint1 -> RallyPointUnit
  * RallyPoint2 -> RallyPointTile
  * Morph1 -> ZergUnitMorph
  * Morph2 -> ZergBuildingMorph
  * BuildSelf1 -> TerranBuildSelf
  * Build5 -> BuildNydusExit
  * Enternyduscanal -> EnterNydusCanal
  * BuildSelf2 -> ProtossBuildSelf
  * CarrierIgnore1 -> ReaverCarrierMove
  * HoldPosition1 -> CarrierHoldPosition
  * ReaverHold -> ReaverHoldPosition
  * RechargeShields1 -> RechargeShieldsUnit
  * Rechargeshields2 -> RechargeShieldsBattery
  * BuildingLiftoff -> BuildingLiftOff
  * DroneLiftoff -> DroneLiftOff
  * Liftoff -> LiftingOff
  * Harvest5 -> Interrupted
  * Pickup1 -> PickupIdle
  * Pickup2 -> PickupTransport
  * Pickup3 -> PickupBunker
  * Powerup2 -> PowerupIdle
  * HoldPosition2 -> HoldPosition
  * HoldPosition3 -> QueenHoldPosition
  * HoldPosition4 -> SuicideHoldPosition

Bug Fixes:
  * Fixed a bug where [Unit::getGroundWeaponCooldown](Unit#getGroundWeaponCooldown.md) would always return 0 for Siege Tanks and Goliaths.
  * Fixed a bug where [Unit::getAirWeaponCooldown](Unit#getAirWeaponCooldown.md) would always return 0 for Goliaths.
  * Fixed a bug with [Unit::isConstructing](Unit#isConstructing.md) - now also returns true when the unit's order is TerranBuildSelf, ProtossBuildSelf, ZergBuildSelf, BuildNydusExit, and BuildAddon.
  * Fixed a bug with [Unit::isIdle](Unit#isIdle.md) - now also returns true when the unit's order is Reaver, Neutral, TowerGuard, and Burrowed.
  * Fixed a bug with [Unit::isMorphing](Unit#isMorphing.md) - now also returns true when the unit's order is ZergBirth.
  * Fixed a bug where [Unit::isTraining](Unit#isTraining.md) - would return true for morphing hatcheries, lairs, and hives.
  * Fixed a bug where [Unit::useTech](Unit#useTech.md) would not work for Archon\_Warp or Dark\_Archon\_Meld.
  * Fixed a bug where [Game::canBuildHere](Game#canBuildHere.md) would return true for refineries over geysers that already have refineries on them.
  * Fixed a bug where [Game::setScreenPosition](Game#setScreenPosition.md) would crash the game if given a position with negative coordinate values.
  * Fixed a bug where [Game::isBuildable](Game#isBuildable.md) would return true for the inaccessible row of tiles at the bottom of the map.
  * Fixed a bug where [Game::isWalkable](Game#isWalkable.md) would return true for the four inaccessible rows of tiles at the bottom of the map.
  * Fixed a bug where [UnitType::maxGroundHits](UnitType#maxGroundHits.md) would return 0 for Terran Siege Tank Siege Mode, Terran Siege Tank Tank Mode, and Terran Goliath.
  * Fixed a bug where [UnitType::maxAirHits](UnitType#maxAirHits.md) would return 0 for Terran Goliath.

## Changes from BWAPI Beta 2.6 ([r1910](https://code.google.com/p/bwapi/source/detail?r=1910)) to BWAPI Beta 2.6.1 ([r1914](https://code.google.com/p/bwapi/source/detail?r=1914)) ##

  * Added [Unit::getID](Unit#getID.md) - returns a unique ID for the unit.
  * Fixed a crash inadvertently introduced in BWAPI Beta 2.6 related to the new mouse and key state functionality.

## Changes from BWAPI Beta 2.5 ([r1830](https://code.google.com/p/bwapi/source/detail?r=1830)) to BWAPI Beta 2.6 ([r1910](https://code.google.com/p/bwapi/source/detail?r=1910)) ##

  * Added [Unit::getLarva](Unit#getLarva.md) - returns a set of 0, 1, 2, or 3 larva units that have spawned from the given Hatchery, Lair, or Hive.
  * Added [Unit::getHatchery](Unit#getHatchery.md) - returns the Hatchery, Lair, or Hive that spawned the given larva. Returns NULL if the unit is not a Zerg Larva.
  * Added [Unit::returnCargo](Unit#returnCargo.md) - returns the worker's cargo (minerals/gas) to a nearby resource depot. Works the same way as the "Return Cargo" button in the Starcraft GUI.
  * Added [Position::getApproxDistance](Misc#Position.md) - an approximate distance function similar to the one starcraft uses.
  * Added [Player::isDefeated](Player#isDefeated.md) - returns true if the player has been defeated
  * Added [Player::isVictorious](Player#isVictorious.md) - returns true if the player has achieved victory.
  * Added [Game::getMousePosition](Game#getMousePosition.md) - returns the position of the mouse on the screen.
  * Added [Game::getScreenPosition](Game#getScreenPosition.md) - returns the position of the screen on the map.
  * Added [Game::setScreenPosition](Game#setScreenPosition.md) - moves the screen to the given position on the map.
  * Added [Game::pingMinimap](Game#pingMinimap.md) - pings the given position on the minimap.
  * Added [Game::getMouseState](Game#getMouseState.md) - returns true if the specified [MouseButton](Input#MouseButton.md) is pressed
  * Added [Game::getKeyState](Game#getKeyState.md) - returns true if the specified [Key](Input#Key.md) is pressed

The following functions have changed in functionality:

  * [AIModule::onEnd](AIModule#onEnd.md) is now called before any user interaction at the end of games and replays.
  * [Game::getFrameCount](Game#getFrameCount.md) no longer increases while the game is paused, however [AIModule::onFrame](AIModule#onFrame.md) is still called.
  * [Unit::getRemainingTrainTime](Unit#getRemainingTrainTime.md) now returns the number of frames until the next larva spawns at the given Hatchery, Lair, or Hive. Works as before on other unit types.
  * [Unit::getDistance(Unit\* target)](Unit#getDistance.md) now computes the distance between units more similar to the way starcraft computes distance between units when determining if a unit is in attack range.
  * [Unit::getDefenseMatrixPoints](Unit#getDefenseMatrixPoints.md) now returns actual defense matrix hit points (not multiplied by 256).

Bug fixes:

  * Fixed a bug where scourge that suicide into other units would not produce an [AIModule::onUnitDestroy](AIModule#onUnitDestroy.md) message.
  * Fixed a bug where [Game::canUpgrade](Game#canUpgrade.md) would sometimes return true even though the player did not have enough resources.
  * Fixed a bug where [Unit::cancelTrain](Unit#cancelTrain.md) would not cancel Terran Nuclear Missiles when called on a Terran Nuclear Missile Silo.
  * Fixed a bug where [Unit::isTraining](Unit#isTraining.md) would return false when called on a Terran Nuclear Missile Silo training a Terran Nuclear Missile.
  * Fixed a bug where [Unit::getTrainingQueue](Unit#getTrainingQueue.md) would return and empty list when called on a Terran Nuclear Missile Silo training a Terran Nuclear Missile.

## Changes from BWAPI Beta 2.4 ([r1689](https://code.google.com/p/bwapi/source/detail?r=1689)) to BWAPI Beta 2.5 ([r1830](https://code.google.com/p/bwapi/source/detail?r=1830)) ##

  * Added a logging option to bwapi.ini - by default it is set to off.
  * Added [TechType](TechType.md)::[getRace](TechType#getRace.md) (the function was declared before but not actually implemented).
  * Added [Unit](Unit.md)::[getBuildType](Unit#getBuildType.md) - returns the building type a worker is about to construct. If the unit is a morphing Zerg unit or an incomplete building, this returns the UnitType the unit is about to become upon completion.

  * Fixed TechTypes::Restoration.whatResearches() so that it now returns UnitTypes::Terran\_Academy.
  * Fixed a bug where [Game](Game.md)::[canBuildHere](Game#canBuildHere.md) would return true even when a nexus/command center/hatchery was too close to invisible minerals/geysers. The function now uses static mineral and geyser data and assumes mineral fields exist unless it can see the build tile where the mineral is supposed to be, and cannot see the mineral unit.
  * Fixed a bug where [Unit](Unit.md)::[isIdle](Unit#isIdle.md) would return false after a worker failed to start construction of a building.
  * Fixed a bug where using Siege Tanks would cause the game to crash.
  * Fixed a bug where BWAPI would crash on game end if a player left during the game.
  * Fixed a bug where [Unit](Unit.md)::[isGatheringGas](Unit#isGatheringGas.md) would sometimes return false for drones harvesting gas into a morphing Hatchery.
  * Fixed a bug where chat messages in multiplayer games would either appear garbled or not show at all.

## Changes from BWAPI Beta 2.3 ([r1610](https://code.google.com/p/bwapi/source/detail?r=1610)) to BWAPI Beta 2.4 ([r1689](https://code.google.com/p/bwapi/source/detail?r=1689)): ##

  * Added [AttackType](AttackType.md) class, however this won't be of much use until the Attack class is implemented (which will let AI Modules "see" projectiles, bullets, psi storms, lurker attacks, etc).
  * Added [Game::isExplored](Game#isExplored.md) - returns true for tiles that are visible or were visible at some point earlier in the match.
  * Added [Unit::isBeingGathered](Unit#isBeingGathered.md) - returns true for mineral patches and the three types of refineries when a unit is gathering from it.

  * Renamed Game::buildable to [Game::isBuildable](Game#isBuildable.md)
  * Renamed Game::walkable to [Game::isWalkable](Game#isWalkable.md)
  * Renamed Game::visible to [Game::isVisible](Game#isVisible.md)
  * Renamed Game::groundHeight to [Game::getGroundHeight](Game#getGroundHeight.md)
  * Added [TilePosition](Misc#TilePosition.md) versions of [Game::isBuildable](Game#isBuildable.md), [Game::isVisible](Game#isVisible.md), [Game::hasCreep](Game#hasCreep.md), and [Game::hasPower](Game#hasPower.md).

The following functions have changed in functionality:

  * [UnitType::seekRange](UnitType#seekRange.md) now returns the seek range in pixels.
  * [UnitType::sightRange](UnitType#sightRange.md) now returns the sight range in pixels.
  * [UnitType::maxHitPoints](UnitType#maxHitPoints.md) now returns actual max hit points (not multiplied by 256).
  * [Unit::getHitPoints](Unit#getHitPoints.md) now returns actual current hit points (not multiplied by 256).
  * [Unit::getShields](Unit#getShields.md) now returns actual current shields (not multiplied by 256).
  * [Unit::getEnergy](Unit#getEnergy.md) now returns actual current energy (not multiplied by 256).
  * [UnitType::canAttack](UnitType#canAttack.md) now returns false for overlords, dropships, and other types of units that cannot attack.
  * [Player::hasResearched](Player#hasResearched.md) now returns true for abilities that the player has researched by default, such as Scanner Sweep.
  * [Game::getFrameCount](Game#getFrameCount.md) now counts from 0. So the first frame is frame 0.
  * [Game::sendText](Game#sendText.md) now processes most cheat codes in single player games. For example, typing Broodwar->sendText("black sheep wall") will reveal the entire map.

Bug fixes:

  * Fixed a bug where [Game::isVisible](Game#isVisible.md) would crash the program when called during a replay.
  * Fixed a bug where [Unit::setRallyPosition](Unit#setRallyPosition.md) and [Unit::setRallyUnit](Unit#setRallyUnit.md) would not execute properly.
  * Fixed a bug where [Unit::patrol](Unit#patrol.md) would appear to change the position of the unit to the target position.
  * Fixed a bug where [Unit::isStartingAttack](Unit#isStartingAttack.md) would always be false for certain types of units, even when they were attacking.
  * Fixed a bug where scanner sweep (and possibly other tech types that don't need to be researched) would not work.
  * Fixed a bug where [AIModule::onFrame](AIModule#onFrame.md) would be called twice on the first frame.
  * Fixed a bug where [Unit::train](Unit#train.md) would not allow more than one unit to be added to the training queue.
  * Fixed a bug where [AIModule::onUnitDestroy](AIModule#onUnitDestroy.md) would not be called for units loaded into dropships/shuttles/overlords when the transport unit was destroyed.
  * Fixed [UnitType::topSpeed](UnitType#topSpeed.md), [Unit::getVelocityX](Unit#getVelocityX.md), and [Unit::getVelocityY](Unit#getVelocityY.md). Everything should now be in pixels per frame.

## Changes from BWAPI Beta 2.2 ([r1491](https://code.google.com/p/bwapi/source/detail?r=1491)) to BWAPI Beta 2.3 ([r1610](https://code.google.com/p/bwapi/source/detail?r=1610)): ##

  * bwapi.ini file no longer accepts curly brace definitions.

The following functions have been added:

  * [AIModule::onUnitRenegade](AIModule#onUnitRenegade.md) - called when a unit changes ownership.
  * [AIModule::onPlayerLeft](AIModule#onPlayerLeft.md) - called when a player leaves the game.
  * [AIModule::onNukeDetect](AIModule#onNukeDetect.md) - called when a nuclear launch has been detected. If the target position is visible at the time of launch (or complete map information is enabled), the target position is provided.
  * [Game::restartGame](Game#restartGame.md) - restarts the single player match.
  * [Unit::getUpgradeLevel](Unit#getUpgradeLevel.md) - returns the upgrade level of the unit.
  * [Unit::getVelocityX](Unit#getVelocityX.md) - returns the x component of velocity in pixels per frame.
  * [Unit::getVelocityY](Unit#getVelocityY.md) - returns the y component of velocity in pixels per frame.
  * [Player::leftGame](Player#leftGame.md) - returns true if the player has left the game.
  * [UnitType::upgrades](UnitType#upgrades.md) - returns the set of upgrades that can affect this UnitType.
  * [UpgradeType::whatUses](UpgradeType#whatUses.md) - returns the set of unit types that are affected by this UpgradeType.

The following functions have been renamed:

  * Unit::getCurrentDirection has been renamed to [Unit::getAngle](Unit#getAngle.md)

  * Player::researching has been renamed to [Player::isResearching](Player#isResearching.md)
  * Player::researched has been renamed to [Player::hasResearched](Player#hasResearched.md)
  * Player::upgrading has been renamed to [Player::isUpgrading](Player#isUpgrading.md)
  * Player::upgradeLevel has been renamed to [Player::getUpgradeLevel](Player#getUpgradeLevel.md)

  * Game::drawMapBox has been renamed to [Game::drawBoxMap](Game#drawBox.md)
  * Game::drawMouseBox has been renamed to [Game::drawBoxMouse](Game#drawBox.md)
  * Game::drawScreenBox has been renamed to [Game::drawBoxScreen](Game#drawBox.md)

  * Game::drawMapTriangle has been renamed to [Game::drawTriangleMap](Game#drawTriangle.md)
  * Game::drawMouseTriangle has been renamed to [Game::drawTriangleMouse](Game#drawTriangle.md)
  * Game::drawScreenTriangle has been renamed to [Game::drawTriangleScreen](Game#drawTriangle.md)

  * Game::drawMapCircle has been renamed to [Game::drawCircleMap](Game#drawCircle.md)
  * Game::drawMouseCircle has been renamed to [Game::drawCircleMouse](Game#drawCircle.md)
  * Game::drawScreenCircle has been renamed to [Game::drawCircleScreen](Game#drawCircle.md)

  * Game::drawMapEllipse has been renamed to [Game::drawEllipseMap](Game#drawEllipse.md)
  * Game::drawMouseEllipse has been renamed to [Game::drawEllipseMouse](Game#drawEllipse.md)
  * Game::drawScreenEllipse has been renamed to [Game::drawEllipseScreen](Game#drawEllipse.md)

  * Game::drawMapDot has been renamed to [Game::drawDotMap](Game#drawDot.md)
  * Game::drawMouseDot has been renamed to [Game::drawDotMouse](Game#drawDot.md)
  * Game::drawScreenDot has been renamed to [Game::drawDotScreen](Game#drawDot.md)

  * Game::drawMapLine has been renamed to [Game::drawLineMap](Game#drawLine.md)
  * Game::drawMouseLine has been renamed to [Game::drawLineMouse](Game#drawLine.md)
  * Game::drawScreenLine has been renamed to [Game::drawLineScreen](Game#drawLine.md)

When complete map information is disabled, the following function no longer provide information about enemy units, regardless of visibility:

  * [Unit::isHallucination](Unit#isHallucination.md)
  * [Unit::isLoaded](Unit#isLoaded.md)
  * [Unit::getTrainingQueue](Unit#getTrainingQueue.md)
  * [Unit::getTransport](Unit#getTransport.md)
  * [Unit::getLoadedUnits](Unit#getLoadedUnits.md)
  * [Unit::getScarabCount](Unit#getScarabCount.md)
  * [Unit::getSpiderMineCount](Unit#getSpiderMineCount.md)
  * [Unit::getTech](Unit#getTech.md)
  * [Unit::getUpgrade](Unit#getUpgrade.md)
  * [Unit::getRemainingResearchTime](Unit#getRemainingResearchTime.md)
  * [Unit::getRemainingUpgradeTime](Unit#getRemainingUpgradeTime.md)
  * [Unit::isResearching](Unit#isResearching.md)
  * [Unit::isUpgrading](Unit#isUpgrading.md)
  * [Unit::getRallyPosition](Unit#getRallyPosition.md)
  * [Unit::getRallyUnit](Unit#getRallyUnit.md)

To determine if a visible enemy unit is busy researching or upgrading, use [Unit::isIdle](Unit#isIdle.md).

The following functions have changed in functionality:
  * [Unit::getAngle](Unit#getAngle.md) (renamed from Unit::getCurrentDirection) now returns the angle of the unit in radians.
  * [UnitType::topSpeed](UnitType#topSpeed.md) now returns the correct top speed of the UnitType in pixels per frame.
  * [Game::leaveGame](Game#leaveGame.md) now goes to the after-match stats screen, rather than going to the main menu.
  * [AIModule::onEnd](AIModule#onEnd.md) is now called with an argument isWinner, which is true if the ai module has won the game.

Bug fixes:

  * Fixed a bug where [Game::drawTextMap](Game#drawText.md) would use screen coordinates. It now uses map coordinates as expected.
  * Fixed a bug where attackUnit, rightClick, and other orders which take a target unit would not target the right unit in the game.
  * Fixed a bug where [Unit::isGatheringGas](Unit#isGatheringGas.md) and [Unit::isGatheringMinerals](Unit#isGatheringMinerals.md) would sometimes return false, even though the unit was gathering gas/minerals.
  * Fixed a bug where getUnits() functions would return an incomplete list of units when called from onUnitMorph, onUnitShow, or onUnitHide.

Other changes:

  * Added documentation of how to draw text in different colors.
  * Increased speed of multiplayer menus.

## Changes from BWAPI Beta 2.1 ([r1416](https://code.google.com/p/bwapi/source/detail?r=1416)) to BWAPI Beta 2.2 ([r1491](https://code.google.com/p/bwapi/source/detail?r=1491)): ##

The following functions have been added:

  * [AIModule::onUnitShow](AIModule#onUnitShow.md)
  * [AIModule::onUnitHide](AIModule#onUnitHide.md)
  * [AIModule::onUnitMorph](AIModule#onUnitMorph.md)

  * [Unit::getInitialType](Unit#getInitialType.md)
  * [Unit::getInitialPosition](Unit#getInitialPosition.md)
  * [Unit::getInitialTilePosition](Unit#getInitialTilePosition.md)
  * [Unit::getInitialResources](Unit#getInitialResources.md)
  * [Unit::getInitialHitPoints](Unit#getInitialHitPoints.md)

  * [Game::isMultiplayer](Game#isMultiplayer.md)
  * [Game::isPaused](Game#isPaused.md)

  * [Game::getStaticMinerals](Game#getStaticMinerals.md)
  * [Game::getStaticGeysers](Game#getStaticGeysers.md)
  * [Game::getStaticNeutralUnits](Game#getStaticNeutralUnits.md)

  * [Game::drawTextMap](Game#drawText.md)
  * [Game::drawTextMouse](Game#drawText.md)
  * [Game::drawTextScreen](Game#drawText.md)

  * [Game::drawMapBox](Game#drawBox.md)
  * [Game::drawMouseBox](Game#drawBox.md)
  * [Game::drawScreenBox](Game#drawBox.md)

  * [Game::drawMapTriangle](Game#drawTriangle.md)
  * [Game::drawMouseTriangle](Game#drawTriangle.md)
  * [Game::drawScreenTriangle](Game#drawTriangle.md)

  * [Game::drawMapCircle](Game#drawCircle.md)
  * [Game::drawMouseCircle](Game#drawCircle.md)
  * [Game::drawScreenCircle](Game#drawCircle.md)

  * [Game::drawMapEllipse](Game#drawEllipse.md)
  * [Game::drawMouseEllipse](Game#drawEllipse.md)
  * [Game::drawScreenEllipse](Game#drawEllipse.md)

  * [Game::drawMapDot](Game#drawDot.md)
  * [Game::drawMouseDot](Game#drawDot.md)
  * [Game::drawScreenDot](Game#drawDot.md)

  * [Game::drawMapLine](Game#drawLine.md)
  * [Game::drawMouseLine](Game#drawLine.md)
  * [Game::drawScreenLine](Game#drawLine.md)

The following functions have changed in functionality:

  * [Unit::exists](Unit#exists.md) - now returns false for inaccessible units, even if they exist.
  * [AIModule::onUnitCreate](AIModule#onUnitCreate.md) is no longer called for invisible units when complete map information is disabled.

The following functions have been renamed:

  * Game::text has been renamed to [Game::drawText](Game#drawText.md)
  * Game::inReplay has been renamed to [Game::isReplay](Game#isReplay.md)
  * AIModule::onAddUnit has been renamed to [AIModule::onUnitCreate](AIModule#onUnitCreate.md)
  * AIModule::onRemoveUnit has been renamed to [AIModule::onUnitDestroy](AIModule#onUnitDestroy.md)

Other changes:

  * BWAPI no longer crashes on replays.

## Changes from BWAPI Beta 2 ([r1400](https://code.google.com/p/bwapi/source/detail?r=1400)) to BWAPI Beta 2.1 ([r1416](https://code.google.com/p/bwapi/source/detail?r=1416)): ##

  * Fixed a bug that produced phantom marines. An internal unit set in BWAPI was not being reset between matches, so units that existed in a previous match appeared to exist in the next game as phantom marines. Retrieving information from these non existant marines and/or issuing orders to them may have also caused Broodwar to crash.

## Changes from BWAPI Beta to BWAPI Beta 2 ([r1400](https://code.google.com/p/bwapi/source/detail?r=1400)): ##

The following functions have been added:

  * [Unit::isCarryingGas](Unit#isCarryingGas.md)
  * [Unit::isCarryingMinerals](Unit#isCarryingMinerals.md)
  * [Unit::isDefenseMatrixed](Unit#isDefenseMatrixed.md)
  * [Unit::isEnsnared](Unit#isEnsnared.md)
  * [Unit::isIrradiated](Unit#isIrradiated.md)
  * [Unit::isMaelstrommed](Unit#isMaelstrommed.md)
  * [Unit::isParasited](Unit#isParasited.md)
  * [Unit::isPlagued](Unit#isPlagued.md)
  * [Unit::isStimmed](Unit#isStimmed.md)

  * [Game::leaveGame](Game#leaveGame.md) - replaces Game::surrender and now works correctly.
  * [Game::setLocalSpeed](Game#setLocalSpeed.md) - lets AIs increase the speed in single player games.

Other changes:

  * Fixed crash due to null sprite pointer in Broodwar memory
  * Minor update of UnitType information for spells and Terran Nuclear Missile.
  * Minor update of description text shown in Chaoslauncher text box.
  * Example AI Module compiles much faster due to new compile of BWTA.lib.