# Class Diagram #

Here is the class diagram of BWAPI: [class diagram](http://i.imgur.com/lppnE.png). Not all functions are shown for each class, and some classes are not included in the diagram (like Position).

# Creating an AI #

You can either create an AI as an [AI Module](AIModule.md) DLL that gets loaded into Starcraft at the start of a match, or as a stand-alone client process that communicates with BWAPI via shared memory. An example of each of these is included in each release of BWAPI.

# Main Classes #

The 5 main BWAPI classes that get information from Starcraft are [Game](Game.md), [Force](Force.md), [Player](Player.md), [Unit](Unit.md), and [Bullet](Bullet.md).

[Game](Game.md) is your primary interface to BWAPI. Using this class you can get sets of forces, players, units, and bullets. You can also issue commands to the game to pause the game, move the screen, and do other things.

[Force](Force.md) usually not very useful except in certain game modes. Sometimes forces correspond to teams, but not always. This is the least used class that interacts with Broodwar.

[Player](Player.md) can be used to get information about each player in the current match.

[Unit](Unit.md) can be used to get information about and control individual units.

[Bullet](Bullet.md) can be used to get information about individual bullet objects. Not all attack animations generate bullet objects.

# Cheat flags #

There are two cheat flags, each of which are disabled by default:

  * CompleteMapInformation - Enable to make all units accessible, not just visible units.
  * UserInput - Enable to get information from the user (what units are selected, chat messages the user enters, etc)

# The four tiers of unit accessibility #

Each unit in the game will be at one of the following levels of accessibility, depending on a number of factors.

## 1) Full Accessibility ##

All of units owned by the BWAPI player/AI are fully accessible all of the time while they are alive. If the Complete Map Information flag is enabled, or if the match is a replay, then all of the units in the match will be fully accessible, not just the units owned by [self()](Game#self.md).

If the Complete Map Information flag is disabled and the match is not a replay, then neutral and enemy units will fall into one of the remaining tiers of accessibility.

Frame 0 notes:

  * On frame 0, all neutral units will have full accessibility, regardless of Compelete Map Information status.

  * If you enabled the Complete Map Information flag on frame 0, enemy units will not become fully accessible until frame 1.

## 2) Normal Accessibility ##

When complete map information is disabled, then all visible and detected enemy units will have normal accessibility. This includes all of the attributes in full accessibility EXCEPT for the following:

  * [getScarabCount](Unit#getScarabCount.md)
  * [getSpiderMineCount](Unit#getSpiderMineCount.md)
  * [getBuildType](Unit#getBuildType.md)
  * [getTrainingQueue](Unit#getTrainingQueue.md)
  * [getTech](Unit#getTech.md)
  * [getUpgrade](Unit#getUpgrade.md)
  * [getRemainingBuildTime](Unit#getRemainingBuildTime.md)
  * [getRemainingTrainTime](Unit#getRemainingTrainTime.md)
  * [getRemainingResearchTime](Unit#getRemainingResearchTime.md)
  * [getRemainingUpgradeTime](Unit#getRemainingUpgradeTime.md)
  * [getRallyPosition](Unit#getRallyPosition.md)
  * [getRallyUnit](Unit#getRallyUnit.md)
  * [getTransport](Unit#getTransport.md)
  * [getCarrier](Unit#getCarrier.md)
  * [getHatchery](Unit#getHatchery.md)
  * [hasNuke](Unit#hasNuke.md)
  * [isHallucination](Unit#isHallucination.md)

These inaccessible functions will just return 0/NULL/false/etc, depending on the return type.

## 3) Partial Accessibility ##

Units that return true for [Unit::isVisible](Unit#isVisible.md) but false for [Unit::isDetected](Unit#isDetected.md) are partially accessible.

Cloaked enemy that are not covered by fog of war will return true for [Unit::isVisible](Unit#isVisible.md), and thus always be at least partially visible. Burrowed enemy units that are not covered by fog of war will return true for [Unit::isVisible](Unit#isVisible.md) only if they are attacking or detected (by a Science Vessel or other detection unit).

Partial accessibility includes access to the following functions:
  * [getID](Unit#getID.md)
  * [getPlayer](Unit#getPlayer.md)
  * [getType](Unit#getType.md)
  * [getPosition](Unit#getPosition.md)
  * [getTilePosition](Unit#getTilePosition.md)
  * [getAngle](Unit#getAngle.md)
  * [getVelocityX](Unit#getVelocityX.md)
  * [getVelocityY](Unit#getVelocityY.md)
  * [getDistance](Unit#getDistance.md)
  * [getGroundWeaponCooldown](Unit#getGroundWeaponCooldown.md)
  * [getAirWeaponCooldown](Unit#getAirWeaponCooldown.md)
  * [getSpellCooldown](Unit#getSpellCooldown.md)
  * [exists](Unit#exists.md)
  * [isAttacking](Unit#isAttacking.md)
  * [isBurrowed](Unit#isBurrowed.md)
  * [isCloaked](Unit#isCloaked.md)
  * [isCompleted](Unit#isCompleted.md)
  * [isDetected](Unit#isDetected.md) - returns false
  * [isMoving](Unit#isMoving.md)
  * [isSieged](Unit#isSieged.md)
  * [isStartingAttack](Unit#isStartingAttack.md)
  * [isVisible](Unit#isVisible.md) - returns true

The initial value functions are also still accessible at this level, however I don't think its possible for neutral units (like mineral patches) to cloak, so I don't think they would be of any use here.

Note: [AIModule::onUnitShow](AIModule#onUnitShow.md) and [AIModule::onUnitHide](AIModule#onUnitHide.md) occur when the unit switches between partial accessibility and no accessibility. If Complete Map Info is disabled, then [AIModule::onUnitDiscover](AIModule#onUnitDiscover.md) and [AIModule::onUnitEvade](AIModule#onUnitEvade.md) also occur during this transition.

## 4) No Accessibility ##

Units that are dead will have no accessibility. If Complete Map Info is disabled, then units shrouded by Fog of War will also have no accessibility, even if they are still alive.

The initial value functions, however, are always accessible at all levels:
  * [getInitialType](Unit#getInitialType.md)
  * [getInitialPosition](Unit#getInitialPosition.md)
  * [getInitialTilePosition](Unit#getInitialTilePosition.md)
  * [getInitialHitPoints](Unit#getInitialHitPoints.md)
  * [getInitialResources](Unit#getInitialResources.md)

These only apply for neutral units that existed at the start of the match are are useful for getting general/static knowledge of the map even when complete map info is disabled. To obtain this static map info use these functions on the units returned by:
  * [Game::getStaticMinerals](Game#getStaticMinerals.md)
  * [Game::getStaticGeysers](Game#getStaticGeysers.md)
  * [Game::getStaticNeutralUnits](Game#getStaticNeutralUnits.md)