Class header file: [BWAPI/Player.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/Player.h#)

Each player in a match will have his or her own player instance. There is also a neutral player which owns all the neutral units.



# Methods #

## getID ##
int getID() const;

Returns a unique ID for the player.

## getName ##
std::string getName() const;

Returns the name of the player.

## getUnits ##
const std::set< [Unit](Unit.md)`*` >& getUnits() const;

Returns the set of units the player own. Note that units loaded into Terran dropships, Terran bunkers, Terran refineries, Protoss assimilators, and Zerg extractors are not yet included in the set.

## getRace ##
[Race](Race.md) getRace() const;

Returns the race of the player.

## getType ##
[PlayerType](PlayerType.md) getType() const;

Returns the type of the player.

## getForce ##
[Force](Force.md)`*` getForce() const;

Returns the force the player is on.

## isAlly ##
bool isAlly([Player](Player.md)`*` player) const;

Returns true if other player is an ally of this player.

## isEnemy ##
bool isEnemy([Player](Player.md)`*` player) const;

Returns true if other player is an enemy of this player.

## isNeutral ##
bool isNeutral() const;

Returns true if the player is the neutral player.

## getStartLocation ##
[TilePosition](Misc#TilePosition.md) getStartLocation() const;

Returns the starting location of the player. If complete map information is disabled, this function will return TilePositions::Unknown for enemy players. For the complete set of starting locations for the current map, see [Game](Game.md)::[getStartLocations](Game#getStartLocations.md).

## isVictorious ##
bool isVictorious() const;

Returns true if the player has achieved victory.

## isDefeated ##
bool isDefeated() const;

Returns true if the player has been defeated.

## leftGame ##
bool leftGame() const;

Returns true if the player left the game.

## minerals ##
int minerals() const;

Returns the amount of minerals the player currently has.

Note that minerals() is equal to [gatheredMinerals](Player#gatheredMinerals.md)() + [refundedMinerals](Player#refundedMinerals.md)() - [repairedMinerals](Player#repairedMinerals.md)() - [spentMinerals](Player#spentMinerals.md)().

## gas ##
int gas() const;

Returns the amount of vespene gas the player currently has.

Note that gas() is equal to [gatheredGas](Player#gatheredGas.md)() + [refundedGas](Player#refundedGas.md)() - [repairedGas](Player#repairedGas.md)() - [spentGas](Player#spentGas.md)().

## gatheredMinerals ##
int gatheredMinerals() const;

Returns the cumulative amount of minerals the player has mined up to this point (including the 50 minerals at the start of the game).

## gatheredGas ##
int gatheredGas() const;

Returns the cumulative amount of gas the player has harvested up to this point.

## repairedMinerals ##
int repairedMinerals() const;

Returns the cumulative amount of minerals the player has spent on repairs up to this point.

## repairedGas ##
int repairedGas() const;

Returns the cumulative amount of gas the player has spent on repairs up to this point.

## refundedMinerals ##
int refundedMinerals() const;

Returns the cumulative amount of minerals refunded from canceled units, canceled upgrades, and canceled research.

## refundedGas ##
int refundedGas() const;

Returns the cumulative amount of gas refunded from canceled units, canceled upgrades, and canceled research.

## spentMinerals ##
int spentMinerals() const;

Returns the cumulative amount of minerals spent, not including repairs.

## spentGas ##
int spentGas() const;

Returns the cumulative amount of gas spent, not including repairs.

## supplyTotal ##
int supplyTotal() const;

int supplyTotal(Race race) const;

Returns the total amount of supply the player has. If a race is provided, the total supply for the given race will be returned, otherwise the player's initial race will be used. Supply counts returned by BWAPI are double what you would expect to see from playing the game. This is because zerglings take up 0.5 in-game supply.

## supplyUsed ##
int supplyUsed() const;

int supplyUsed(Race race) const;

Returns how much of the supply is actually being used by units. If a race is provided, the used supply for the given race will be returned, otherwise the player's initial race will be used. Supply counts returned by BWAPI are double what you would expect to see from playing the game. This is because zerglings take up 0.5 in-game supply.

## allUnitCount ##
int allUnitCount([UnitType](UnitType.md) type) const;

Returns the current number of all accessible units of the given type owned by this player (both completed units and incomplete units). If the Complete Map Information flag is disabled, only visible units will be accessible so this function will return the same values as visibleUnitCount.

## visibleUnitCount ##
int visibleUnitCount([UnitType](UnitType.md) type) const;

Returns the current number of all visible units of the given type owned by this player (both completed units and incomplete units). If the Complete Map Information flag is disabled, then this function will return the same values as allUnitCount.

## completedUnitCount ##
int completedUnitCount([UnitType](UnitType.md) type) const;

Returns the current number of completed accessible units of the given type owned by this player.

## incompleteUnitCount ##
int incompleteUnitCount([UnitType](UnitType.md) type) const;

Returns the current number of incomplete accessible units of the given type owned by this player.

## deadUnitCount ##
int deadUnitCount([UnitType](UnitType.md) unit) const;

Returns the total number of friendly units of the given type that this player has lost. If the Complete Map Information flag is disabled, this will return 0 for enemy players.

## killedUnitCount ##
int killedUnitCount([UnitType](UnitType.md) unit) const;

Returns the total number of enemy units of the given type that this player has killed. If the Complete Map Information flag is disabled, this will return 0 for enemy players.

## isUnitAvailable ##
bool isUnitAvailable([UnitType](UnitType.md) unit) const;

Returns true if the player is allowed to build the given unit type. Some Use Map Settings maps can restrict the use of certain units.

## getUpgradeLevel ##
int getUpgradeLevel([UpgradeType](UpgradeType.md) upgrade) const;

Returns the player's current upgrade level of the given upgrade. To order a unit to upgrade a given upgrade type, see [Unit](Unit.md)::[upgrade](Unit#upgrade.md).

## isUpgrading ##
bool isUpgrading([UpgradeType](UpgradeType.md) upgrade) const;

Returns true if the player is upgrading the given upgrade. To order a unit to upgrade a given upgrade type, see [Unit](Unit.md)::[upgrade](Unit#upgrade.md).

## getMaxUpgradeLevel ##
int getMaxUpgradeLevel([UpgradeType](UpgradeType.md) upgrade) const;

Returns the maximum upgrades the player can perform using the specified upgrade. Some Use Map Settings maps can increase or decrease the number of upgrades the player can perform (up to 255).

## hasResearched ##
bool hasResearched([TechType](TechType.md) tech) const;

Returns true if the player has finished researching the given tech. To order a unit to research a given tech type, see [Unit](Unit.md)::[research](Unit#research.md).

## isResearching ##
bool isResearching([TechType](TechType.md) tech) const;

Returns true if the player is researching the given tech. To order a unit to research a given tech type, see [Unit](Unit.md)::[reseach](Unit#research.md).

## isResearchAvailable ##
bool isResearchAvailable([TechType](TechType.md) tech) const

Returns true if the player is allowed to research the given tech. Some Use Map Settings maps can enforce restrictions on technologies.

## getColor ##
[Color](Color.md) getColor() const;

Returns the color of the player, used for drawing to the screen.

## getTextColor ##
int getTextColor() const;

Returns a control character that represents the player's color. Used for printing text to the screen.

## maxEnergy ##
int maxEnergy([UnitType](UnitType.md) unit) const;

Returns the maximum amount of energy for the given unit type, taking into account the upgrades the player has.

## topSpeed ##
double topSpeed(UnitType unit) const;

Returns the top speed for the given unit type, taking into account the upgrades the player has.

## groundWeaponMaxRange ##
int groundWeaponMaxRange(UnitType unit) const;

Returns the maximum range of the given unit type's ground weapon, taking into account the upgrades the player has.

## airWeaponMaxRange ##
int airWeaponMaxRange(UnitType unit) const;

Returns the maximum range of the given unit type's air weapon, taking into account the upgrades the player has.

## weaponMaxRange ##
int weaponMaxRange(WeaponType weapon) const;

Returns the maximum range of the given weapon type with the player's upgrades applied.

## sightRange ##
int sightRange(UnitType unit) const;

Returns the sight range for the given unit type, taking into account the upgrades the player has.

## groundWeaponDamageCooldown ##
int groundWeaponDamageCooldown(UnitType unit) const;

Returns the attack cooldown of the given unit type's ground weapon, taking into account the upgrades the player has.

## armor ##
int armor(UnitType unit) const;

Returns the armor for the given unit type, taking into account the upgrades the player has.

## getUnitScore ##
int getUnitScore() const;

Returns the total unit score that the player has accumulated. This excludes buildings.

## getKillScore ##
int getKillScore() const;

Returns the total kill score that the player has accumulated. This excludes buildings.

## getBuildingScore ##
int getBuildingScore() const;

Returns the total building score that the player has accumulated.

## getRazingScore ##
int getRazingScore() const;

Returns the total razings score that the player has accumulated. In other words, the score for buildings destroyed.

## getCustomScore ##
int getCustomScore() const;

Returns the custom score used in Use Map Settings.