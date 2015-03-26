Class header file: [BWAPI/TechType.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/TechType.h#)

List of all [TechTypes](TechTypes.md).

Methods:

  * [getID](#getID.md)
  * [getName](#getName.md)
  * [getRace](#getRace.md)
  * [mineralPrice](#mineralPrice.md)
  * [gasPrice](#gasPrice.md)
  * [researchTime](#researchTime.md)
  * [energyUsed](#energyUsed.md)
  * [whatResearches](#whatResearches.md)
  * [getWeapon](#getWeapon.md)
  * [targetsUnit](#targetsUnit.md)
  * [targetsPosition](#targetsPosition.md)
  * [whatUses](#whatUses.md)

Non-member methods in TechTypes namespace:

  * [getTechType](#getTechType.md)
  * [allTechTypes](#allTechTypes.md)

### getID ###
int getID() const;

Returns the unique ID for this tech type.

### getName ###
std::string getName() const;

Returns the name of the tech type.

### getRace ###
[Race](Race.md) getRace() const;

Returns the race that uses the TechType. For example, TechTypes::Scanner\_Sweep.getRace() will return Races::Terran.

### mineralPrice ###
int mineralPrice() const;

Returns the mineral cost of the tech type.

### gasPrice ###
int gasPrice() const;

Returns the vespene gas price of the tech type.

### researchTime ###
int researchTime() const;

Returns the number of frames needed to research this tech type.

### energyUsed ###
int energyUsed() const;

Returns the amount of energy used each time this tech type is used.

### whatResearches ###
[UnitType](UnitType.md) whatResearches() const;

Returns the type of unit that researches this tech type. If this tech type is available for free (does not need to be researched), then this method will return UnitTypes::None.

### getWeapon ###
[WeaponType](WeaponType.md) getWeapon() const;

Returns the corresponding weapon for this tech type, or TechTypes::None if no corresponding weapon exists. For example, TechTypes::Dark\_Swarm.getWeapon() will return WeaponTypes::Dark\_Swarm.

### targetsUnit ###
bool targetsUnit() const;

Returns true if this tech type must be used on another unit (i.e. Irradiate).

### targetsPosition ###
bool targetsPosition() const;

Returns true if this tech type must be used at a specified a position (i.e. Dark Swarm).

### whatUses ###
const std::set<[UnitType](UnitType.md)>& whatUses() const;

Returns the set of units that can use this tech type. Usually this will just be a set of one unit type, however in some cases, such as TechTypes::Burrowing, several unit types will be returned.

### getTechType ###
[TechType](TechType.md) getTechType(std::string name);

Given a string, this will return the tech type.

### allTechTypes ###
std::set<[TechType](TechType.md)>& allTechTypes();

Returns the set of all the [TechTypes](TechTypes.md).