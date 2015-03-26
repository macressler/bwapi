Class header file: [BWAPI/Unit.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/Unit.h)

The Unit class is used to get information about individual units as well as issue orders to units. Each unit in the game has a unique Unit object, and Unit objects are not deleted until the end of the match (so you don't need to worry about unit pointers becoming invalid).

Note: There are 4 tiers of unit accessibility that determine which functions AIs will have access to. If the Complete Map Information cheat flag is enabled, you have perfect information of every unit. Otherwise, the functions that will return information will be limited depending on the unit's visibility. To learn more about unit accessibility, read the [BWAPI Overview](BWAPIOverview.md) page.



# Methods #

## getID ##
int getID() const;

Returns a unique ID for this unit.

## getReplayID ##
int getReplayID() const;

Returns the ID of the unit from a replay file's actions. This is only available when CompleteMapInformation is enabled.

## getPlayer ##
[Player](Player.md)`*` getPlayer() const;

Returns a pointer to the player that owns this unit.

## getType ##
[UnitType](UnitType.md) getType() const;

Returns the current type of the unit.

## getPosition ##
[Position](Misc#Position.md) getPosition() const;

Returns the position of the unit on the map.

## getRegion ##
[Region](Region.md) `*`getRegion() const;

Returns the [Region](Region.md) that the unit is currently in.

## getTilePosition ##
[TilePosition](Misc#TilePosition.md) getTilePosition() const;

Returns the build tile position of the unit on the map. Useful if the unit is a building. The tile position is of the top left corner of the building.

## getLeft ##
int getLeft() const;

Returns the x position for the unit's left collision boundry.

## getTop ##
int getTop() const;

Returns the y position for the unit's top collision boundry.

## getRight ##
int getRight() const;

Returns the x position for the unit's right collision boundry.

## getBottom ##
int getBottom() const;

Returns the y position for the unit's bottom collision boundry.

## getAngle ##
double getAngle() const;

Returns the direction the unit is facing, measured in radians. An angle of 0 means the unit is facing east.

## getVelocityX ##
double getVelocityX() const;

Returns the x component of the unit's velocity, measured in pixels per frame.

## getVelocityY ##
double getVelocityY() const;

Returns the y component of the unit's velocity, measured in pixels per frame.

## getHitPoints ##
int getHitPoints() const;

Returns the unit's current amount of hit points.

## getShields ##
int getShields() const;

Returns the unit's current amount of shields.

## getEnergy ##
int getEnergy() const;

Returns the unit's current amount of energy.

## getResources ##
int getResources() const;

Returns the unit's current amount of containing resources. Useful for determining how much minerals are left in a mineral patch, or how much gas is left in a geyser (can also be called on a refinery/assimilator/extractor).

## getResourceGroup ##
int getResourceGroup() const;

Returns the group index of a resource. Can be used to identify which resources belong to an expansion.

## getDistance ##
int getDistance([Unit](Unit.md)`*` target) const;

Returns the edge-to-edge distance between the current unit and the target unit.

int getDistance([Position](Misc#Position.md) target) const;

Returns the distance from the edge of the current unit to the target position.

## hasPath ##
bool hasPath([Unit](Unit.md)`*` target) const;

bool hasPath([Position](Misc#Position.md) target) const;

Returns true if the target is on the same island as the unit, and false if the unit supposedly can't reach the destination target. This is based on static map data.

See also: [Game::hasPath](Game#hasPath.md)

## getLastCommandFrame ##
int getLastCommandFrame() const;

Returns the frame of the last successful command sent using BWAPI. For example, issuing an Attack command with BWAPI will record the frame it was issued in, and you retrieve the frame with this.

## getLastCommand ##
[UnitCommand](UnitCommand.md) getLastCommand() const;

Returns the last successful command sent using BWAPI. For example, issuing a Move command with BWAPI will immediately result in this function returning a Move command (with the same target position).

## getLastAttackingPlayer ##
[Player](Player.md) `*` getLastAttackingPlayer() const;

Returns the last player that attacked this unit, or NULL if it is not applicable.

## setClientInfo ##
void setClientInfo(void`*` clientinfo);

Associates client info with the unit. The client is responsible for the allocation and deallocation of the client info pointer.

## getClientInfo ##
void`*` getClientInfo();

Retrieves the client info that was set by [setClientInfo](#setClientInfo.md). The client is responsible for the allocation and deallocation of the client info pointer.

## getUpgradeLevel ##
int getUpgradeLevel([UpgradeType](UpgradeType.md) upgrade) const;

Returns true if the owner of this player has upgraded the given upgrade type, and this unit is affected by this upgrade.

## getInitialType ##
[UnitType](UnitType.md) getInitialType() const;

Returns the initial type of the unit or Unknown if it wasn't a neutral unit at the beginning of the game.

## getInitialPosition ##
[Position](Misc#Position.md) getInitialPosition() const;

Returns the initial position of the unit on the map, or Positions::Unknown if the unit wasn't a neutral unit at the beginning of the game.

## getInitialTilePosition ##
[TilePosition](Misc#TilePosition.md) getInitialTilePosition() const;

Returns the initial build tile position of the unit on the map, or TilePositions::Unknown if the unit wasn't a neutral unit at the beginning of the game. The tile position is of the top left corner of the building.

## getInitialHitPoints ##
int getInitialHitPoints() const;

Returns the unit's initial amount of hit points, or 0 if it wasn't a neutral unit at the beginning of the game.

## getInitialResources ##
int getInitialResources() const;

Returns the unit's initial amount of containing resources, or 0 if the unit wasn't a neutral unit at the beginning of the game.

## getKillCount ##
int getKillCount() const;

Returns the unit's current kill count.

## getAcidSporeCount ##
int getAcidSporeCount() const;

Returns the unit's acid spore count.

## getInterceptorCount ##
int getInterceptorCount() const;

Returns the number of interceptors the Protoss Carrier has.

## getScarabCount ##
int getScarabCount() const;

Returns the number of scarabs in the Protoss Reaver.

## getSpiderMineCount ##
int getSpiderMineCount() const;

Returns the number of spider mines in the Terran Vulture.

## getGroundWeaponCooldown ##
int getGroundWeaponCooldown() const;

Returns unit's ground weapon cooldown. It is 0 if the unit is ready to attack.

## getAirWeaponCooldown ##
int getAirWeaponCooldown() const;

Returns unit's air weapon cooldown. It is 0 if the unit is ready to attack.

## getSpellCooldown ##
int getSpellCooldown() const;

Returns unit's spell cooldown. It is 0 if the unit is ready to cast a spell.

## getDefenseMatrixPoints ##
int getDefenseMatrixPoints() const;

Returns the remaining hit points of the defense matrix. Initially a defense Matrix has 250 points.

See also: [Unit](Unit.md)::[getDefenseMatrixTimer](Unit#getDefenseMatrixTimer.md), [Unit](Unit.md)::[isDefenseMatrixed](Unit#isDefenseMatrixed.md).

## getDefenseMatrixTimer ##
int getDefenseMatrixTimer() const;

Returns the time until the defense matrix wears off. 0 -> No defense Matrix present.

## getEnsnareTimer ##
int getEnsnareTimer() const;

Returns the time until the ensnare effect wears off. 0 -> No ensnare effect present.

## getIrradiateTimer ##
int getIrradiateTimer() const;

Returns the time until the radiation wears off. 0 -> No radiation present.

## getLockdownTimer ##
int getLockdownTimer() const;

Returns the time until the lockdown wears off. 0 -> No lockdown present.

## getMaelstromTimer ##
int getMaelstromTimer() const;

Returns the time until the maelstrom wears off. 0 -> No maelstrom present.

## getOrderTimer ##
int getOrderTimer() const;

## getPlagueTimer ##
int getPlagueTimer() const;

Returns the time until the plague wears off. 0 -> No plague present.

## getRemoveTimer ##
int getRemoveTimer() const;

Returns the amount of time until the unit is removed, or 0 if the unit does not have a remove timer. Used to determine how much time remains before hallucinated units, dark swarm, etc have until they are removed.

## getStasisTimer ##
int getStasisTimer() const;

Returns the time until the stasis field wears off. 0 -> No stasis field present.

## getStimTimer ##
int getStimTimer() const;

Returns the time until the stimpack wears off. 0 -> No stimpack boost present.

## getBuildType ##
[UnitType](UnitType.md) getBuildType() const;

Returns the building type a worker is about to construct. If the unit is a morphing Zerg unit or an incomplete building, this returns the UnitType the unit is about to become upon completion.

## getTrainingQueue ##
std::list< [UnitType](UnitType.md) > getTrainingQueue() const;

Returns the list of units queued up to be trained.

See also: [Unit](Unit.md)::[train](Unit#train.md), [Unit](Unit.md)::[cancelTrain](Unit#cancelTrain.md), [Unit](Unit.md)::[isTraining](Unit#isTraining.md).

## getTech ##
[TechType](TechType.md) getTech() const;

Returns the tech that the unit is currently researching. If the unit is not researching anything, [TechTypes](TechTypes.md)::None is returned.

See also: [Unit](Unit.md)::[research](Unit#research.md), [Unit](Unit.md)::[cancelResearch](Unit#cancelResearch.md), [Unit](Unit.md)::[isResearching](Unit#isResearching.md), [Unit](Unit.md)::[getRemainingResearchTime](Unit#getRemainingResearchTime.md).

## getUpgrade ##
[UpgradeType](UpgradeType.md) getUpgrade() const;

Returns the upgrade that the unit is currently upgrading. If the unit is not upgrading anything, [UpgradeTypes](UpgradeTypes.md)::None is returned.

See also: [Unit](Unit.md)::[upgrade](Unit#upgrade.md), [Unit](Unit.md)::[cancelUpgrade](Unit#cancelUpgrade.md), [Unit](Unit.md)::[isUpgrading](Unit#isUpgrading.md), [Unit](Unit.md)::[getRemainingUpgradeTime](Unit#getRemainingUpgradeTime.md).

## getRemainingBuildTime ##
int getRemainingBuildTime() const;

Returns the remaining build time of a unit/building that is being constructed.

## getRemainingTrainTime ##
int getRemainingTrainTime() const;

Returns the remaining time of the unit that is currently being trained. If the unit is a Hatchery, Lair, or Hive, this returns the amount of time until the next larva spawns, or 0 if the unit already has 3 larva.

## getRemainingResearchTime ##
int getRemainingResearchTime() const;

Returns the amount of time until the unit is done researching its current tech. If the unit is not researching anything, 0 is returned.

See also: [Unit](Unit.md)::[research](Unit#research.md), [Unit](Unit.md)::[cancelResearch](Unit#cancelResearch.md), [Unit](Unit.md)::[isResearching](Unit#isResearching.md), [Unit](Unit.md)::[getTech](Unit#getTech.md).

## getRemainingUpgradeTime ##
int getRemainingUpgradeTime() const;

Returns the amount of time until the unit is done upgrading its current upgrade. If the unit is not upgrading anything, 0 is returned.

See also: [Unit](Unit.md)::[upgrade](Unit#upgrade.md), [Unit](Unit.md)::[cancelUpgrade](Unit#cancelUpgrade.md), [Unit](Unit.md)::[isUpgrading](Unit#isUpgrading.md), [Unit](Unit.md)::[getUpgrade](Unit#getUpgrade.md).

## getBuildUnit ##
[Unit](Unit.md)`*` getBuildUnit() const;

If the unit is an SCV that is constructing a building, this will return the building it is constructing. If the unit is a Terran building that is being constructed, this will return the SCV that is constructing it.

## getUnitsInRadius ##
std::set<[Unit](Unit.md)`*`>& getUnitsInRadius(int radius) const;

Retrieves the set of all units that are within a certain radius of the unit's bounding box.

See also: [Game::getUnitsInRadius](Game#getUnitsInRadius.md), [Unit::getUnitsInWeaponRange](Unit#getUnitsInWeaponRange.md)

## getUnitsInWeaponRange ##
std::set<[Unit](Unit.md)`*`>& getUnitsInWeaponRange(WeaponType weapon) const;

Retrieves the set of all units that are currently within the given weapon's range.

See also: [Unit::getUnitsInRadius](Unit#getUnitsInRadius.md)

## getTarget ##
[Unit](Unit.md)`*` getTarget() const;

After issuing an order to a target unit, this returns the target that the unit should move to and returns NULL after the unit has reached its target.

See also: [Unit](Unit.md)::[getOrderTarget](Unit#getOrderTarget.md), See also: [Unit](Unit.md)::[isInWeaponRange](Unit#isInWeaponRange.md)

## getTargetPosition ##
[Position](Misc#Position.md) getTargetPosition() const;

Returns the target position the unit is moving to (provided a valid path to the target position exists).

## getOrder ##
[Order](Order.md) getOrder() const;

Returns the [Order](Order.md) that this unit is currently executing.

## getOrderTarget ##
[Unit](Unit.md)`*` getOrderTarget() const;

This is set when your unit has performed an order to a target unit and for targets that are automatically acquired.

See also: [Unit](Unit.md)::[getTarget](Unit#getTarget.md)

## getSecondaryOrder ##
[Order](Order.md) getSecondaryOrder() const;

Returns the secondary [Order](Order.md) that this unit is currently executing.

## getRallyPosition ##
[Position](Misc#Position.md) getRallyPosition() const;

Returns the position the building is rallied to. If the building does not produce units, Positions::None is returned.

An unset rally position will return (0,0).

See also: [Unit](Unit.md)::[setRallyPoint](Unit#setRallyPoint.md), [Unit](Unit.md)::[getRallyUnit](Unit#getRallyUnit.md).

## getRallyUnit ##
[Unit](Unit.md)`*` getRallyUnit() const;

Returns the unit the building is rallied to. If the building is not rallied to any unit, NULL is returned.

See also: [Unit](Unit.md)::[setRallyPoint](Unit#setRallyPoint.md), [Unit](Unit.md)::[getRallyPosition](Unit#getRallyPosition.md).

## getAddon ##
[Unit](Unit.md)`*` getAddon() const;

Returns the add-on of this unit, or NULL if the unit doesn't have an add-on.

## getNydusExit ##
[Unit](Unit.md)`*` getNydusExit() const;

Returns the Nydus Canal unit that is connected to this Nydus Canal, or NULL if the unit doesn't have a connecting Nydus Canal.

## getTransport ##
[Unit](Unit.md)`*` getTransport() const;

Returns the dropship, shuttle, overlord, or bunker that is this unit is loaded in to.

## getLoadedUnits ##
std::set<[Unit](Unit.md)`*`> getLoadedUnits() const;

Returns the set of the units loaded into a Terran Bunker, Terran Dropship, Protoss Shuttle, Protoss Carrier, or Zerg Overlord.

## getCarrier ##
[Unit](Unit.md)`*` getCarrier() const;

Returns the carrier that this unit belongs to, or NULL if this unit is not an Interceptor or if its carrier has recently been destroyed.

## getInterceptors ##
std::set<[Unit](Unit.md)`*`> getInterceptors() const;

Returns the set of interceptors owned by this carrier. The interceptors inside the carrier can be obtained via getLoadedUnits, while the interceptors outside of the carrier is the difference of these two sets.

## getHatchery ##
[Unit](Unit.md)`*` getHatchery() const;

For Zerg Larva, this returns the Hatchery, Lair, or Hive unit this Larva was spawned from. For all other unit types this function returns NULL.

## getLarva ##
std::set<[Unit](Unit.md)`*`> getLarva() const;

Returns the set of larva spawned by this unit. If the unit has no larva, or is not a Hatchery, Lair, or Hive, this function returns an empty set. Equivalent to clicking "Select Larva" from the Starcraft GUI.

## getPowerUp ##
Unit `*`getPowerUp() const;

Returns the powerup a worker is holding (Capture the Flag for example), or NULL if there is none.

## exists ##
bool exists() const;

3 cases to consider:

  * If exists() returns true, the unit exists.
  * If exists() returns false and the unit is owned by self(), then the unit does not exist.
  * If exists() returns false and the unit is not owned by self(), then the unit may or may not exist (for example: an enemy unit outside of the player's vision).

See also: [Unit](Unit.md)::[isVisible](Unit#isVisible.md).

## hasNuke ##
bool hasNuke() const;

Returns true if the unit is a Terran Nuclear Missile Silo and has a Terran Nuclear Missile trained and ready to go.

## isAccelerating ##
bool isAccelerating() const;

Returns true if the unit is currently accelerating.

## isAttacking ##
bool isAttacking() const;

Returns true if the unit is currently attacking.

## isAttackFrame ##
bool isAttackFrame () const;

Returns true if the unit is currently starting an attack or playing an attack animation. Don't issue the unit another command until this returns false or else the next attack sequence may be interrupted.

## isBeingConstructed ##
bool isBeingConstructed() const;

Returns true if the unit is being constructed. Always true for incomplete Protoss and Zerg buildings, and true for incomplete Terran buildings that have an SCV constructing them. If the SCV halts construction, isBeingConstructed will return false.

See also: [Unit](Unit.md)::[build](Unit#build.md), [Unit](Unit.md)::[cancelConstruction](Unit#cancelConstruction.md), [Unit](Unit.md)::[haltConstruction](Unit#haltConstruction.md), [Unit](Unit.md)::[isConstructing](Unit#isConstructing.md).

## isBeingGathered ##
bool isBeingGathered() const;

Returns true if the unit is a mineral patch or refinery that is being gathered.

## isBeingHealed ##
bool isBeingHealed() const;

Returns true if the unit is currently being healed by a Terran Medic.

## isBlind ##
bool isBlind() const;

Returns true if the unit is currently blind from a Medic's Optical Flare.

## isBraking ##
bool isBraking() const;

Returns true if the unit is currently braking/slowing down.

## isBurrowed ##
bool isBurrowed() const;

Returns true if the unit is a Zerg unit that is current burrowed.

See also: [Unit](Unit.md)::[burrow](Unit#burrow.md), [Unit](Unit.md)::[unburrow](Unit#unburrow.md).

## isCarryingGas ##
bool isCarryingGas() const;

Returns true if the unit is a worker that is carrying gas.

See also: [Unit](Unit.md)::[returnCargo](Unit#returnCargo.md), [Unit](Unit.md)::[isGatheringGas](Unit#isGatheringGas.md).

## isCarryingMinerals ##
bool isCarryingMinerals() const;

Returns true if the unit is a worker that is carrying minerals.

See also: [Unit](Unit.md)::[returnCargo](Unit#returnCargo.md), [Unit](Unit.md)::[isGatheringMinerals](Unit#isGatheringMinerals.md).

## isCloaked ##
bool isCloaked() const;

Returns true if the unit is cloaked.

See also: [Unit](Unit.md)::[cloak](Unit#cloak.md), [Unit](Unit.md)::[decloak](Unit#decloak.md).

## isCompleted ##
bool isCompleted() const;

Returns true if the unit has been completed.

## isConstructing ##
bool isConstructing() const;

Returns true when a unit has been issued an order to build a structure and is moving to the build location. Also returns true for Terran SCVs while they construct a building.

See also: [Unit](Unit.md)::[build](Unit#build.md), [Unit](Unit.md)::[cancelConstruction](Unit#cancelConstruction.md), [Unit](Unit.md)::[haltConstruction](Unit#haltConstruction.md), [Unit](Unit.md)::[isBeingConstructed](Unit#isBeingConstructed.md).

## isDefenseMatrixed ##
bool isDefenseMatrixed() const;

Returns true if the unit has a defense matrix from a Terran Science Vessel.

## isDetected ##
bool isDetected() const;

Returns true if the unit is visible and detected. If this is false and [Unit::isVisible](Unit#isVisible.md) returns true, then the unit is only partially visible, and requires detection (such as from a science vessel or overlord) to become fully visible and selectable/targetable.

## isEnsnared ##
bool isEnsnared() const;

Returns true if the unit has been ensnared by a Zerg Queen.

## isFollowing ##
bool isFollowing() const;

Returns true if the unit is following another unit.

See also: [Unit](Unit.md)::[follow](Unit#follow.md), [Unit](Unit.md)::[getTarget](Unit#getTarget.md).

## isGatheringGas ##
bool isGatheringGas() const;

Returns true if the unit is in one of the four states for gathering gas (MoveToGas, WaitForGas, HarvestGas, ReturnGas).

See also: [Unit](Unit.md)::[isCarryingGas](#isCarryingGas.md).

## isGatheringMinerals ##
bool isGatheringMinerals() const;

Returns true if the unit is in one of the four states for gathering minerals (MoveToMinerals, WaitForMinerals, MiningMinerals, ReturnMinerals).

See also: [Unit](Unit.md)::[isCarryingMinerals](#isCarryingMinerals.md).

## isHallucination ##
bool isHallucination() const;

Returns true for hallucinated units, false for normal units. Returns true for hallucinated enemy units only if Complete Map Information is enabled.

See also: [Unit](Unit.md)::[getRemoveTimer](Unit#getRemoveTimer.md).

## isHoldingPosition ##
bool isHoldingPosition() const;

Returns true for units that are holding position.

See also: [Unit](Unit.md)::[holdPosition](Unit#holdPosition.md).


## isIdle ##
bool isIdle() const;

Returns true if the unit is not doing anything.

See also: [Unit](Unit.md)::[stop](Unit#stop.md).

## isInterruptible ##
bool isInterruptible() const;

Returns true if the unit can be interrupted by another order like move or attack, otherwise there are very few orders that can be issued such as Unburrow, LiftOff, and Cancel.

## isInvincible ##
bool isInvincible () const;

Return true if the unit is currently invincible (stasis field, preplaced invincible setting(can apply to critters in melee), or Use Map Settings invincible trigger).

## isInWeaponRange ##
bool isInWeaponRange(Unit `*`target) const;

Returns true if the unit can immediately attack the target unit without any movement.

## isIrradiated ##
bool isIrradiated() const;

Returns true if the unit is being irradiated by a Terran Science Vessel.

See also: [Unit](Unit.md)::[getIrradiateTimer](Unit#getIrradiateTimer.md).

## isLifted ##
bool isLifted() const;

Returns true if the unit is a Terran building that is currently lifted off the ground.

See also: [Unit](Unit.md)::[lift](Unit#lift.md),[Unit](Unit.md)::[land](Unit#land.md).

## isLoaded ##
bool isLoaded() const;

Return true if the unit is loaded into a Terran Bunker, Terran Dropship, Protoss Shuttle, or Zerg Overlord.

See also: [Unit](Unit.md)::[load](Unit#load.md), [Unit](Unit.md)::[unload](Unit#unload.md), [Unit](Unit.md)::[unloadAll](Unit#unloadAll.md).

## isLockedDown ##
bool isLockedDown() const;

Returns true if the unit is locked down by a Terran Ghost.

See also: [Unit](Unit.md)::[getLockdownTimer](Unit#getLockdownTimer.md).

## isMaelstrommed ##
bool isMaelstrommed() const;

Returns true if the unit is being maelstrommed.

See also: [Unit](Unit.md)::[getMaelstromTimer](Unit#getMaelstromTimer.md).

## isMorphing ##
bool isMorphing() const;

Returns true if the unit is a zerg unit that is morphing.

See also: [Unit](Unit.md)::[morph](Unit#morph.md), [Unit](Unit.md)::[cancelMorph](Unit#cancelMorph.md), [Unit](Unit.md)::[getBuildType](Unit#getBuildType.md), [Unit](Unit.md)::[getRemainingBuildTime](Unit#getRemainingBuildTime.md).

## isMoving ##
bool isMoving() const;

Returns true if the unit is moving.

See also: [Unit](Unit.md)::[attack](Unit#attack.md), [Unit](Unit.md)::[stop](Unit#stop.md).

## isParasited ##
bool isParasited() const;

Returns true if the unit has been parasited by some other player.

## isPatrolling ##
bool isPatrolling() const;

Returns true if the unit is patrolling between two positions.

See also: [Unit](Unit.md)::[patrol](Unit#patrol.md).

## isPlagued ##
bool isPlagued() const;

Returns true if the unit has been plagued by a Zerg Defiler.

See also: [Unit](Unit.md)::[getPlagueTimer](Unit#getPlagueTimer.md).

## isRepairing ##
bool isRepairing() const;

Returns true if the unit is a Terran SCV that is repairing or moving to repair another unit.

## isResearching ##
bool isResearching() const;

Returns true if the unit is a building that is researching tech. See [TechTypes](TechTypes.md) for the complete list of available techs in Broodwar.

See also: [Unit](Unit.md)::[research](Unit#research.md), [Unit](Unit.md)::[cancelResearch](Unit#cancelResearch.md), [Unit](Unit.md)::[getTech](Unit#getTech.md), [Unit](Unit.md)::[getRemainingResearchTime](Unit#getRemainingResearchTime.md).

## isSelected ##
bool isSelected() const;

Returns true if the unit has been selected by the user via the starcraft GUI. Only available if you enable [Flag](Misc#Flag.md)::UserInput during [AIModule](AIModule.md)::[onStart](AIModule#onStart.md).

See also: [Game](Game.md)::[getSelectedUnits](Game#getSelectedUnits.md).

## isSieged ##
bool isSieged() const;

Returns true if the unit is a Terran Siege Tank that is currently in Siege mode.

See also: [Unit](Unit.md)::[siege](Unit#siege.md), [Unit](Unit.md)::[unsiege](Unit#unsiege.md).

## isStartingAttack ##
bool isStartingAttack() const;

Returns true if the unit is starting to attack.

See also: [Unit](Unit.md)::[attack](Unit#attack.md), [Unit](Unit.md)::[getGroundWeaponCooldown](Unit#getGroundWeaponCooldown.md), [Unit](Unit.md)::[getAirWeaponCooldown](Unit#getAirWeaponCooldown.md).

## isStasised ##
bool isStasised() const;

Returns true if the unit has been stasised by a Protoss Arbiter.

See also: [Unit](Unit.md)::[getStasisTimer](Unit#getStasisTimer.md).

## isStimmed ##
bool isStimmed() const;

Returns true if the unit is currently stimmed.

See also: [Unit](Unit.md)::[getStimTimer](Unit#getStimTimer.md).

## isStuck ##
bool isStuck() const;

Returns true if the unit is "stuck" on another unit, but not stuck behind a wall.

## isTraining ##
bool isTraining() const;

Returns true if the unit is training units (i.e. a Barracks training Marines).

See also: [Unit](Unit.md)::[train](Unit#train.md), [Unit](Unit.md)::[getTrainingQueue](Unit#getTrainingQueue.md), [Unit](Unit.md)::[cancelTrain](Unit#cancelTrain.md), [Unit](Unit.md)::[getRemainingTrainTime](Unit#getRemainingTrainTime.md).

## isUnderAttack ##
bool isUnderAttack() const;

Returns true if the unit was recently attacked.

## isUnderDarkSwarm ##
bool isUnderDarkSwarm() const;

Returns true if the unit is under a Dark Swarm.

## isUnderDisruptionWeb ##
bool isUnderDisruptionWeb() const;

Returns true if the unit is under a Disruption Web.

## isUnderStorm ##
bool isUnderStorm() const;

Returns true if the unit is under a Protoss Psionic Storm.

## isUnpowered ##
bool isUnpowered() const;

Returns true if the unit is a Protoss building that is unpowered because no pylons are in range.

## isUpgrading ##
bool isUpgrading() const;

Returns true if the unit is a building that is upgrading. See [UpgradeTypes](UpgradeTypes.md) for the complete list of available upgrades in Broodwar.

See also: [Unit](Unit.md)::[upgrade](Unit#upgrade.md), [Unit](Unit.md)::[cancelUpgrade](Unit#cancelUpgrade.md), [Unit](Unit.md)::[getUpgrade](Unit#getUpgrade.md), [Unit](Unit.md)::[getRemainingUpgradeTime](Unit#getRemainingUpgradeTime.md).

## isVisible ##
bool isVisible() const;

bool isVisible(Player`*` player) const;

Returns true if the unit is visible. If the CompleteMapInformation cheat flag is enabled, existing units hidden by the fog of war will be accessible, but isVisible will still return false.

If a player is specified, this will return true if the unit is visible to the given player. This version of the function is only available in replays or if the CompleteMapInformation cheat flag is enabled.

See also: [Unit](Unit.md)::[exists](Unit#exists.md).


# Unit Commands #

## canIssueCommand ##
bool canIssueCommand ([UnitCommand](UnitCommand.md) command);

Returns true if the unit is able to execute the given command, or false if there is an error. For example Unit::canIssueCommand(UnitCommand(UnitCommandType::Attack\_Position,NULL,50,60,0)) will return true if the unit can issue the attackMove command to the given position.

## issueCommand ##
bool issueCommand([UnitCommand](UnitCommand.md) command);

Issues the give unit command, or returns false if there is an error. For example Unit::issueCommand(UnitCommand(UnitCommandType::Attack\_Position,NULL,50,60,0)) will order the unit to attack move to the Position (50,60).

## attack ##
bool attack([Position](Misc#Position.md) target, bool shiftQueueCommand = false);

bool attack([Unit](Unit.md)`*` target, bool shiftQueueCommand = false);

Orders the unit to attack move to a specified location or attack a single unit. After issuing, the unit's order will become Orders::AttackMove or Orders::AttackUnit, depending on how the call was made.

This command can be queued by setting shiftQueueCommand to true.

## build ##
bool build([TilePosition](Misc#TilePosition.md) target, [UnitType](UnitType.md) type);

Orders the unit to build the given unit type at the given position. Note that if the player does not have enough resources when the unit attempts to place the building down, the order will fail. The tile position specifies where the top left corner of the building will be placed. After issuing the unit's order will become Orders::PlaceBuilding.

See also: [haltConstruction](Unit#haltConstruction.md), [Unit::cancelConstruction](Unit#cancelConstruction.md), [Unit::isConstructing](Unit#isConstructing.md), [Unit::isBeingConstructed](Unit#isBeingConstructed.md), [Unit::getBuiltType](Unit#getBuildType.md), [Unit::getBuildUnit](Unit#getBuildUnit.md), [Unit::getRemainingBuildTime](Unit#getRemainingBuildTime.md).

## buildAddon ##
bool buildAddon( [UnitType](UnitType.md) type);

Orders the unit to build the given add-on. The unit must be a Terran building that can have an add-on and the specified unit type must be an add-on unit type. The build() command can also be used to build add-ons.

See also: [Unit::cancelAddon](Unit#cancelAddon.md), [Unit::isConstructing](Unit#isConstructing.md), [Unit::getBuiltType](Unit#getBuildType.md), [Unit::getBuildUnit](Unit#getBuildUnit.md), [Unit::getRemainingBuildTime](Unit#getRemainingBuildTime.md).

## train ##
bool train([UnitType](UnitType.md) type);

Orders this unit to add the specified unit type to the training queue. Note that the player must have sufficient resources to train. If you wish to make units from a hatchery, use [getLarva](getLarva.md) to get the larva associated with the hatchery and then call [morph](morph.md) on the larva you want to morph. This command can also be used to make interceptors and scarabs.

See also: [Unit::cancelTrain](Unit#cancelTrain.md), [Unit::isTraining](Unit#isTraining.md), [Unit::getTrainingQueue](Unit#getTrainingQueue.md), [Unit::getRemainingTrainTime](Unit#getRemainingTrainTime.md).

## morph ##
bool morph([UnitType](UnitType.md) type);

Orders the unit to morph into the specified unit type. Returns false if given a wrong type.

See also: [Unit::cancelMorph](Unit#cancelMorph.md), [Unit::isMorphing](Unit#isMorphing.md), [Unit::getBuildType](Unit#getBuildType.md), [Unit::getRemainingBuildTime](Unit#getRemainingBuildTime.md).

## research ##
bool research([TechType](TechType.md) tech);

Orders the unit to research the given tech type.

See also: [Unit::cancelResearch](Unit#cancelResearch.md), [Unit::isResearching](Unit#isResearching.md), [Unit::getTech](Unit#getTech.md), [Unit::getRemainingResearchTime](Unit#getRemainingResearchTime.md).

## upgrade ##
bool upgrade(UpgradeType upgrade);

Orders the unit to upgrade the given upgrade type.

See also: [Unit::cancelUpgrade](Unit#cancelUpgrade.md), [Unit::isUpgrading](Unit#isUpgrading.md), [Unit::getUpgrade](Unit#getUpgrade.md), [Unit::getRemainingUpgradeTime](Unit#getRemainingUpgradeTime.md).

## setRallyPoint ##
bool setRallyPoint([Position](Misc#Position.md) target);

bool setRallyPoint([Unit](Unit.md) target);

Orders the unit to set its rally position to the specified position or unit.

See also: [Unit::getRallyPosition](Unit#getRallyPosition.md), [Unit::getRallyUnit](Unit#getRallyUnit.md).

## move ##
bool move([Position](Misc#Position.md) target, bool shiftQueueCommand = false);

Orders the unit to move to the specified position. After issuing, the unit's order will become Orders::Move.

This command can be queued by setting shiftQueueCommand to true.

See also: [Unit::isMoving](Unit#isMoving.md).

## patrol ##
bool patrol([Position](Misc#Position.md) target, bool shiftQueueCommand = false);

Orders the unit to patrol between its current position and the specified position. After issuing, the unit's order will become Orders::Patrol.

This command can be queued by setting shiftQueueCommand to true.

See also: [Unit::isPatrolling](Unit#isPatrolling.md).

## holdPosition ##
bool holdPosition(bool shiftQueueCommand = false);

Orders the unit to hold its position. Note: Reavers and Carriers can only hold position if they have at least one Scarab or Interceptor. After issuing, the unit's order will become Orders::HoldPosition.

This command can be queued by setting shiftQueueCommand to true.

See also: [Unit::isHoldingPosition](Unit#isHoldingPosition.md).

## stop ##
bool stop(bool shiftQueueCommand = false);

Orders the unit to stop. After issuing, the unit's order will become Orders::Stop.

This command can be queued by setting shiftQueueCommand to true.

See also: [Unit](Unit.md)::[isMoving](Unit#isMoving.md), [Unit](Unit.md)::[isBraking](Unit#isBraking.md).

## follow ##
bool follow([Unit](Unit.md) target, bool shiftQueueCommand = false);

Orders the unit to follow the specified unit. After issuing, the unit's order will become Orders::Follow.

This command can be queued by setting shiftQueueCommand to true.

See also: [Unit](Unit.md)::[isFollowing](Unit#isFollowing.md).

## gather ##
bool gather([Unit](Unit.md)`*` target, bool shiftQueueCommand = false);

Orders the unit to gather the specified unit. Only workers can be ordered to gather, and the target must be a mineral patch, Refinery, Assimilator, or Extractor.

This command can be queued by setting shiftQueueCommand to true.

See also: [Unit::isGatheringGas](Unit#isGatheringGas.md), [Unit::isGatheringMinerals](Unit#isGatheringMinerals.md).

## returnCargo ##
bool returnCargo(bool shiftQueueCommand = false);

Orders the unit to return its cargo to a nearby resource depot such as a Command Center. Only workers that are carrying minerals or gas can be ordered to return cargo.

This command can be queued by setting shiftQueueCommand to true.

See also: [Unit::isCarryingGas](Unit#isCarryingGas.md), [isCarryingMinerals](Unit#isCarryingMinerals.md), [Unit::isGatheringGas](Unit#isGatheringGas.md), [Unit::isGatheringMinerals](Unit#isGatheringMinerals.md).

## repair ##
bool repair([Unit](Unit.md)`*` target, bool shiftQueueCommand = false);

Orders the unit to repair the specified unit. Only Terran SCVs can be ordered to repair, and the target must be a mechanical Terran unit or building. After issuing, the unit's order will become Orders::Repair.

This command can be queued by setting shiftQueueCommand to true.

See also: [Unit::isRepairing](Unit#isRepairing.md).

## burrow ##
bool burrow();

Orders the unit to burrow. Either the unit must be a Zerg Lurker, or the unit must be a Zerg ground unit and burrow tech must be researched. After issuing, the unit's order will become Orders::Burrowing while the unit transitions.

See also: [Unit::unburrow](Unit#unburrow.md), [Unit::isBurrowed](Unit#isBurrowed.md).

## unburrow ##
bool unburrow();

Orders the burrowed unit to unburrow. After issuing, the unit's order will become Orders::Unburrowing while the unit transitions.

See also: [Unit::burrow](Unit#burrow.md), [Unit::isBurrowed](Unit#isBurrowed.md).

## cloak ##
bool cloak();

Orders the unit to cloak.

See also: [Unit::decloak](Unit#decloak.md), [Unit::isCloaked](Unit#isCloaked.md).

## decloak ##
bool decloak();

Orders the unit to decloak.

See also: [Unit::cloak](Unit#cloak.md), [Unit::isCloaked](Unit#isCloaked.md).

## siege ##
bool siege();

Orders the unit to siege. Note: unit must be a Terran siege tank. After issuing, the unit's order will become Orders::Sieging while the siege tank transitions.

See also: [Unit::unsiege](Unit#unsiege.md), [Unit::isSieged](Unit#isSieged.md).

## unsiege ##
bool unsiege();

Orders the unit to unsiege. Note: unit must be a Terran siege tank. After issuing, the unit's order will become Orders::Unsieging while the siege tank transitions.

See also: [Unit::siege](Unit#siege.md), [Unit::isSieged](Unit#isSieged.md).

## lift ##
bool lift();

Orders the unit to lift. Note: unit must be a Terran building that can be lifted.

See also: [Unit::land](Unit#land.md), [Unit::isLifted](Unit#isLifted.md).

## land ##
bool land([TilePosition](Misc#TilePosition.md) target);

Orders the unit to land. Note: unit must be a Terran building that is currently lifted.

See also: [Unit::lift](Unit#lift.md), [Unit::isLifted](Unit#isLifted.md).

## load ##
bool load([Unit](Unit.md)`*` target, bool shiftQueueCommand = false);

Orders the unit to load the target unit.

This command can be queued by setting shiftQueueCommand to true.

See also: [Unit](Unit.md)::[unload](Unit#unload.md), [Unit](Unit.md)::[unloadAll](Unit#unloadAll.md), [Unit](Unit.md)::[getLoadedUnits](Unit#getLoadedUnits.md), [Unit](Unit.md):[isLoaded](Unit#isLoaded.md).

## unload ##
bool unload([Unit](Unit.md)`*` target);

Orders the unit to unload the target unit.

See also: [Unit](Unit.md)::[load](Unit#load.md), [Unit](Unit.md)::[unloadAll](Unit#unloadAll.md), [Unit](Unit.md)::[getLoadedUnits](Unit#getLoadedUnits.md), [Unit](Unit.md):[isLoaded](Unit#isLoaded.md).

## unloadAll ##
bool unloadAll(bool shiftQueueCommand = false);

Orders the unit to unload all loaded units at the unit's current position.

This command can be queued by setting shiftQueueCommand to true.

See also: [Unit](Unit.md)::[load](Unit#load.md), [Unit](Unit.md)::[unload](Unit#unload.md), [Unit](Unit.md)::[unloadAll](Unit#unloadAll.md), [Unit](Unit.md)::[getLoadedUnits](Unit#getLoadedUnits.md), [Unit](Unit.md):[isLoaded](Unit#isLoaded.md).

## unloadAll ##
bool unloadAll([Position](Misc#Position.md) target, bool shiftQueueCommand = false);

Orders the unit to unload all loaded units at the specified location. Unit should be a Terran Dropship, Protoss Shuttle, or Zerg Overlord. If the unit is a Terran Bunker, the units will be unloaded right outside the bunker, like in the first version of unloadAll.

This command can be queued by setting shiftQueueCommand to true.

See also: [Unit](Unit.md)::[load](Unit#load.md), [Unit](Unit.md)::[unload](Unit#unload.md), [Unit](Unit.md)::[unloadAll](Unit#unloadAll.md), [Unit](Unit.md)::[getLoadedUnits](Unit#getLoadedUnits.md), [Unit](Unit.md):[isLoaded](Unit#isLoaded.md).

## rightClick ##
bool rightClick([Position](Misc#Position.md) target, bool shiftQueueCommand = false);

bool rightClick([Unit](Unit.md)`*` target, bool shiftQueueCommand = false);

Works like the right click in the GUI. Right click on a mineral patch to order a worker to mine, right click on an enemy to attack it.

This command can be queued by setting shiftQueueCommand to true.

## haltConstruction ##
bool haltConstruction();

Orders the SCV to stop constructing the building, and the building is left in a partially complete state until it is canceled, destroyed, or completed.

See also: [Unit](Unit.md)::[Unit::build](Unit#build.md), [Unit](Unit.md)::[Unit::cancelConstruction](Unit#cancelConstruction.md), [Unit::isConstructing](Unit#isConstructing.md).

## cancelConstruction ##
bool cancelConstruction();

Orders the building to stop being constructed.

See also: [Unit::build](Unit#build.md), [Unit::beingConstructed](Unit#beingConstructed.md).

## cancelAddon ##
bool cancelAddon();

Orders the unit to stop making the addon.

See also: [Unit::buildAddon](Unit#buildAddon.md).

## cancelTrain ##
bool cancelTrain(int slot = -2);

Orders the unit to remove the specified unit from its training queue. Leaving the default value will remove the last unit from the training queue.

See also: [Unit::train](Unit#train.md), [Unit::isTraining](Unit#isTraining.md), [Unit::getTrainingQueue](Unit#getTrainingQueue.md).

## cancelMorph ##
bool cancelMorph();

Orders the unit to stop morphing.

See also: [Unit::morph](Unit#morph.md), [Unit::isMorphing](Unit#isMorphing.md).

## cancelResearch ##
bool cancelResearch();

Orders the unit to cancel a research in progress.

See also: [Unit::research](Unit#research.md), [Unit::isResearching](Unit#isResearching.md), [Unit::getTech](Unit#getTech.md).

## cancelUpgrade ##
bool cancelUpgrade();

Orders the unit to cancel an upgrade in progress.

See also: [Unit::upgrade](Unit#upgrade.md), [Unit::isUpgrading](Unit#isUpgrading.md), [Unit::getUpgrade](Unit#getUpgrade.md).

## useTech ##
```

bool useTech([TechType] tech);
bool useTech([TechType] tech, Position position);
bool useTech([TechType] tech, Unit* target);```

Orders the unit to use a technology either not requiring a target (i.e. Stim Pack), a target position (i.e. Spider Mines), or a target unit (i.e. Irradiate).
Returns true if the tech can be used.

## placeCOP ##
bool placeCOP([TilePosition](TilePosition.md) target);

Moves a Flag Beacon from its current location to the target location.