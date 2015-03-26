Class header file: [BWAPI/Region.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/Region.h#)

The Region class provides access to some of Broodwar's pathing information and offers members that can assist in navigation, scouting, construction, and information for key areas such as chokepoints. Though not always accurate, it is a lightweight alternative to BWTA that beginners can start with.

These regions are not so advanced as to cover everything up to a choke point with accurate polygons, but instead are small clusters of tiles connected to each other, kind of like a honeycomb.



# Methods #

## getID ##
```

int getID() const;```
Returns a unique ID that represents this region. This ID is the same one used by Broodwar.

## getRegionGroupID ##
```

int getRegionGroupID() const;```
Returns a value that represents the group that this region belongs to. A region group is a value that represents a fully connected group of regions, such as the entire mainland. An island for example, will have a different region ID than the main land.

## getCenter ##
```

[Position] getCenter() const;```
Returns a position that represents the region's center.

## isHigherGround ##
```

bool isHigherGround() const;```
Returns true if the region is part of strategic higher ground. Strategic higher ground can be any high ground region.

## getDefensePriority ##
```

int getDefensePriority() const;```
Returns a value that represents the priority given to the region for defensive or offensive measures. A value of 2 may represent a choke point. This representation may not always be accurate.

## isWalkable ##
```

bool isWalkable() const;```
Returns true if the entire region is walkable.

## getNeighbors ##
```

const std::set<Region*> &getNeighbors() const;```
Returns the set of all neighbor regions. A neighbor is any region that is touching this one.

## getBoundsLeft ##
```

int getBoundsLeft() const;```
Returns the region's standard left boundry position, in pixels. This boundry only considers the full tiles that are part of this region.

> _See also: [Region::getBoundsTop](Region#getBoundsTop.md), [Region::getBoundsRight](Region#getBoundsRight.md), [Region::getBoundsBottom](Region#getBoundsBottom.md)_

## getBoundsTop ##
```

int getBoundsTop() const;```
Returns the region's standard top boundry position, in pixels. This boundry only considers the full tiles that are part of this region.

> _See also: [Region::getBoundsLeft](Region#getBoundsLeft.md), [Region::getBoundsRight](Region#getBoundsRight.md), [Region::getBoundsBottom](Region#getBoundsBottom.md)_

## getBoundsRight ##
```

int getBoundsRight() const;```
Returns the region's standard right boundry position, in pixels. This boundry only considers the full tiles that are part of this region.

> _See also: [Region::getBoundsLeft](Region#getBoundsLeft.md), [Region::getBoundsTop](Region#getBoundsTop.md), [Region::getBoundsBottom](Region#getBoundsBottom.md)_

## getBoundsBottom ##
```

int getBoundsBottom() const;```
Returns the region's standard bottom boundry position, in pixels. This boundry only considers the full tiles that are part of this region.

> _See also: [Region::getBoundsLeft](Region#getBoundsLeft.md), [Region::getBoundsTop](Region#getBoundsTop.md), [Region::getBoundsRight](Region#getBoundsRight.md)_

## getClosestAccessibleRegion ##
```

Region *getClosestAccessibleRegion() const;```
Retrieves the closest accessable neighbor region.

> _See also: [Region::getClosestInaccessibleRegion](Region#getClosestInaccessibleRegion.md)_

## getClosestInaccessibleRegion ##
```

Region *getClosestInaccessibleRegion() const;```
Retrieves the closest inaccessable neighbor region.

> _See also: [Region::getClosestAccessibleRegion](Region#getClosestAccessibleRegion.md)_

## getDistance ##
```

int getDistance(BWAPI::Region *other) const```
Retrieves the distance between two region centers.