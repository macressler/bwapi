Class header file: [BWAPI/Race.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/Race.h#)

List of all [Races](#Races.md).

Methods:

  * [getID](#getID.md)
  * [getName](#getName.md)
  * [getWorker](#getWorker.md)
  * [getCenter](#getCenter.md)
  * [getRefinery](#getRefinery.md)
  * [getTransport](#getTransport.md)
  * [getSupplyProvider](#getSupplyProvider.md)



Non-member methods in Races namespace:

  * [getRace](#getRace.md)
  * [allRaces](#allRaces.md)

### getID ###
int getID() const;

Returns a unique ID for this race.

### getName ###
std::string getName() const;

Returns the name of the race. For example Races::Terran.getName() will return a std::string object containing "Terran".

### getWorker ###
[UnitType](UnitType.md) getWorker() const;

Returns the worker unit type for the given race. For example Races::Protoss.getWorker() will return UnitTypes::Protoss\_Probe.

### getCenter ###
[UnitType](UnitType.md) getCenter() const;

Returns the center unit type for the given race. For example Races::Terran.getCenter() will return UnitTypes::Terran\_Command\_Center. While there are three center types for Zerg (Hatchery, Lair, and Hive), Races::Zerg.getCenter() will only return UnitTypes::Zerg\_Hatchery, since it is the unit type needed to make a new center.

### getRefinery ###
[UnitType](UnitType.md) getRefinery() const;

Returns the refinery unit type for the given race. For example: Races::Zerg.getRefinery() will return UnitTypes::Zerg\_Extractor.

### getTransport ###
[UnitType](UnitType.md) getTransport() const;

Returns the transport unit type for the given race. For example: Races::Protoss.getTransport() will return UnitTypes::Protoss\_Shuttle.

### getSupplyProvider ###
[UnitType](UnitType.md) getSupplyProvider() const;

Returns the main supply provider unit type for the given race. For example: Races::Terran.getSupplyProvider() will return UnitTypes::Terran\_Supply\_Depot.

### getRace ###
[Race](Race.md) getRace(std::string name);

Given the name of a race, this function will return the race type. For example: Races::getRace("Zerg") will return Races::Zerg.

### allRaces ###
std::set<[Race](Race.md)>& allRaces();

Returns the set of all the races, which are listed below.

## Races ##

  * Zerg
  * Terran
  * Protoss
  * Random
  * Other

  * None
  * Unknown