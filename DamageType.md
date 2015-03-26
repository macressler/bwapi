Class header file: [BWAPI/DamageType.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/DamageType.h#)

Each type of Unit in Starcraft: Broodwar has a particular [WeaponType](WeaponType.md) for its ground weapon and air weapon (either of which could be WeaponTypes::None). Each type of Weapon has a particular damage type, which could be explosive, concussive, or something else. Here is the list of all the possible [DamageTypes](#DamageTypes.md).

Methods:

  * [getID](#getID.md)
  * [getName](#getName.md)

Non-member methods in Orders namespace:

  * [getDamageType](#getDamageType.md)
  * [allDamageTypes](#allDamageTypes.md)

### getID ###
int getID();

Returns a unique ID for this damage type.

### getName ###
std::string getName();

Returns the name of this damage type. For example DamageTypes::Explosive.getName() will return std::string("Explosive").

### getDamageType ###
[DamageType](DamageType.md) getDamageType(std::string name);

Given the name of a damage type, this will return a corresponding DamageType object. For example, DamageTypes::getDamageType("Concussive") will return DamageTypes::Concussive.

### allDamageTypes ###
std::set<[DamageType](DamageType.md)>& allDamageTypes();

Returns the set of all the DamageTypes, which are listed below:

## DamageTypes ##

  * Concussive
  * Explosive
  * Ignore\_Armor
  * Independent
  * Normal
  * None
  * Unknown