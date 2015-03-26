Class header file: [BWAPI/BulletType.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/BulletType.h#)

Each [Bullet](Bullet.md) object in the game has a certain type. The list of all the possible Bullet types is available here: [BulletTypes](BulletTypes.md).

Methods:

  * [getID](#getID.md)
  * [getName](#getName.md)

Non-member methods in BulletTypes namespace:

  * [getBulletType](#getBulletType.md)
  * [allBulletTypes](#allBulletTypes.md)

### getID ###
int getID();

Returns the unique ID for this bullet type.

### getName ###
std::string getName();

Returns the name of this bullet type.

### getBulletType ###
[Order](Order.md) getBulletType(std::string name);

Given the name of a bullet type, BulletTypes::getBulletType() will return the corresponding BulletType object.

### allBulletTypes ###
std::set<[BulletType](BulletType.md)>& allBulletTypes();

Returns the set of all the [BulletTypes](BulletTypes.md).