Class header file: [BWAPI/WeaponType.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/WeaponType.h#)

List of all [WeaponTypes](WeaponTypes.md).

Methods:

  * [getID](#getID.md)
  * [getName](#getName.md)
  * [getTech](#getTech.md)
  * [whatUses](#whatUses.md)
  * [damageAmount](#damageAmount.md)
  * [damageBonus](#damageBonus.md)
  * [damageCooldown](#damageCooldown.md)
  * [damageFactor](#damageFactor.md)
  * [upgradeType](#upgradeType.md)
  * [damageType](#damageType.md)
  * [explosionType](#explosionType.md)
  * [minRange](#minRange.md)
  * [maxRange](#maxRange.md)
  * [innerSplashRadius](#innerSplashRadius.md)
  * [medianSplashRadius](#medianSplashRadius.md)
  * [outerSplashRadius](#outerSplashRadius.md)

  * [targetsAir](#targetsAir.md)
  * [targetsGround](#targetsGround.md)
  * [targetsMechanical](#targetsMechanical.md)
  * [targetsOrganic](#targetsOrganic.md)
  * [targetsNonBuilding](#targetsNonBuilding.md)
  * [targetsNonRobotic](#targetsNonRobotic.md)
  * [targetsTerrain](#targetsTerrain.md)
  * [targetsOrgOrMech](#targetsOrgOrMech.md)
  * [targetsOwn](#targetsOwn.md)

Non-member methods in WeaponTypes namespace:

  * [getWeaponType](#getWeaponType.md)
  * [allWeaponTypes](#allWeaponTypes.md)
  * [normalWeaponTypes](#normalWeaponTypes.md)
  * [specialWeaponTypes](#specialWeaponTypes.md)

### getID ###
int getID() const;

Returns a unique ID for this weapon type.

### getName ###
std::string getName() const;

Returns the name of the weapon.

### getTech ###
[TechType](TechType.md) getTech() const;

Returns the tech type that must be researched before this weapon can be used, or TechTypes::None if no tech type is required.

### whatUses ###
[UnitType](UnitType.md) whatUses() const;

Returns the unit that can use this weapon.

### damageAmount ###
int damageAmount() const;

Returns the amount of damage that this weapon deals per attack.

### damageBonus ###
int damageBonus() const;

### damageCooldown ###
int damageCooldown() const;

Returns the amount of cooldown time between attacks.

### damageFactor ###
int damageFactor() const;

Returns the amount that the damage increases per upgrade

See also: WeaponType::[upgradeType](#upgradeType.md).

### upgradeType ###
[UpgradeType](UpgradeType.md) upgradeType() const;

Returns the upgrade type that can be upgraded to increase the attack damage.

### damageType ###
[DamageType](DamageType.md) damageType() const;

Returns the type of damage that this weapon uses (i.e. concussive, normal, explosive, etc).

### explosionType ###
[ExplosionType](ExplosionType.md) explosionType() const;

Returns the type of explosion that this weapon uses.

### minRange ###
int minRange() const;

Returns the minimum attack range of the weapon, measured in pixels, 0 for most things except WeaponTypes::Arclite\_Shock\_Cannon (the weapon of the Terran Siege Tank in Siege Mode).

### maxRange ###
int maxRange() const;

Returns the maximum attack range of the weapon, measured in pixels.

### innerSplashRadius ###
int innerSplashRadius() const;

Inner radius used in splash damage calculations.

### medianSplashRadius ###
int medianSplashRadius() const;

Median radius used in splash damage calculations.

### outerSplashRadius ###
int outerSplashRadius() const;

Outer radius used in splash damage calculations.

### targetsAir ###
bool targetsAir() const;

Returns true if this weapon can attack air units.

### targetsGround ###
bool targetsGround() const;

Returns true if this weapon can attack ground units.

### targetsMechanical ###
bool targetsMechanical() const;

### targetsOrganic ###
bool targetsOrganic() const;

### targetsNonBuilding ###
bool targetsNonBuilding() const;

### targetsNonRobotic ###
bool targetsNonRobotic() const;

### targetsTerrain ###
bool targetsTerrain() const;

### targetsOrgOrMech ###
bool targetsOrgOrMech() const;

### targetsOwn ###
bool targetsOwn() const;

### getWeaponType ###
[WeaponType](WeaponType.md) getWeaponType(std::string name);

Given the name of a weapon, this will return the corresponding weapon type object.

### allWeaponTypes ###
std::set<[WeaponType](WeaponType.md)>& allWeaponTypes();

Returns the set of all the [WeaponTypes](WeaponTypes.md).

### normalWeaponTypes ###
std::set<[WeaponType](WeaponType.md)>& normalWeaponTypes();

Returns the set of all normal weapons in [WeaponTypes](WeaponTypes.md).

### specialWeaponTypes ###
std::set<[WeaponType](WeaponType.md)>& specialWeaponTypes();

Returns the set of all special weapons in [WeaponTypes](WeaponTypes.md).