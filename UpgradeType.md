Class header file: [BWAPI/UpgradeType.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/UpgradeType.h#)

The UpgradeType class is used to get information about a particular upgrade.

List of all [UpgradeTypes](UpgradeTypes.md).



# Methods #
## getID ##
int getID() const;

Returns the unique ID for this upgrade type.

## getName ##
std::string getName() const;

Returns the name for the upgrade type.

## getRace ##
[Race](Race.md) getRace() const;

Returns the race the upgrade is for. For example, UpgradeTypes::Terran\_Infantry\_Armor.getRace() will return Races::Terran.

## mineralPrice ##
int mineralPrice(int level = 1) const;

Returns the mineral price for the specified upgrade level. For the base price, call `mineralPrice(1)`.

## mineralPriceFactor ##
int mineralPriceFactor() const;

Returns the amount that the mineral price increases for each additional upgrade.

## gasPrice ##
int gasPrice(int level = 1) const;

Returns the vespene gas price for the specified upgrade level. For the base price, call `gasPrice(1)`.

## gasPriceFactor ##
int gasPriceFactor() const;

Returns the amount that the vespene gas price increases for each additional upgrade.

## upgradeTime ##
int upgradeTime(int level = 1) const;

Returns the number of frames needed to research the specified upgrade level. For the base time, call `upgradeTime(1)`.

## upgradeTimeFactor ##
int upgradeTimeFactor() const;

Returns the number of frames that the upgrade time increases for each additional upgrade.

## maxRepeats ##
int maxRepeats() const;

Returns the maximum number of times the upgrade can be researched.

## whatUpgrades ##
[UnitType](UnitType.md) whatUpgrades() const;

Returns the type of unit that researches the upgrade.

## whatsRequired ##
[UnitType](UnitType.md) whatsRequired(int level = 1) const;

Returns the type of unit that is required for the specified upgrade level.

## whatUses ##
const std::set<[UnitType](UnitType.md)>& whatUses() const;

Returns the set of units that are affected by this upgrade.

# Non-Member Methods #
## getUpgradeType ##
[UpgradeType](UpgradeType.md) getUpgradeType(std::string name);

Given a string, this will return the upgrade type.

## allUpgradeTypes ##
std::set<[UpgradeType](UpgradeType.md)>& allUpgradeTypes();

Returns the set of all the UpgradeTypes.