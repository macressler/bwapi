Class header file: [BWAPI/Error.h](http://code.google.com/p/bwapi/source/browse/trunk/bwapi/include/BWAPI/Error.h#)

Functions in BWAPI may set an error code. To retrieve the error code, call [Game](Game.md)::[getLastError](Game#getLastError.md).

Methods:

  * [getID](#getID.md)
  * [toString](#toString.md)

Non-member methods in Errors namespace:

  * [getError](#getError.md)
  * [allErrors](#allErrors.md)

### getID ###
int getID();

Returns a unique ID for this error.

### toString ###
std::string toString();

Returns the name of the error. For example Errors::Insufficient\_Minerals.toString() will return a std::string object containing "Insufficient Minerals".

### getError ###
[Error](Error.md) getError(std::string name);

Given the name of an error, this function will return the error code. For example: Errors::getError("Unbuildable Location") will return Errors::Unbuildable\_Location.

### allErrors ###
std::set<[Error](Error.md)>& allErrors();

Returns the set of all the error codes, which are listed below.

## Errors ##

  * [Unit\_Does\_Not\_Exist](#Unit_Does_Not_Exist.md)
  * [Unit\_Not\_Visible](#Unit_Not_Visible.md)
  * [Unit\_Not\_Owned](#Unit_Not_Owned.md)
  * [Unit\_Busy](#Unit_Busy.md)
  * [Incompatible\_UnitType](#Incompatible_UnitType.md)
  * [Incompatible\_TechType](#Incompatible_TechType.md)
  * [Incompatible\_State](#Incompatible_State.md)
  * [Already\_Researched](#Already_Researched.md)
  * [Fully\_Upgraded](#Fully_Upgraded.md)
  * [Currently\_Researching](#Currently_Researching.md)
  * [Currently\_Upgrading](#Currently_Upgrading.md)
  * [Insufficient\_Minerals](#Insufficient_Minerals.md)
  * [Insufficient\_Gas](#Insufficient_Gas.md)
  * [Insufficient\_Supply](#Insufficient_Supply.md)
  * [Insufficient\_Energy](#Insufficient_Energy.md)
  * [Insufficient\_Tech](#Insufficient_Tech.md)
  * [Insufficient\_Ammo](#Insufficient_Ammo.md)
  * [Insufficient\_Space](#Insufficient_Space.md)
  * [Invalid\_Tile\_Position](#Invalid_Tile_Position.md)
  * [Unbuildable\_Location](#Unbuildable_Location.md)
  * [Unreachable\_Location](#Unreachable_Location.md)
  * [Out\_Of\_Range](#Out_Of_Range.md)
  * [Unable\_To\_Hit](#Unable_To_Hit.md)
  * [Access\_Denied](#Access_Denied.md)
  * [File\_Not\_Found](#File_Not_Found.md)
  * [Invalid\_Parameter](#Invalid_Parameter.md)
  * [None](#None.md)
  * [Unknown](#Unknown.md)

### `Unit_Does_Not_Exist` ###

Returned if you try to order a unit or get information from a unit that no longer exists.

### `Unit_Not_Visible` ###

Returned if you try to retrieve information about a unit that is not currently visible or is dead.

### `Unit_Not_Owned` ###

Returned when attempting to order a unit that BWAPI does not own (i.e. can't order enemy army to go away )

### `Unit_Busy` ###

Returned when trying to order a unit to do something when it is performing another order or is in a state which prevents it from performing the desired order. For example, ordering a Terran Engineering Bay to upgrade something while it is already upgrading something else will return this error. Similarly, trying to train units from a factory that is lifted will return this error.

### `Incompatible_UnitType` ###

Returned if you do something weird like try to build a Pylon with an SCV, or train Vultures in a Barracks, or order a Hydralisk to lay a spider mine.

### `Incompatible_TechType` ###

Returned when trying to use a tech type with the wrong [Unit](Unit.md)::[useTech](Unit#useTech.md) method.

### `Incompatible_State` ###

Returned if you to do something like try to cancel an upgrade when the unit isn't upgrading.

### `Already_Researched` ###

Returned if you try to research something that is already researched.

### `Fully_Upgraded` ###

Returned if you try to upgrade something that is already fully upgraded.

### `Currently_Researching` ###

Returned if you try to research something that is already being researched. For example, if you try to research [TechTypes](TechTypes.md)::Spider\_Mines from two different machine shops (or twice from the same machine shop), the second call will generate this error code.

### `Currently_Upgrading` ###

Returned if you try to upgrade something that is already being upgraded. For example, if you try to upgrade [UpgradeTypes](UpgradeTypes.md)::Terran\_Infantry\_Weapons from two different Engineering Bays at the same time, the second call will generate this error code.

### `Insufficient_Minerals` ###

Returned if you try to train or build something without enough minerals.

### `Insufficient_Gas` ###

Returned if you try to train or build something without enough vespene gas.

### `Insufficient_Supply` ###

Returned if you try to train something without enough supply.

### `Insufficient_Energy` ###

Returned if you to do something like try to order a Defiler to cast a Dark Swarm without enough energy.

### `Insufficient_Tech` ###

Returned if you do something like try to train Medics when you don't have an Academy, or try to lay Spider Mines before spider mines have been researched.

### `Insufficient_Ammo` ###

Returned if you do something like try to lay Spider Mines when your Vulture is out of Spider Mines. Same thing with Reavers and Scarabs.

### `Insufficient_Space` ###
Returned if you try to train more Interceptors than the Carrier can hold, try to train more Scarabs than a Reaver can hold, or try to load more units into a transport than there is space.

### `Invalid_Tile_Position` ###

Returned if you try to build something at an invalid tile position, such as TilePositions::None, TilePositions::Unknown, or another position outside of the borders of the map.

### `Unbuildable_Location` ###

Returned if you try to build something on unbuildable terrain (either from the buildability map data or if a unit is in the way). For build tiles that are not visible, we could just use the buildability map data and assume that no units are blocking it (to prevent cheating).

### `Unreachable_Location` ###

Returned if you try to construct a building where the worker cannot reach based on static map data.

### `Out_Of_Range` ###

Returned if you order an immovable unit, like a Protoss Photon Cannon, to attack a unit that is out of range.

### `Unable_To_Hit` ###

Returned if you do something like order a Vulture to attack a flying unit.

### `Access_Denied` ###

Returned if you try to get information that is not allowed with the given flag settings. For example, trying to read the enemy's resource counts while the CompleteMapInformation flag is not enabled will return this error. Similarly, trying to read the coordinates of the screen or mouse while the UserInput flag is not enabled will also return this error.

### `File_Not_Found` ###

Returned if the function cannot find a required file.

### `Invalid_Parameter` ###

A generic error returned for bad parameters such as NULL, empty strings, strings that are too large, a bad index, etc.

### `None` ###

Used when no error has been encountered.

### `Unknown` ###

Used when the error code is not recognized or can not be determined.