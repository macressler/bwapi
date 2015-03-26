Class header file: [BWAPI/UnitSizeType.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/UnitSizeType.h#)

List of all [UnitSizeTypes](#UnitSizeTypes.md).

Methods:

  * [getID](#getID.md)
  * [getName](#getName.md)

Non-member methods in UnitSizeTypes namespace:

  * [getUnitSizeType](#getUnitSizeType.md)
  * [allUnitSizeTypes](#allUnitSizeTypes.md)

### getID ###
int getID();

Returns a unique ID for this UnitSizeType.

### getName ###
std::string getName();

Returns the string corresponding to the UnitSizeType object. For example, UnitSizeTypes::Medium.getName() returns std::string("Medium").

### getUnitSizeType ###
[UnitSizeType](UnitSizeType.md) getUnitSizeType(std::string name);

Given a string, this function returns the size time it refers to. For example, UnitSizeTypes::getUnitSizeType("Small") returns UnitSizeTypes::Small.

### allUnitSizeTypes ###
std::set<[UnitSizeType](UnitSizeType.md)>& allUnitSizeTypes();

Returns the set of all the sizes, which are listed below:

## UnitSizeTypes ##

  * Independent
  * Small
  * Medium
  * Large
  * None
  * Unknown