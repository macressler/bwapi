Class header file: [BWAPI/ExplosionType.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/ExplosionType.h#)

Each type of Unit in Starcraft: Broodwar has a particular WeaponType for its ground weapon and air weapon (either of which could be WeaponTypes::None). Each type of Weapon has a particular explosion type. Here is the list of all the possible [ExplosionTypes](ExplosionTypes.md).

Methods:

  * [getID](#getID.md)
  * [getName](#getName.md)

Non-member methods in ExplosionTypes namespace:

  * [getExplosionType](#getExplosionType.md)
  * [allExplosionTypes](#allExplosionTypes.md)

### getID ###
int getID();

Returns a unique ID for this explosion type.

### getName ###
std::string getName();

Returns the name of this explosion type.

### getExplosionType ###
[ExplosionType](ExplosionType.md) getExplosionType(std::string name);

Given a name of an explosion type, this will return the corresponding ExplosionType object.

### allExplosionTypes ###
std::set<[ExplosionType](ExplosionType.md)>& allExplosionTypes();

Returns the set of all the [ExplosionTypes](ExplosionTypes.md).