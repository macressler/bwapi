Class header file: [BWAPI/UnitCommandType.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/UnitCommandType.h#)

Specifies the type of UnitCommand. Used when constructing UnitCommand objects, which are then passed to [Unit::issueCommand](Unit#issueCommand.md) which uses this type to determine which Unit member function to call.

List of all [UnitCommandTypes](UnitCommandTypes.md).

Methods:

  * [getID](#getID.md)
  * [getName](#getName.md)

Non-member methods in UnitCommandTypes namespace:

  * [getUnitCommandType](#getUnitCommandType.md)
  * [allUnitCommandTypes](#allUnitCommandTypes.md)


### getID ###
int getID();

Returns the unique ID for this unit command type.

### getName ###
std::string getName();

Returns the name of the unit command type. For example UnitCommandTypes::Hold\_Position.getName() will return an std::string object containing "Hold Position".

### getUnitCommandType ###
[UnitCommandType](UnitCommandType.md) getUnitCommandType(std::string name);

Given the name of a unit command type, this function will return the UnitCommandType. For example: UnitCommandTypes::getUnitCommandType("Attack Unit") will return UnitCommandTypes::Attack\_Unit.

### allUnitCommandTypes ###
std::set<[UnitCommandType](UnitCommandType.md)>& allUnitCommandTypes();

Returns the set of all the [UnitCommandTypes](UnitCommandTypes.md).